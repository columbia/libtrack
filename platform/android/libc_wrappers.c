/*
 * libc_wrappers.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Specially handled libc entry points
 *
 */
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/prctl.h>
#include <sys/types.h>

#include "backtrace.h"
#include "libz.h"
#include "wrap_lib.h"
#include "wrap_tls.h"
#include "java_backtrace.h"

extern int local_strcmp(const char *s1, const char *s2);
extern int local_strncmp(const char *s1, const char *s2, size_t n);

extern struct dvm_iface dvm;

typedef int (*handler_func)(struct tls_info *tls);

static int handle_exit(struct tls_info *tls);
static int handle_thread_exit(struct tls_info *tls);
static int handle_exec(struct tls_info *tls);
static int handle_fork(struct tls_info *tls);
static int handle_prctl(struct tls_info *tls);
static int handle_pth_setname(struct tls_info *tls);
static int handle_pthread(struct tls_info *tls);
static int handle_signal(struct tls_info *tls);
static int handle_sigaction(struct tls_info *tls);

static int handle_dup(struct tls_info *tls);
static int handle_open(struct tls_info *tls);
static int handle_opendir(struct tls_info *tls);
static int handle_openat(struct tls_info *tls);
static int handle_fopen(struct tls_info *tls);
static int handle_socket(struct tls_info *tls);
static int handle_pipe(struct tls_info *tls);
static int handle_accept(struct tls_info *tls);
static int handle_closefd(struct tls_info *tls);
static int handle_closefptr(struct tls_info *tls);

static int handle_rename_fd1(struct tls_info *tls);
static int handle_epoll(struct tls_info *tls);

#define safe_call(TLS, ERR, CODE...) \
	{ \
		struct timespec _start, _end; \
		__clear_wrapping(); \
		if ((TLS)->info.log_time) \
			libc.clock_gettime(CLOCK_THREAD_CPUTIME_ID, &_start); \
		CODE; \
		if ((TLS)->info.log_time) { \
			libc.clock_gettime(CLOCK_THREAD_CPUTIME_ID, &_end); \
			log_posixtime(TLS, (TLS)->info.symbol, \
				      &_start, &_end); \
			(TLS)->info.log_time = 0; \
		} \
		ERR = *__errno(); \
		__set_wrapping(); \
	}

/*
 * keep a table of valid file descriptors and their types
 */
#define MIN_FDTABLE_SZ 128
static pthread_mutex_t fdtable_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
static int   fdtable_sz = MIN_FDTABLE_SZ;
static char  init_fdtable[MIN_FDTABLE_SZ];
static char *fdtable = init_fdtable;

/* caller must hold fdtable_mutex */
static inline int __maybe_grow_fdtable(int fd)
{
	if (fd >= fdtable_sz) {
		int newsz = fd < (MIN_FDTABLE_SZ*2) ? MIN_FDTABLE_SZ*2 : fd * 2;
		char *newtable = (char *)libc.malloc(newsz);
		if (!newtable)
			return -1;
		/* libc_log("I:grow fdtable from %d to %d", fdtable_sz, newsz); */
		libc.memset(newtable, 0, newsz);
		if (fdtable_sz) { /* copy over the old table */
			libc.memcpy(newtable, fdtable, fdtable_sz);
			if (fdtable && fdtable != init_fdtable)
				libc.free(fdtable);
		}
		fdtable_sz = newsz;
		fdtable = newtable;
	}
	return 0;
}

struct sockaddr_max {
	struct sockaddr sa;
	char d[256];
};

static char __get_socktype(int sockfd)
{
	struct sockaddr_max sam;
	int len = sizeof(sam);

	if (!libc.getsockname)
		return 'S';

	if (libc.getsockname(sockfd, (struct sockaddr *)&sam.sa, &len) < 0)
		return 'S';
	if (sam.sa.sa_family == AF_UNIX || sam.sa.sa_family == AF_LOCAL)
		return 'U';
	return 'S';
}

static char __get_path_type(const char *path, int fd)
{
	char buf[256];

	if (!path)
		return '\0';

	if (path[0] != '/') {
		if (local_strncmp("pipe:", path, 5) == 0)
			return 'P';
		if (local_strncmp("socket:", path, 7) == 0)
			return __get_socktype(fd);
		if (local_strncmp("anon_inode:[eventpoll]", path, 22) == 0)
			return 'e';
	}

	/*
	 * Set the fd type based on the path the caller is trying to open.
	 * /dev/ paths get their own type as to /proc and /sys
	 */
	if (local_strncmp("/dev/", path, 5) == 0) {
		if (local_strncmp("/binder", path + 4, 7) == 0)
			return 'B';
		else
			return 'D';
	} else if (local_strncmp("/proc/", path, 6) == 0) {
		return 'K';
	} else if (local_strncmp("/sys/", path, 5) == 0) {
		return 'k';
	}

	/*
	 * try a stat call...
	 */
	if (libc.stat) {
		struct stat st;
		if (libc.stat(path, &st) < 0)
			goto out;
		if (S_ISLNK(st.st_mode)) {
			if (libc.readlink(path, buf, sizeof(buf)) < 0)
				goto out;
			/* only support 2-levels of linking */
			if (libc.stat(buf, &st) < 0)
				goto out;
		}

		if (S_ISDIR(st.st_mode))
			return 'f';
		else if (S_ISFIFO(st.st_mode))
			return 'P';
		else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
			return 'D';
		else if (S_ISSOCK(st.st_mode))
			return __get_socktype(fd);
		else if (S_ISREG(st.st_mode))
			return 'F';
	}

out:
	/*
	 * TODO: theoretically, we should parse /proc/mounts here
	 *       just in case the caller is accessing something on
	 *       a network-mounted device, e.g., NFS
	 */

	/* default to standard file type */
	return 'F';
}


