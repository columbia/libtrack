/*
 * libc_wrappers.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Specially handled libc entry points
 *
 */
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#include "wrap_lib.h"
#include "backtrace.h"
#include "java_backtrace.h"

extern int local_strcmp(const char *s1, const char *s2);
extern int local_strncmp(const char *s1, const char *s2, size_t n);

extern pthread_key_t log_key;
extern pthread_key_t s_log_buffer_key;

extern struct dvm_iface dvm;

typedef int (*handler_func)(struct log_info *info);

static int handle_exit(struct log_info *info);
static int handle_thread_exit(struct log_info *info);
static int handle_exec(struct log_info *info);
static int handle_fork(struct log_info *info);
static int handle_pthread(struct log_info *info);
static int handle_signal(struct log_info *info);
static int handle_sigaction(struct log_info *info);

static int handle_dup(struct log_info *info);
static int handle_open(struct log_info *info);
static int handle_openat(struct log_info *info);
static int handle_fopen(struct log_info *info);
static int handle_socket(struct log_info *info);
static int handle_pipe(struct log_info *info);
static int handle_accept(struct log_info *info);
static int handle_closefd(struct log_info *info);
static int handle_closefptr(struct log_info *info);

static int handle_read(struct log_info *info);
static int handle_write(struct log_info *info);


/*
 * keep a table of valid file descriptors and their types
 */
#define MIN_FDTABLE_SZ 128
static pthread_mutex_t fdtable_mutex = PTHREAD_MUTEX_INITIALIZER;
static int   fdtable_sz = 0;
static char *fdtable = NULL;

/* caller must hold fdtable_mutex */
static inline int __maybe_grow_fdtable(int fd)
{
	if (!fdtable_sz || fd > fdtable_sz) {
		int newsz = fd < (MIN_FDTABLE_SZ/2) ? MIN_FDTABLE_SZ : fd * 2;
		char *newtable = (char *)libc.malloc(newsz);
		if (!newtable)
			return -1;
		libc.memset(newtable, 0, newsz);
		if (fdtable_sz) { /* copy over the old table */
			libc.memcpy(newtable, fdtable, fdtable_sz);
			if (fdtable)
				libc.free(fdtable);
		}
		fdtable_sz = newsz;
		fdtable = newtable;
	}
	return 0;
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

	uint8_t wrapsym;  /* should be called from wrap_special */
	uint8_t modsym;   /* should be called to modify symbol name */
} s_wrap_cache[WRAP_CACHE_SZ];
static pthread_mutex_t cache_mutex = PTHREAD_MUTEX_INITIALIZER;

static inline uint8_t wrap_hash(const char *name)
{
	uint8_t v = 0;
	while (*name)
		v = (v << 1) ^ (uint8_t)(*name++);
	return v ? v : 0x1; /* disallow empty hash values */
}

static void add_entry(const char *symname, handler_func handler,
		      int wrapsym, int modsym)
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
	entry->wrapsym = wrapsym;
	entry->modsym = modsym;
}