static const char fd_types[] = {
	'B', /* /dev/binder */
	'D', /* device files (/dev) */
	'E', /* epoll FD */
	'F', /* regular file */
	'f', /* directory */
	'K', /* special kernel file: /proc */
	'k', /* special kernel file: /sys */
	'P', /* pipe */
	'p', /* popen pipe */
	'S', /* network socket */
	'U', /* unix domain socket (local) */
};

static char __guess_fdtype(int fd)
{
	char path[32];
	char buf[256];

	/*
	 * On Linux/Android we can use /proc/self/fd/X to make a reasonable
	 * guess as to the origin of this FD
	 */
	libc.snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
	if (libc.readlink(path, buf, sizeof(buf)) < 0)
		return '?';

	/* guess a type based on returned path */
	return __get_path_type(buf, fd);
}

static inline char get_fdtype(int fd)
{
	char c = '\0';
	if (fd < 0)
		return c;
	mtx_lock(&fdtable_mutex);

	if (__maybe_grow_fdtable(fd) < 0)
		goto out_unlock;

	c = fdtable[fd];
	if (!c) {
		c = __guess_fdtype(fd);
		fdtable[fd] = c;
	}

out_unlock:
	mtx_unlock(&fdtable_mutex);
	return c;
}

static inline void set_fdtype(int fd, char type)
{
	if (fd < 0)
		return;
	mtx_lock(&fdtable_mutex);

	if (__maybe_grow_fdtable(fd) < 0)
		goto out_unlock;

	fdtable[fd] = type;

out_unlock:
	mtx_unlock(&fdtable_mutex);
}


/*
 * keep a cache of symbol names and some associated data
 */
#define WRAP_CACHE_SZ   256
static struct wrap_cache_entry {
	struct wrap_cache_entry *next;
	const char *name;
	handler_func handler;
	char call_str[64];
	int  call_strlen;

	uint8_t wrapsym;  /* should be called from wrap_special */
	uint8_t modsym;   /* should be called to modify symbol name */
	uint8_t notrace;
	uint8_t notime;
	uint8_t noargs;
} s_wrap_cache[WRAP_CACHE_SZ];

static inline uint8_t wrap_hash(const char *name)
{
	uint8_t v = 0;
	while (*name)
		v = (v << 1) ^ (uint8_t)(*name++);
	return v ? v : 0x1; /* disallow empty hash values */
}

#define WF_WRAPSYM  0x01
#define WF_MODSYM   0x02
#define WF_NOTRACE  0x04
#define WF_NOTIME   0x08
#define WF_NOARGS   0x10

static void add_entry(const char *symname, handler_func handler, int flags)
{
	uint8_t hidx;
	struct wrap_cache_entry *entry;

	hidx = wrap_hash(symname);
	entry = &s_wrap_cache[hidx];
	if (entry->name) {
		/* collision: malloc more space... */
		struct wrap_cache_entry *e;
		e = (struct wrap_cache_entry *)libc.malloc(sizeof(*e));
		if (!e)
			return;
		libc.memset(e, 0, sizeof(*e));
		while (entry->next)
			entry = entry->next;
		entry->next = e;
		entry = e;
	}

	entry->name = symname;
	entry->handler = handler;
	entry->call_strlen = libc.snprintf(entry->call_str,
					   sizeof(entry->call_str)-1,
					   "CALL:%s\n", symname);

	entry->wrapsym = !!(flags & WF_WRAPSYM);
	entry->modsym = !!(flags & WF_MODSYM);
	entry->notrace = !!(flags & WF_NOTRACE);
	entry->notime = !!(flags & WF_NOTIME);
	entry->noargs = !!(flags & WF_NOARGS);
}

static inline struct wrap_cache_entry *get_cached_sym(struct log_info *info)
{
	struct wrap_cache_entry *entry, *next;

	if (info->symcache)
		return info->symcache;

	if (!info->symhash)
		info->symhash = wrap_hash(info->symbol);

	entry = &s_wrap_cache[info->symhash];

	if (!entry->name)
		return NULL;

	do {
		next = entry->next;
		if (local_strcmp(info->symbol, entry->name) == 0)
			break;
		entry = next;
	} while (next);

	info->symcache = entry;

out:
	return entry;
}