static inline struct wrap_cache_entry *get_cached_sym(struct log_info *info)
{
	uint8_t hidx;
	struct wrap_cache_entry *entry, *next;

	if (info->symhash)
		return info->symcache;

	hidx = wrap_hash(info->symbol);
	entry = &s_wrap_cache[hidx];

	info->symhash = hidx;

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

static inline void clear_wrap_cache(struct log_info *info)
{
	int i;
	struct wrap_cache_entry *entry, *tmp;

	for (i = 0; i < WRAP_CACHE_SZ; i++) {
		entry = &s_wrap_cache[i];
		entry = entry->next;
		while (entry) {
			tmp = entry;
			entry = entry->next;
			libc.free(tmp);
		}
	}
	libc.memset(s_wrap_cache, 0, sizeof(s_wrap_cache));
	libc.wrap_cache = 0;
}

void setup_wrap_cache(void)
{
	if (libc.wrap_cache)
		return;
	libc.wrap_cache = 1;

	memset(&s_wrap_cache, 0, sizeof(s_wrap_cache));

	/* setup all known functions we want to wrap */
	add_entry("__fork", handle_fork, 1, 0);
	add_entry("__open", handle_open, 1, 0);
	add_entry("__openat", handle_openat, 1, 0);
	add_entry("__sclose", handle_closefptr, 1, 0);
	add_entry("_exit", handle_exit, 1, 0);
	add_entry("accept", handle_accept, 1, 0);
	add_entry("bsd_signal", handle_signal, 1, 0);
	add_entry("close", handle_closefd, 1, 0);
	add_entry("dup", handle_dup, 1, 0);
	add_entry("dup2", handle_dup, 1, 0);
	add_entry("exit", handle_exit, 1, 0);
	add_entry("exec", handle_exec, 1, 0);
	add_entry("fclose", handle_closefptr, 1, 0);
	add_entry("fork", handle_fork, 1, 0);
	add_entry("fopen", handle_fopen, 1, 0);
	add_entry("freopen", handle_fopen, 1, 0);
	add_entry("open", handle_open, 1, 0);
	add_entry("openat", handle_openat, 1, 0);
	add_entry("pclose", handle_closefptr, 1, 0);
	add_entry("pipe", handle_pipe, 1, 0);
	add_entry("pipe2", handle_pipe, 1, 0);
	add_entry("popen", handle_pipe, 1, 0);
	add_entry("pthread_create", handle_pthread, 1, 0);
	add_entry("pthread_exit", handle_thread_exit, 1, 0);
	add_entry("sig_action", handle_sigaction, 1, 0);
	add_entry("signal", handle_signal, 1, 0);
	add_entry("socket", handle_socket, 1, 0);
	add_entry("socketpair", handle_socket, 1, 0);
	add_entry("sysv_signal", handle_signal, 1, 0);
	add_entry("vfork", handle_fork, 1, 0);

	/* setup functions we want to dynamically rename in the BT */
	add_entry("read", handle_read, 0, 1);
	add_entry("readv", handle_read, 0, 1);
	add_entry("pread64", handle_read, 0, 1);
	add_entry("write", handle_write, 0, 1);
	add_entry("writev", handle_write, 0, 1);
	add_entry("pwrite64", handle_write, 0, 1);
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
	struct ret_ctx *ret;

	ret = get_retmem();
	if (!ret)
		BUG_MSG(0x4311, "No TLS return value!");

	return ret->u.u32[0];
}

/*
 * Use a cache/table to modify info->symbol based on the function called and
 * its arguments. This allows us to track FDs through the system and mark
 * their access as network, FS, pipe, etc. by translating the symbol name to,
 * e.g., read_N (for network read).
 */
void wrap_symbol_mod(struct log_info *info)
{
	struct wrap_cache_entry *e;

	e = get_cached_sym(info);
	if (e && e->modsym)
		(void)e->handler(info);
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
int __attribute__((visibility("hidden")))
wrap_special(struct log_info *info)
{
	struct wrap_cache_entry *e;

	if (!info->symbol)
		return 0;

	e = get_cached_sym(info);
	if (e && e->wrapsym)
		return e->handler(info);

	return 0;
}

static void flush_and_close(const char *msg, struct log_info *info)
{
	void *f;

	if (info->should_log || libc.pthread_getspecific(log_key)) {
		f = get_log(1);
		if (!f)
			return;
		log_print(f, LOG, "I:%s %s(0x%x,0x%x,0x%x,0x%x)", msg,
			  info->symbol, info->regs[0], info->regs[1],
			  info->regs[2], info->regs[3]);
		if (zlib.valid) {
			zlib.gzflush((struct gzFile *)f, Z_FINISH);
			zlib.gzclose_w((struct gzFile *)f);
		} else {
			libc.fflush((FILE *)f);
			libc.fclose((FILE *)f);
		}
	}
}

int handle_exit(struct log_info *info)
{
	clear_retmem(0);
	flush_and_close("EXIT", info);
	close_dvm_iface(&dvm, 0);
	bt_free_log_buffer(0);
	bt_flush_cache(0);
	return 0;
}

int handle_thread_exit(struct log_info *info)
{
	clear_retmem(0);
	flush_and_close("THREAD_EXIT", info);
	bt_free_log_buffer(0);
	bt_flush_cache(0);
	return 0;
}

int handle_fork(struct log_info *info)
{
	clear_retmem(1);
	clear_tracing(1);
	clear_wrap_cache(info);
	flush_and_close("FORK", info);
	close_dvm_iface(&dvm, 1);
	bt_free_log_buffer(1);
	bt_flush_cache(1);
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

static void setup_exec_env(void)
{
	const char *ld_preload = LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME);
	libc.setenv("LD_PRELOAD", ld_preload, 1);
	/* libc_log("I:New LD_PRELOAD value '%s'", ld_preload); */
	/* libc.setenv("LD_DEBUG", "3", 1); */
}

int handle_exec(struct log_info *info)
{
	if (local_strcmp("execle", info->symbol) == 0)
		libc_log("E:No support for execle!");

	if (local_strcmp("execve", info->symbol) == 0)
		info->regs[2] = (uint32_t)wrap_environ((const char **)info->regs[2]);
	else
		setup_exec_env();

	if (info->should_log)
		libc_log("I:%s:%s:", info->symbol, (const char *)info->regs[0]);

	clear_retmem(1);
	clear_tracing(1);
	clear_wrap_cache(info);

	if (libc.pthread_getspecific(log_key))
		libc_close_log();
	close_dvm_iface(&dvm, 1);
	bt_flush_cache(1);
	bt_free_log_buffer(1);

	return 0;
}

int handle_pthread(struct log_info *info)
{
	clear_retmem(0);
	flush_and_close("PTHREAD", info);
	close_dvm_iface(&dvm, 0);
	bt_free_log_buffer(0);
	bt_flush_cache(0);
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
	void *logf;
	char *buf;

	logf = get_log(0);
	buf = libc.pthread_getspecific(s_log_buffer_key);
	if (buf && logf) {
		int *log_pos = (int *)(buf + LOG_BUFFER_SIZE);
		if (*log_pos > 0) {
			if (zlib.valid)
				zlib.gzwrite((struct gzFile *)logf, buf, *log_pos);
			else
				libc.fwrite(buf, *log_pos, 1, (FILE *)logf);
			*log_pos = 0;
		}
	}

	log_flush(logf);
}

static void wrapped_sighandler(int sig, struct siginfo *siginfo, void *ctx)
{
	sighandler_func sh;

	/*
	 * put this in a separate scope in order to call the
	 * original function with as little additional stack
	 * usage as possible.
	 */
	if (should_log()) {
		FILE *logf;
		struct timeval tv;

		libc.gettimeofday(&tv, NULL);
		logf = get_log(0);
		if (logf)
			__log_print(&tv, logf, "SIG", "RCV:%d:%s:",
				    sig, signame(sig));

	}

	if (sig >= MAX_SIGNALS)
		return; /* I guess we eat this one... */

	if (sig == s_special_sig) {
		__flush_btlog();
		libc.fflush(NULL); /* flush the entire process' buffers */
		if (libc.pthread_getspecific(log_key)) {
			libc_log("CAUGHT_SIGNAL:%d:%s:", sig, signame(sig));
			libc_close_log();
		}
	}

	/* NOTE: siginfo and ctx may be invalid! */
	if (s_sighandler[sig])
		(s_sighandler[sig])(sig, siginfo, ctx);
}

/*
 * 'orig' should be a valid function pointer
 */
static int install_sighandler(struct log_info *info,
			      int sig, sighandler_func orig)
{
	if (info->should_log) {
		Dl_info dli;
		if (dladdr((void *)orig, &dli)) {
			__log_print(&info->tv, get_log(0),
				    "SIG", "HANDLE:%s[%p](%s@%p):%d:%s:",
				    dli.dli_sname ? dli.dli_sname : "??",
				    (void *)orig,
				    dli.dli_fname ? dli.dli_fname : "xx",
				    dli.dli_fbase ? dli.dli_fbase : (void *)0,
				    sig, signame(sig));
		} else {
			__log_print(&info->tv, get_log(0),
				    "SIG", "HANDLE:[%p]:%d:%s:",
				    (void *)orig, sig, signame(sig));
		}
	}
	if (sig < MAX_SIGNALS)
		s_sighandler[sig] = orig;
	return 0;
}

int handle_signal(struct log_info *info)
{
	sighandler_func sh = NULL;

	sh = (sighandler_func)(info->regs[1]);
	if (sh == NULL ||
	    sh == (sighandler_func)SIG_IGN ||
	    sh == (sighandler_func)SIG_DFL ||
	    sh == (sighandler_func)SIG_ERR)
		return 0;

	if (install_sighandler(info, (int)info->regs[0], sh) == 0)
		info->regs[1] = (uint32_t)wrapped_sighandler;

	return 0;
}

void setup_special_sighandler(int sig)
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

int handle_sigaction(struct log_info *info)
{
	struct sigaction *sa;
	sighandler_func sh = NULL;

	sa = (struct sigaction *)(info->regs[1]);
	if (!sa)
		return 0;

	sh = (sighandler_func)(sa->sa_sigaction);
	if (sh == NULL ||
	    sh == (sighandler_func)SIG_IGN ||
	    sh == (sighandler_func)SIG_DFL ||
	    sh == (sighandler_func)SIG_ERR)
		return 0;

	if (install_sighandler(info, (int)info->regs[0], sh) == 0)
		sa->sa_sigaction = (sigaction_func)wrapped_sighandler;

	return 0;
}

static inline char __get_path_type(const char *path)
{
	char type = 'F'; /* default to standard file system type */

	if (!path)
		return '\0';
	/*
	 * Set the fd type based on the path the caller is trying to open.
	 * /dev/ paths get their own type as to /proc and /sys
	 */
	if (local_strncmp("/dev/", path, 5) == 0)
		type = 'D';
	else if (local_strncmp("/proc/", path, 6) == 0)
		type = 'K';
	else if (local_strncmp("/sys/", path, 5) == 0)
		type = 'K';

	/*
	 * TODO: theoretically, we should parse /proc/mounts here
	 *       just in case the caller is accessing something on
	 *       a network-mounted device, e.g., NFS
	 */

	return type;
}

int handle_open(struct log_info *info)
{
	struct ret_ctx *ret;
	int rval;
	char type;
	const char *path = (const char *)info->regs[0];
	int (*openfunc)(const char *, int, int, int);

	/*
	 * handles:
	 * int open(const char *path, int flags, ...);
	 * int __open(const char *path, int flags, ...);
	 */
	openfunc = info->func;

	rval = openfunc(path, (int)info->regs[1],
			(int)info->regs[2], (int)info->regs[3]);

	if (rval >= 0) {
		char type = __get_path_type(path);
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d,%s)='%c'\n", rval, path, type);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}


int handle_openat(struct log_info *info)
{
	struct ret_ctx *ret;
	int rval;
	const char *path = (const char *)info->regs[1];
	int (*openfunc)(int, const char *, int);

	/*
	 * handles:
	 * int openat(int dirfd, const char *pathname, int flags);
	 * int __openat(int dirfd, const char *pathname, int flags);
	 */
	openfunc = info->func;

	rval = openfunc((int)info->regs[0], path, (int)info->regs[2]);

	if (rval >= 0) {
		char type = __get_path_type(path);
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d,%s)='%c'\n", rval, path, type);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_fopen(struct log_info *info)
{
	struct ret_ctx *ret;
	FILE *rval;
	const char *path = (const char *)info->regs[0];
	const char *mode = (const char *)info->regs[1];
	FILE *(*openfunc)(const char *, const char *, void *);

	/*
	 * handles:
	 * FILE *fopen(const char *path, const char *mode);
	 * FILE *freopen(const char *path, const char *mode, FILE *stream);
	 */
	openfunc = info->func;

	rval = openfunc(path, mode, (void *)info->regs[2]);

	if (rval) {
		char type = __get_path_type(path);
		int fd = libc.fno(rval);
		set_fdtype(fd, type);
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d,%s)='%c'\n", fd, path, type);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = (uint32_t)rval;
	return 1;
}


int handle_dup(struct log_info *info)
{
	struct ret_ctx *ret;
	int oldfd, rval;
	char type;
	int (*dupfunc)(int, int);

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

	rval = dupfunc(oldfd, info->regs[1]);

	/* we duplicated the fd, so it's the same type as the oldfd */
	if (rval >= 0) {
		set_fdtype(rval, type);
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d)='%c'\n", rval, type);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_socket(struct log_info *info)
{
	struct ret_ctx *ret;
	int rval;
	int (*sockfunc)(int, int, int, int *);

	/*
	 * handles:
	 * int socket(int domain, int type, int protocol);
	 * int socketpair(int domain, int type, int protocol, int sv[2]);
	 */
	sockfunc = info->func;

	rval = sockfunc((int)info->regs[0], (int)info->regs[1],
			(int)info->regs[2], (int *)info->regs[3]);

	if (rval >= 0) {
		set_fdtype(rval, 'N');
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d)='N'\n", rval);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_pipe(struct log_info *info)
{
	struct ret_ctx *ret;
	int rval;
	int (*pipefunc)(int *, int);
	FILE *(*popenfunc)(const char *, const char *);

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
		rval = pipefunc(pfd, (int)info->regs[1]);
		if (rval == 0 && pfd) {
			set_fdtype(pfd[0], 'P');
			set_fdtype(pfd[1], 'P');
			if (info->should_log)
				bt_printf(info, "LOG:I:fds(%d,%d)='P'\n",
					  pfd[0], pfd[1]);
		}
	} else if (info->symbol[1] == 'o') {
		FILE *f;
		f = popenfunc((const char *)info->regs[0],
			      (const char *)info->regs[1]);
		if (f) {
			int fd = libc.fno(f);
			set_fdtype(fd, 'P');
			if (info->should_log)
				bt_printf(info, "LOG:I:fd(%d,%s)='P'\n",
					  fd, (const char *)info->regs[0]);
		}
		rval = (int)f;
	} else {
		/* don't handle this function */
		return 0;
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_accept(struct log_info *info)
{
	struct ret_ctx *ret;
	int rval;
	int (*acceptfunc)(int, void *, void *);

	/*
	 * handles:
	 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	 */
	acceptfunc = info->func;

	rval = acceptfunc((int)info->regs[0], (void *)info->regs[1],
			  (void *)info->regs[2]);

	if (rval >= 0) {
		set_fdtype(rval, 'N');
		if (info->should_log)
			bt_printf(info, "LOG:I:fd(%d)='N'\n", rval);
	}

	ret = get_retmem();
	ret->sym = info->symbol;
	ret->u.u32[0] = rval;
	return 1;
}

int handle_closefd(struct log_info *info)
{
	int fd;

	/* handle: close() */

	fd = (int)info->regs[0];

	mtx_lock(&fdtable_mutex);
	if (fd < fdtable_sz)
		fdtable[fd] = 0; /* it's now closed */
	mtx_unlock(&fdtable_mutex);
	return 0;
}

int handle_closefptr(struct log_info *info)
{
	FILE *f;
	int fd;

	/* handle: fclose(), pclose(), __sclose() */

	f = (FILE *)info->regs[0];
	fd = libc.fno(f);

	mtx_lock(&fdtable_mutex);
	if (fd < fdtable_sz)
		fdtable[fd] = 0; /* it's now closed */
	mtx_unlock(&fdtable_mutex);

	return 0;
}

int handle_read(struct log_info *info)
{
	return 0;
}

int handle_write(struct log_info *info)
{
	return 0;
}