void __hidden setup_wrap_cache(void)
{
	if (libc.wrap_cache)
		return;
	libc.wrap_cache = 1;

	libc.memset(&s_wrap_cache, 0, sizeof(s_wrap_cache));

	/* setup all known functions we want to wrap */
	add_entry("__fork", handle_fork, WF_WRAPSYM);
	add_entry("__bionic_clone", handle_fork, WF_WRAPSYM);
	add_entry("__sys_clone", handle_fork, WF_WRAPSYM);
	add_entry("__pthread_clone", handle_pthread, WF_WRAPSYM);
	add_entry("_exit", handle_exit, WF_WRAPSYM);
	add_entry("_exit_thread", handle_thread_exit, WF_WRAPSYM);
	add_entry("_exit_with_stack_teardown", handle_thread_exit, WF_WRAPSYM);
	add_entry("bsd_signal", handle_signal, WF_WRAPSYM);
	add_entry("clone", handle_fork, WF_WRAPSYM);
	add_entry("daemon", handle_fork, WF_WRAPSYM);
	add_entry("exit", handle_exit, WF_WRAPSYM);
	add_entry("exec", handle_exec, WF_WRAPSYM);
	add_entry("execl", handle_exec, WF_WRAPSYM);
	add_entry("execle", handle_exec, WF_WRAPSYM);
	add_entry("execlp", handle_exec, WF_WRAPSYM);
	add_entry("execve", handle_exec, WF_WRAPSYM);
	add_entry("execvp", handle_exec, WF_WRAPSYM);
	add_entry("fork", handle_fork, WF_WRAPSYM);
	add_entry("prctl", handle_prctl, WF_WRAPSYM);
	add_entry("pthread_create", handle_pthread, WF_WRAPSYM);
	add_entry("pthread_exit", handle_thread_exit, WF_WRAPSYM);
	add_entry("pthread_setname_np", handle_pth_setname, WF_WRAPSYM);
	add_entry("sig_action", handle_sigaction, WF_WRAPSYM);
	add_entry("signal", handle_signal, WF_WRAPSYM);
	add_entry("system", handle_fork, WF_WRAPSYM);
	add_entry("sysv_signal", handle_signal, WF_WRAPSYM);
	add_entry("vfork", handle_fork, WF_WRAPSYM);

	/*
	 * functions on which we dynamically interpose
	 * (to intercept the returned results)
	 */
	add_entry("__open", handle_open, WF_WRAPSYM);
	add_entry("__openat", handle_openat, WF_WRAPSYM);
	add_entry("__sclose", handle_closefptr, WF_WRAPSYM | WF_MODSYM);
	add_entry("accept", handle_accept, WF_WRAPSYM);
	add_entry("close", handle_closefd, WF_WRAPSYM | WF_MODSYM);
	add_entry("dup", handle_dup, WF_WRAPSYM);
	add_entry("dup2", handle_dup, WF_WRAPSYM);
	add_entry("epoll_create", handle_epoll, WF_WRAPSYM);
	add_entry("epoll_ctl", handle_epoll, WF_WRAPSYM);
	add_entry("fclose", handle_closefptr, WF_WRAPSYM | WF_MODSYM);
	add_entry("fopen", handle_fopen, WF_WRAPSYM);
	add_entry("freopen", handle_fopen, WF_WRAPSYM);
	add_entry("open", handle_open, WF_WRAPSYM);
	add_entry("opendir", handle_opendir, WF_WRAPSYM);
	add_entry("openat", handle_openat, WF_WRAPSYM);
	add_entry("pclose", handle_closefptr, WF_WRAPSYM | WF_MODSYM);
	add_entry("pipe", handle_pipe, WF_WRAPSYM);
	add_entry("pipe2", handle_pipe, WF_WRAPSYM);
	add_entry("popen", handle_pipe, WF_WRAPSYM);
	add_entry("socket", handle_socket, WF_WRAPSYM);
	add_entry("socketpair", handle_socket, WF_WRAPSYM);

	/* setup functions we want to dynamically rename in the BT */
	add_entry("epoll_wait", handle_epoll, WF_MODSYM);
	add_entry("read", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("readv", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("pread", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("pread64", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("write", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("writev", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("pwrite", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("pwrite64", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("ioctl", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("__ioctl", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("fcntl", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("__fcntl", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("__fcntl64", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	add_entry("fstat", handle_rename_fd1, WF_WRAPSYM | WF_MODSYM);
	/* TODO: select? */
	/* TODO: fdprintf ? */
	/* TODO: fstatfs ? */
	/* TODO: mmap ? */

	/* functions that we don't want to backtrace */
	add_entry("memset", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memcpy", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memcmp", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memmove", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memmem", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memswap", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("memrchr", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("__memcmp16", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("malloc", NULL, WF_NOTRACE);
	add_entry("realloc", NULL, WF_NOTRACE);
	add_entry("calloc", NULL, WF_NOTRACE);
	add_entry("free", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("__memcpy_chk", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("__memmove_chk", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("pthread_getspecific", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("pthread_setspecific", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("pthread_self", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
	add_entry("clock_gettime", NULL, WF_NOTRACE | WF_NOTIME | WF_NOARGS);
}

static inline void timespec_sub(struct timespec *a, const struct timespec *b)
{
	a->tv_sec  -= b->tv_sec;
	a->tv_nsec -= b->tv_nsec;
	if (a->tv_nsec < 0) {
		a->tv_nsec += 1000000000;
		a->tv_sec  -= 1;
	}
}

static inline void log_posixtime(struct tls_info *tls, const char *sym,
				 struct timespec *start, struct timespec *end)
{
	struct timespec posix_time = *end;
	timespec_sub(&posix_time, start);
	bt_printf(tls, "LOG:T:%s:%lu.%lu\n", sym,
		  (unsigned long)posix_time.tv_sec,
		  (unsigned long)posix_time.tv_nsec);
}

/**
 * @wrapped_return - carefully pull a stored return value from TLS and return
 *                   to the original caller
 *
 * TODO:
 * Right now, we always return a 32-bit number. This won't work for large
 * return value functions...
 */
uint32_t wrapped_return(void)
{
	/* record this ASAP */
	struct timespec posix_end;
	libc.clock_gettime(CLOCK_THREAD_CPUTIME_ID, &posix_end);

	{
		struct tls_info *tls;
		struct ret_ctx *ret;
		uint32_t rval, err = (*__errno());

		tls = get_tls();
		ret = get_retmem(tls);
		if (!ret)
			BUG_MSG(0x4311, "No TLS return value!");

		if (tls->info.log_time) {
			rval = 0; /* handled by arch_wrapped_return */
			log_posixtime(tls, ret->sym,
				      &ret->posix_start, &posix_end);
			tls->info.log_time = 0;
		} else {
			err = ret->_errno;
			rval = ret->u.u32[0];
		}

		(*__errno()) = err;
		return rval;
	}
}

/*
 * Use a cache/table to modify info->symbol based on the function called and
 * its arguments. This allows us to track FDs through the system and mark
 * their access as network, FS, pipe, etc. by translating the symbol name to,
 * e.g., read_N (for network read).
 */
void __hidden wrap_symbol_mod(struct tls_info *tls)
{
	struct wrap_cache_entry *e;

	e = get_cached_sym(&tls->info);

	if (e && e->modsym && e->handler) {
		tls->info.should_mod_sym = 1;
		tls->info.should_handle = 0;
		(void)e->handler(tls);
		tls->info.should_mod_sym = 0;
	}
}

/**
 * @wrap_symbol_notrace
 *
 */
int __hidden wrap_symbol_notrace(struct tls_info *tls)
{
	struct wrap_cache_entry *e;
	e = get_cached_sym(&tls->info);
	if (e)
		return e->notrace;
	return 0;
}

/**
 * @wrap_symbol_notime
 *
 */
int __hidden wrap_symbol_notime(struct tls_info *tls)
{
	struct wrap_cache_entry *e;
	e = get_cached_sym(&tls->info);
	if (e)
		return e->notime;
	return 0;
}

/**
 * @wrap_symbol_noargs
 *
 */
int __hidden wrap_symbol_noargs(struct tls_info *tls)
{
	struct wrap_cache_entry *e;
	e = get_cached_sym(&tls->info);
	if (e)
		return e->noargs;
	return 0;
}

/**
 * @wrap_symbol_callstr
 *
 */
const char __hidden *wrap_symbol_callstr(struct tls_info *tls, int *len)
{
	struct wrap_cache_entry *e;
	e = get_cached_sym(&tls->info);
	if (e) {
		if (len)
			*len = e->call_strlen;
		return e->call_str;
	}
	return NULL;
}

/**
 * @wrap_special - handle the wrapping of special functions
 *
 * @param symbol The symbol name being wrapped
 * @param regs Pointer to memory holding saved register state
 * @param stack Pointer to stack memory associated with original call
 *
 * This function should return:
 *	0 if nothing special is to happen
 *	!0 if it handled the actual wrap call
 *	   (will invoke wrapped_return instead of actual function call)
 */
int __hidden wrap_special(struct tls_info *tls)
{
	struct wrap_cache_entry *e;

	if (!tls || !wsym(tls))
		return 0;

	e = get_cached_sym(&tls->info);
	if (e && e->wrapsym && e->handler) {
		int ret;
		tls->info.should_handle = 1;
		tls->info.should_mod_sym = 0;
		ret = e->handler(tls);
		tls->info.should_handle = 0;
		return ret;
	}

	return 0;
}

static void flush_and_close(struct tls_info *tls)
{
	if (tls->info.should_log) {
		bt_printf(tls, "LOG:I:CLOSE:%s(0x%x,0x%x,0x%x,0x%x):\n",
			  wsym(tls),
			  tls->info.regs[0], tls->info.regs[1],
			  tls->info.regs[2], tls->info.regs[3]);
		bt_flush(tls, &tls->info);
	}
	libc_close_log();
}

int handle_exit(struct tls_info *tls)
{
	if (!tls->info.should_handle)
		return 0;
	close_dvm_iface(&dvm);
	flush_and_close(tls);
	clear_tls(1);
	return 0;
}

int handle_fork(struct tls_info *tls)
{
	if (!tls->info.should_handle)
		return 0;
	flush_and_close(tls);
	libc.forking = libc.getpid();
	return 0;
}

int handle_prctl(struct tls_info *tls)
{
	int cmd;
	const char *name;

	if (!tls->info.should_handle)
		return 0;

	cmd = (int)tls->info.regs[0];
	name = (const char *)(tls->info.regs[1]);

	if (cmd != PR_SET_NAME)
		return 0;

	/* close this log file and open a new one with the new name! */
	if (tls->info.should_log)
		bt_printf(tls, "LOG:I:name=%s\n", name);
	return 0;
}

int handle_pth_setname(struct tls_info *tls)
{
	const char *name;

	if (!tls->info.should_handle)
		return 0;

	name = (const char *)(tls->info.regs[1]);

	/* close this log file and open a new one with the new name! */
	if (tls->info.should_log)
		bt_printf(tls, "LOG:I:name=%s\n", name);
	return 0;
}


static const char *wrap_ld_preload(const char *old_val)
{
	size_t sz = 0, old_sz = 0;
	const char *p;
	const char *ld_preload = LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME);
	size_t ldp_sz = sizeof(LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME));

	if (!old_val) {
		p = "LD_PRELOAD=" LIB_PATH "/" _str(_IBNAM_)
				  ":" LIB_PATH "/" _str(LIBNAME);
		goto out;
	}

	p = old_val;
	while (*p) p++;
	old_sz = (size_t)(p - old_val); /* doesn't include NULL terminator */

	p = libc.malloc(old_sz + ldp_sz + 1); /* +1 for ':' */
	if (!p)
		return NULL;

	libc.memcpy((void *)p, (void *)old_val, old_sz);
	((char *)p)[old_sz] = ':';
	libc.memcpy((void *)(p + old_sz + 1), (void *)ld_preload, ldp_sz);

out:
	/* libc_log("I:New LD_PRELOAD value '%s'", p); */
	return p;
}

static const char **wrap_environ(const char **old_env)
{
	int n, sz = 1; /* NULL */
	const char **p = old_env;
	const char **new_env = NULL;
	int add_ldpreload = 1;

	/* the number of vars we'll be adding */
	n = 1; /* LD_PRELOAD */

	if (!old_env)
		goto alloc_new;

	/* get number of env vars */
	while (*p) {
		/* libc_log("I:env[]=%s", *p); */
		if (local_strncmp(*p,"LD_PRELOAD", 10) == 0) {
			/* add our path to the preload list */
			*p = wrap_ld_preload(*p);
			/* shortcut: we modified the pointer in-place */
			new_env = old_env;
		}
		sz++;
		p++;
	}

	if (new_env)
		return new_env;

alloc_new:
	new_env = (const char **)libc.malloc((sz + n) * sizeof(*p));
	if (!new_env) {
		libc_log("E:No memory for new env!");
		return old_env;
	}
	libc.memset(new_env, 0, (sz + n) * sizeof(*p));

	new_env[0] = wrap_ld_preload(NULL);

	/* copy over old pointers */
	while (old_env && sz--)
		new_env[n+sz] = old_env[sz];

	return new_env;
}

static void setup_exec_env(struct tls_info *tls)
{
	const char *ld_preload = LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME);
	libc.setenv("LD_PRELOAD", ld_preload, 1);
	if (tls->info.should_log)
		bt_printf(tls, "LOG:I:New LD_PRELOAD value '%s'", ld_preload);
	/* libc.setenv("LD_DEBUG", "3", 1); */
}

int handle_exec(struct tls_info *tls)
{
	struct log_info *info = &tls->info;

	if (!info->should_handle)
		return 0;

	if (local_strcmp("execle", info->symbol) == 0)
		libc_log("E:No support for execle!");

	if (local_strcmp("execve", info->symbol) == 0)
		info->regs[2] = (uint32_t)wrap_environ((const char **)info->regs[2]);
	else
		setup_exec_env(tls);

	if (info->should_log)
		bt_printf(tls, "LOG:I:%s:%s:\n", info->symbol, (const char *)info->regs[0]);

	close_dvm_iface(&dvm);
	flush_and_close(tls);
	clear_tls(1);

	return 0;
}

int handle_pthread(struct tls_info *tls)
{
	if (!tls->info.should_handle)
		return 0;
	flush_and_close(tls);
	return 0;
}

int handle_thread_exit(struct tls_info *tls)
{
	if (!tls->info.should_handle)
		return 0;

	flush_and_close(tls);
	clear_tls(0); /* release TLS memory */
	return 0;
}


typedef void (*sighandler_func)(int sig, void *siginfo, void *ctx);
typedef void (*sigaction_func)(int, struct siginfo *, void *);

#define MAX_SIGNALS 32
static int s_special_sig = -1;
sighandler_func s_sighandler[MAX_SIGNALS];

static inline const char *signame(int sig)
{
	if (libc.strsignal)
		return libc.strsignal(sig);
	return "UNKNOWN";
}

static void __flush_btlog(void)
{
	struct tls_info *tls;

	void *logf;
	char *buf;

	if (!should_log())
		return;

	tls = get_tls();
	if (!tls)
		return;

	if (tls->logfile && tls->logbuffer)
		bt_flush(tls, &tls->info);
	log_flush(tls->logfile);
}

static void wrapped_sighandler(int sig, struct siginfo *siginfo, void *ctx)
{
	sighandler_func sh;

	/*
	 * put this in a separate scope in order to call the
	 * original function with as little additional stack
	 * usage as possible.
	 */
	if (should_log())
		libc_log("SIG:RCV:%d:%s", sig, signame(sig));

	if (sig >= MAX_SIGNALS)
		return; /* I guess we eat this one... */

	if (sig == s_special_sig) {
		__flush_btlog();
		libc_log("SIG:LOG_FLUSH:%d:%s:", sig, signame(sig));
		libc.fflush(NULL); /* flush the entire process' buffers */
		libc_close_log();
		return;
	}

	/* NOTE: siginfo and ctx may be invalid! */
	if (s_sighandler[sig]) {
		/* flush the logs every time we get a signal
		 * that the app handles */
		__flush_btlog();
		libc_close_log();
		(s_sighandler[sig])(sig, siginfo, ctx);
	}
}

/*
 * 'orig' should be a valid function pointer
 */
static int install_sighandler(struct log_info *info,
			      int sig, sighandler_func orig)
{
	if (sig >= MAX_SIGNALS)
		return 1;

	if (info->should_log) {
		Dl_info dli;
		void *f = get_log(0);
		if (dladdr((void *)orig, &dli)) {
			__log_print(&info->tv, f,
				    "SIG", "HANDLE:%s[%p](%s@%p):%d:%s:",
				    dli.dli_sname ? dli.dli_sname : "??",
				    (void *)orig,
				    dli.dli_fname ? dli.dli_fname : "xx",
				    dli.dli_fbase ? dli.dli_fbase : (void *)0,
				    sig, signame(sig));
		} else {
			__log_print(&info->tv, f,
				    "SIG", "HANDLE:[%p]:%d:%s:",
				    (void *)orig, sig, signame(sig));
		}
		log_flush(f);
	}
	s_sighandler[sig] = orig;
	return 0;
}

int handle_signal(struct tls_info *tls)
{
	if (!tls->info.should_handle)
		return 0;

	sighandler_func sh = NULL;

	sh = (sighandler_func)(tls->info.regs[1]);
	if (sh == NULL ||
	    sh == (sighandler_func)SIG_IGN ||
	    sh == (sighandler_func)SIG_DFL ||
	    sh == (sighandler_func)SIG_ERR)
		return 0;

	if (install_sighandler(&tls->info, (int)tls->info.regs[0], sh) == 0)
		tls->info.regs[1] = (uint32_t)wrapped_sighandler;

	return 0;
}

void __hidden setup_special_sighandler(int sig)
{
	struct sigaction sa;

	if (!libc.sigaction)
		return;

	libc.memset(&sa, 0, sizeof(sa));
	sa.sa_handler = (void (*)(int))wrapped_sighandler;
	libc.sigaction(sig, &sa, NULL);

	s_special_sig = sig;

	if (should_log())
		libc_log("I:Installed special handler for sig %d", sig);
}

int handle_sigaction(struct tls_info *tls)
{
	struct sigaction *sa;
	sighandler_func sh = NULL;

	if (!tls->info.should_handle)
		return 0;

	sa = (struct sigaction *)(tls->info.regs[1]);
	if (!sa)
		return 0;

	sh = (sighandler_func)(sa->sa_sigaction);
	if (sh == NULL ||
	    sh == (sighandler_func)SIG_IGN ||
	    sh == (sighandler_func)SIG_DFL ||
	    sh == (sighandler_func)SIG_ERR)
		return 0;

	if (install_sighandler(&tls->info, (int)tls->info.regs[0], sh) == 0)
		sa->sa_sigaction = (sigaction_func)wrapped_sighandler;

	return 0;
}

int handle_open(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int rval, err;
	char type;
	const char *path;
	struct log_info *info;
	int (*openfunc)(const char *, int, int, int);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int open(const char *path, int flags, ...);
	 * int __open(const char *path, int flags, ...);
	 */
	path = (const char *)info->regs[0];
	openfunc = info->func;

	safe_call(tls, err,
		  rval = openfunc(path, (int)info->regs[1],
				  (int)info->regs[2], (int)info->regs[3])
		 );
	if (rval >= 0) {
		char type = __get_path_type(path, rval);
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d,%s)='%c':\n", rval, path, type);
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4312, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_opendir(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int err;
	const char *path;
	struct log_info *info;
	DIR *rval;
	DIR *(*openfunc)(const char *);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * DIR *opendir(const char *dirname);
	 */
	path = (const char *)info->regs[0];
	openfunc = info->func;

	safe_call(tls, err,
		  rval = openfunc(path);
		 );
	if (rval != NULL && libc.dirfd) {
		int dfd = libc.dirfd(rval);
		set_fdtype(dfd, 'f');
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d,%s)='f':\n", dfd, path);
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4312, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = (uint32_t)rval;
	return 1;
}

int handle_openat(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int rval, err;
	struct log_info *info;
	const char *path;
	int (*openfunc)(int, const char *, int);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int openat(int dirfd, const char *pathname, int flags);
	 * int __openat(int dirfd, const char *pathname, int flags);
	 */
	path = (const char *)info->regs[1];
	openfunc = info->func;

	safe_call(tls, err,
		  rval = openfunc((int)info->regs[0], path, (int)info->regs[2])
		 );
	if (rval >= 0) {
		char type = __get_path_type(path, rval);
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d,%s)='%c':\n", rval, path, type);
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4313, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_fopen(struct tls_info *tls)
{
	struct ret_ctx *ret;
	FILE *rval;
	int err;
	const char *path;
	const char *mode;
	struct log_info *info;
	FILE *(*openfunc)(const char *, const char *, void *);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * FILE *fopen(const char *path, const char *mode);
	 * FILE *freopen(const char *path, const char *mode, FILE *stream);
	 */
	path = (const char *)info->regs[0];
	mode = (const char *)info->regs[1];
	openfunc = info->func;

	safe_call(tls, err, rval = openfunc(path, mode, (void *)info->regs[2]));
	if (rval) {
		int fd = libc.fno(rval);
		char type = __get_path_type(path, fd);
		set_fdtype(fd, type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d,%s)='%c':\n", fd, path, type);
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4314, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = (uint32_t)rval;
	return 1;
}


int handle_dup(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int oldfd, rval, err;
	char type;
	struct log_info *info;
	int (*dupfunc)(int, int);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int dup(int oldfd);
	 * int dup2(int oldfd, int newfd);
	 */
	dupfunc = info->func;

	oldfd = info->regs[0];
	if (oldfd < 0)
		return 0; /* don't mess around with invalid input */

	type = get_fdtype(oldfd);

	safe_call(tls, err, rval = dupfunc(oldfd, info->regs[1]));

	/* we duplicated the fd, so it's the same type as the oldfd */
	if (rval >= 0) {
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d)='%c':\n",
				  rval, type ? type : '?');
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4315, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_socket(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int rval, err;
	struct log_info *info;
	char type;
	int domain;
	int *sv;
	int (*sockfunc)(int, int, int, int *);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int socket(int domain, int type, int protocol);
	 * int socketpair(int domain, int type, int protocol, int sv[2]);
	 */
	sockfunc = info->func;
	domain = (int)info->regs[0];
	sv = (int *)(info->regs[3]);

	type = 'S';
	if (domain == AF_UNIX || domain == AF_LOCAL)
		type = 'U';

	safe_call(tls, err, rval = sockfunc(domain, (int)info->regs[1],
					     (int)info->regs[2], sv));
	if (rval < 0)
		goto out;

	if (local_strncmp("tpair", info->symbol + 5, 5) == 0) {
		/* socket pair returns values in sv */
		set_fdtype(sv[0], type);
		set_fdtype(sv[1], type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d)='%c':\n"
				       "LOG:I:fd(%d)='%c':\n",
				       sv[0], type, sv[1], type);
	} else {
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d)='%c':\n", rval, type);
	}

out:
	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4316, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_pipe(struct tls_info *tls)
{
	struct ret_ctx *ret;
	uint32_t rval, err;
	struct log_info *info;
	uint32_t (*pipefunc)(int *, int);
	FILE *(*popenfunc)(const char *, const char *);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int pipe(int fd[2]);
	 * int pipe2(int fd[2], int flags);
	 * FILE *popen(const char *cmd, const char *type);
	 */
	pipefunc = info->func;
	popenfunc = info->func;

	if (info->symbol[1] == 'i') { /* pipe/pipe2 */
		int *pfd = (int *)info->regs[0];

		safe_call(tls, err, rval = pipefunc(pfd, (int)info->regs[1]));
		if (rval == 0 && pfd) {
			set_fdtype(pfd[0], 'P');
			set_fdtype(pfd[1], 'P');
			if (info->should_log)
				bt_printf(tls, "LOG:I:fd(%d)='P'"
					        ":LOG:I:fd(%d)='P':\n",
					  pfd[0], pfd[1]);
		}
	} else if (info->symbol[1] == 'o') {
		FILE *f;

		/* popen forks! */
		flush_and_close(tls);
		libc.forking = libc.getpid();

		safe_call(tls, err,
			  f = popenfunc((const char *)info->regs[0],
					(const char *)info->regs[1])
			 );
		if (f) {
			int fd = libc.fno(f);
			set_fdtype(fd, 'p');
			if (info->should_log)
				bt_printf(tls, "LOG:I:fd(%d,%s)='p':\n",
					  fd, (const char *)info->regs[0]);
		}
		rval = (uint32_t)f;
	} else {
		/* don't handle this function */
		return 0;
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4317, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_accept(struct tls_info *tls)
{
	struct ret_ctx *ret;
	int rval, err, sockfd;
	struct log_info *info;
	char type;
	int (*acceptfunc)(int, void *, void *);

	info = &tls->info;
	if (!info->should_handle)
		return 0;

	/*
	 * handles:
	 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	 */
	sockfd = (int)info->regs[0];
	acceptfunc = info->func;
	type = get_fdtype(sockfd);

	safe_call(tls, err,
		  rval = acceptfunc(sockfd, (void *)info->regs[1],
				    (void *)info->regs[2])
		 );
	if (rval >= 0) {
		set_fdtype(rval, 'S');
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d)='S':\n", rval);
	}

	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4318, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = rval;
	return 1;
}

static int __rename_close(struct tls_info *tls, int fd)
{
	char type;
	struct log_info *info;
	struct ret_ctx *ret;

	info = &tls->info;

	type = get_fdtype(fd);

	ret = get_retmem(tls);
	if (!ret)
		return 0;

	libc.snprintf(ret->symmod, MAX_SYMBOL_LEN, "%s_%c",
		      info->symbol, type ? type : '?');
	info->symbol = (const char *)ret->symmod;

	return 0;
}

int handle_closefd(struct tls_info *tls)
{
	int fd;
	struct log_info *info = &tls->info;

	fd = (int)info->regs[0];

	if (info->should_mod_sym)
		return __rename_close(tls, fd);

	if (!info->should_handle)
		return 0;

	/* handle: close() */

	mtx_lock(&fdtable_mutex);
	if (fd < fdtable_sz)
		fdtable[fd] = 0; /* it's now closed */
	mtx_unlock(&fdtable_mutex);

	if (info->should_log)
		bt_printf(tls, "LOG:I:%s:fd(%d):\n", info->symbol, fd);
	return 0;
}

int handle_closefptr(struct tls_info *tls)
{
	FILE *f;
	int fd;
	struct log_info *info = &tls->info;

	f = (FILE *)info->regs[0];
	fd = libc.fno(f);

	if (info->should_mod_sym)
		return __rename_close(tls, fd);

	if (!info->should_handle)
		return 0;

	/* handle: fclose(), pclose(), __sclose() */

	mtx_lock(&fdtable_mutex);
	if (fd < fdtable_sz)
		fdtable[fd] = 0; /* it's now closed */
	mtx_unlock(&fdtable_mutex);

	if (info->should_log)
		bt_printf(tls, "LOG:I:%s:fd(%d):\n", info->symbol, fd);

	return 0;
}

int handle_rename_fd1(struct tls_info *tls)
{
	int fd;
	char type;
	struct log_info *info;
	struct ret_ctx *ret;

	info = &tls->info;
	fd = (int)info->regs[0];

	if (info->should_handle) {
		/* print out the FD used in this call */
		if (info->should_log)
			bt_printf(tls, "LOG:I:%s:fd(%d):\n", info->symbol, fd);
		return 0;
	}

	if (!info->should_mod_sym)
		return 0;

	/*
	 * symbols: read, readv, pread, pread64
	 *          write, writev, pwrite, pwrite64
	 *          ioctl, __ioctl, fcntl, __fcntl
	 * all have fd as first argument!
	 */
	type = get_fdtype(fd);

	ret = get_retmem(tls);
	if (!ret)
		return 0;

	libc.snprintf(ret->symmod, MAX_SYMBOL_LEN, "%s_%c", info->symbol, type);
	info->symbol = (const char *)ret->symmod;

	return 0;
}


/*****
 *
 * epoll handling
 *
 */
#define MAX_EPOLL_FDS 100
static struct epoll_fd_set {
	int fds[MAX_EPOLL_FDS];
} *s_epfds = NULL;
int s_epfds_sz = 0;

static pthread_mutex_t epfds_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;

static inline int __maybe_grow_epfds(int fd)
{
	if (!s_epfds_sz|| fd > s_epfds_sz) {
		int i, j;
		int newsz = fd < (MIN_FDTABLE_SZ/2) ? MIN_FDTABLE_SZ : fd * 2;
		struct epoll_fd_set *newtable;
		newtable = (struct epoll_fd_set *)libc.malloc(newsz * sizeof(*newtable));
		if (!newtable)
			return -1;
		/* set all fds to -1 initially */
		for (i = 0; i < newsz; i++) {
			for (j = 0; j < MAX_EPOLL_FDS; j++)
				newtable[i].fds[j] = -1;
		}
		if (s_epfds_sz) { /* copy over the old table */
			libc.memcpy(newtable, s_epfds, s_epfds_sz * sizeof(*newtable));
			if (s_epfds)
				libc.free(s_epfds);
		}
		s_epfds_sz = newsz;
		s_epfds = (struct epoll_fd_set *)newtable;
	}
	return 0;
}


/* caller should hold epfds_mutex */
static struct epoll_fd_set* get_epfds(int epfd)
{
	if (__maybe_grow_epfds(epfd) < 0)
		return NULL;
	return &s_epfds[epfd];
}

static void add_epfd(int epfd, int fd)
{
	struct epoll_fd_set *epfds;
	int i;

	if (fd < 0 || epfd < 0)
		return;

	mtx_lock(&epfds_mutex);
	epfds = get_epfds(epfd);
	if (!epfds) {
		mtx_unlock(&epfds_mutex);
		return;
	}

	for (i = 0; i < MAX_EPOLL_FDS; i++) {
		if (epfds->fds[i] < 0) {
			epfds->fds[i] = fd;
			break;
		}
		if (epfds->fds[i] == fd)
			break; /* it's alredy there?! */
	}
	mtx_unlock(&epfds_mutex);
}

static void del_epfd(int epfd, int fd)
{
	struct epoll_fd_set *epfds;
	int i;

	if (fd < 0 || epfd < 0)
		return;

	mtx_lock(&epfds_mutex);
	epfds = get_epfds(epfd);
	if (!epfds) {
		mtx_unlock(&epfds_mutex);
		return;
	}

	for (i = 0; i < MAX_EPOLL_FDS; i++) {
		if (epfds->fds[i] == fd) {
			epfds->fds[i] = -1;
			break;
		}
	}
	/* compact */
	for ( ; i < MAX_EPOLL_FDS - 1; i++) {
		if (epfds->fds[i+1] < 0)
			break;
		epfds->fds[i] = epfds->fds[i+1];
		epfds->fds[i+1] = -1;
	}
	mtx_unlock(&epfds_mutex);
}

static int __epoll_modsym(struct tls_info *tls)
{
	int rval, i, j;
	char *symptr, *symend;
	struct log_info *info = &tls->info;
	struct epoll_fd_set *epfds;
	char fdt[MAX_EPOLL_FDS];

	struct ret_ctx *ret;

	/* only rename epoll_wait */
	if (strncmp("wait", info->symbol + 6, 4) != 0)
		return 0;

	/* TODO: modify epoll_wait name based on consituent FDs */
	mtx_lock(&epfds_mutex);
	epfds = get_epfds((int)info->regs[0]);
	if (!epfds) {
		mtx_unlock(&epfds_mutex);
		return 0;
	}

	libc.memset(&fdt, 0, MAX_EPOLL_FDS);
	for (i = 0; i < MAX_EPOLL_FDS; i++) {
		if (epfds->fds[i] < 0)
			break;
		fdt[i] = get_fdtype(epfds->fds[i]);
		if (!fdt[i])
			fdt[i] = '?';
	}
	mtx_unlock(&epfds_mutex);

	ret = get_retmem(tls);
	if (!ret)
		return 0;

	symptr = ret->symmod;
	symend = symptr + MAX_SYMBOL_LEN - 1;
	symptr += libc.snprintf(symptr, MAX_SYMBOL_LEN, "%s_", info->symbol);

	/* sort the file types using fd_types array */
	for (i = 0; i < (int)sizeof(fd_types); i++) {
		for (j = 0; j < MAX_EPOLL_FDS; j++) {
			if (fdt[j] == fd_types[i]) {
				*symptr++ = fdt[j];
				fdt[j] = 0;
				if (symptr > symend)
					break;
			}
		}
		if (symptr > symend)
			break;
	}

	/* output any unknown fd types at the end */
	for (j = 0; j < MAX_EPOLL_FDS; j++) {
		if (fdt[j]) {
			*symptr++ = fdt[j];
			if (symptr > symend)
				break;
		}
	}
	*symptr = 0;

	info->symbol = (const char *)ret->symmod;

	return 0;
}


static int __handle_epoll_create(struct tls_info *tls)
{
	int epfd, err;
	struct ret_ctx *ret;
	struct log_info *info = &tls->info;
	int (*createfunc)(int);
	/*
	 * handles:
	 * int epoll_create(int size);
	 */
	createfunc = info->func;

	safe_call(tls, err, epfd = createfunc((int)info->regs[0]));
	if (epfd >= 0) {
		set_fdtype(epfd, 'E');
		if (info->should_log)
			bt_printf(tls, "LOG:I:fd(%d)='E':\n", epfd);
	}
	ret = get_retmem(NULL);
	if (!ret)
		BUG_MSG(0x4319, "No TLS return value!");
	ret->sym = info->symbol;
	ret->_errno = err;
	ret->u.u32[0] = epfd;
	return 1;
}

static int __handle_epoll_ctl(struct tls_info *tls)
{
	int epfd, fd, op;
	struct log_info *info = &tls->info;

	epfd = (int)info->regs[0];
	op = (int)info->regs[1];
	fd = (int)info->regs[2];

	if (info->should_log)
		bt_printf(tls, "LOG:I:%s fd(%d)='%c' %s epfd=%d:\n",
			  op == EPOLL_CTL_ADD ? "adding" :
			    (op == EPOLL_CTL_DEL ? "deleting" : "??"),
			  fd,
			  get_fdtype(fd),
			  op == EPOLL_CTL_ADD ? "to" :
			    (op == EPOLL_CTL_DEL ? "from" : "??"),
			  epfd);
	if (op == EPOLL_CTL_ADD)
		add_epfd(epfd, fd);
	else if (op == EPOLL_CTL_DEL)
		del_epfd(epfd, fd);

	return 0;
}

int handle_epoll(struct tls_info *tls)
{
	struct log_info *info;

	if (!tls)
		return 0;

	info = &tls->info;

	if (info->should_mod_sym)
		return __epoll_modsym(tls);

	if (!info->should_handle)
		return 0;

	/*
	 * we're to handle one of these functions,
	 * right now it's epoll_create and epoll_ctl
	 */
	if (strncmp("ctl", info->symbol + 6, 3) == 0)
		return __handle_epoll_ctl(tls);
	else if (strncmp("create", info->symbol + 6, 6) == 0)
		return __handle_epoll_create(tls);
	else
		return 0;
}
