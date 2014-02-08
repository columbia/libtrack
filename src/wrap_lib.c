/*
 * wrap_lib.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Glue to wrap up a library (including possibly libc) and trace certain
 * functions within that library.
 */
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include <asm/wrap_lib.h>

#include "wrap_lib.h"
#include "backtrace.h"
#include "java_backtrace.h"

/* from platform specific code */
extern void setup_wrap_cache(void);

/* lib-specific wrapping handlers (e.g. [v]fork in libc) */
#ifdef HAVE_WRAP_SPECIAL
extern int wrap_special(struct tls_info *tls);
#else
static inline int wrap_special(struct tls_info *tls)
{
	(void)info;
	return 0;
}
#endif

const char *progname = NULL;

const char __hidden
* local_strrchr(const char *str, int c)
{
	const char *s = str;
	while (*s++);
	while (--s > str)
		if ((int)*s == c)
			return s;
	return NULL;
}

int __hidden
local_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int __hidden
local_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return 0;
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return 0;
}

struct libc_iface libc __hidden;

#ifdef LIBC_DEBUG_LOCKING
static pthread_mutex_t libc_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
#endif

/*
 * Symbol table / information
 *
 */
#undef TEXT_SIZE
#undef SAVED
#undef SYM
#define TEXT_SIZE(size)
#define SAVED(addr,name) #name
#define SYM(addr,name)
static const char *wrapped_sym=
#include "real_syms.h"
;
#undef TEXT_SIZE
#undef SAVED
#undef SYM

#define TEXT_SIZE(size)
#define SAVED(addr,name)
#define SYM(addr,name) { #name, (unsigned long)(addr) },
struct symbol {
	const char *name;
	unsigned long offset;
} sym_table[] = {
#include "real_syms.h"
	{ NULL, 0 },
};
#undef TEXT_SIZE
#undef SAVED
#undef SYM

#define TEXT_SIZE(size) size
#define SAVED(addr,name)
#define SYM(addr,name)
static int wrapped_text_size =
#include "real_syms.h"
;
#undef TEXT_SIZE
#undef SAVED
#undef SYM

int cached_pid = 0;

static Dl_info wrapped_dli;
static Dl_info dl_dli;

/*
 * Is the given address within the TEXT section of our wrapped library?
 */
static int is_in_wrapped_text(unsigned long addr, const char *sym)
{
	unsigned long start, end;

	start = (unsigned long)wrapped_dli.dli_fbase;
	end = start + (unsigned long)wrapped_text_size;
	if (addr >= start && addr < end)
		return 1;

	return 0;
}

/*
 * Use our internal offset table to locate the symbol within the
 * given DSO handle.
 *
 */
static void *table_dlsym(void *dso, const char *sym, int allow_null)
{
	struct symbol *symbol;

	if (!wrapped_dli.dli_fbase) {
		void *sym;
		/* get the address of a symbol we know exists in the library */
		sym = dlsym(dso, wrapped_sym);
		if (!sym)
			SYMERR(0x1);
		if (dladdr(sym, &wrapped_dli) == 0)
			SYMERR(0x2);
	}

	for (symbol = &sym_table[0]; symbol->name; symbol++) {
		if (local_strcmp(symbol->name, sym) == 0)
			break;
	}
	if (!symbol->name) {
		if (allow_null)
			return NULL;
		else
			BUG_MSG(0x3, "Can't find '%s'!", sym);
	}

	return (void *)((char *)wrapped_dli.dli_fbase + symbol->offset);
}

static inline FILE *__open_stdlogfile()
{
	FILE *logf;
	char buf[256];
	const char *nm = local_strrchr(progname, '/');
	libc.snprintf(buf, sizeof(buf), "%s/%d.%d.%s.%s.log",
		      LOGFILE_PATH, libc.getpid(),
		      libc.gettid(), _str(_IBNAM_),
		      nm ? nm+1 : progname);
	logf = libc.fopen(buf, "a");
	if (!logf)
		return NULL;
	libc.fchmod(libc.fno(logf), 0666);
	return logf;
}

static inline struct gzFile *__open_gzlogfile(void)
{
	FILE *logf;
	struct gzFile *gzlogf;
	char buf[256];
	const char *nm = local_strrchr(progname, '/');
	libc.snprintf(buf, sizeof(buf), "%s/%d.%d.%s.%s.log.gz",
		      LOGFILE_PATH, libc.getpid(),
		      libc.gettid(), _str(_IBNAM_),
		      nm ? nm+1 : progname);
	logf = libc.fopen(buf, "a");
	if (!logf)
		return NULL;
	libc.fchmod(libc.fno(logf), 0666);
	gzlogf = zlib.gzdopen(libc.fno(logf), "ab");
	if (!gzlogf) {
		libc.fclose(logf);
		return NULL;
	}
	//zlib.gzsetparams(gzlogf, Z_BEST_COMPRESSION, Z_DEFAULT_STRATEGY);
	zlib.gzsetparams(gzlogf, Z_BEST_SPEED, Z_DEFAULT_STRATEGY);
	zlib.gzflush(gzlogf, Z_FULL_FLUSH);
	return gzlogf;
}

static void ___open_log(struct tls_info *tls, int acquire_new, void **logf)
{
	void *f;

	if (logf)
		*logf = NULL;

	if (!tls)
		return;
	if (libc.dso == (void *)1)
		return;
	if (!libc.dso) {
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			_BUG(0x10);
	}

	if (!zlib.dso)
		init_zlib_iface(&zlib, ZLIB_DFLT_PATH);

	f = tls->logfile;
	if (!f && acquire_new) {
		if (zlib.valid) {
			f = (void *)__open_gzlogfile();
			if (!f) {
				zlib.valid = 0;
				f = (void *)__open_stdlogfile();
				log_print(f, LOG, "E:Failed to open libz!");
			}
		} else
			f = (void *)__open_stdlogfile();

		tls->logfile = f;
		log_print(f, LOG, "BEGIN(%s)", lh_sym(tls->lh));
		log_flush(f);
	}

	if (logf)
		*logf = f;
}

static void *___get_log(int release, int acquire_new)
{
	struct tls_info *tls;
	void *f = NULL;

	if (acquire_new)
		tls = get_tls();
	else
		tls = peek_tls();
	if (!tls)
		return NULL;

	___open_log(tls, acquire_new, &f);

	if (release)
		tls->logfile = NULL;

	return f;
}

/* this version won't open a new log */
void __hidden *__get_log(int release)
{
	return ___get_log(release, 0);
}

/* this version _will_ open a new logfile */
void __hidden *get_log(int release)
{
	return ___get_log(release, 1);
}

void __hidden tls_release_logfile(struct tls_info *tls)
{
	void *f;

	if (!tls)
		return;

	f = tls->logfile;
	if (!f)
		return;

	bt_flush(tls, &tls->info);
	tls->logfile = NULL;


	log_print(f, LOG, "END(%s)", lh_sym(tls->lh));
	log_flush(f);
	log_close(f);
}

void __hidden libc_close_log(void)
{
	struct tls_info *tls;

	tls = get_tls();
	if (!tls || !tls->logfile)
		return;

	tls_release_logfile(tls);
}

/**
 * @wrapped_dlsym Locate a symbol within a library, possibly loading the lib.
 *
 * @param libpath Full path to the library in which symbol should be found
 * @param lib_handle Pointer to memory location to store loaded library handle
 * @param symbol String name of the symbol to be found in libpath
 *
 * This function is called whenever a library must be loaded, or whenever
 * a symbol must be located (within a given library)
 */
void *wrapped_dlsym(const char *libpath, void **lib_handle, const char *symbol)
{
	void *sym;

	if (!lib_handle)
		BUG(0x21);

	if (!*lib_handle) {
		*lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);
		if (!*lib_handle)
			BUG(0x22);
	}

	sym = table_dlsym(*lib_handle, symbol, 0);
	if (!sym)
		BUG(0x23);
	return sym;
}

#ifdef LIBC_DEBUG_LOCKING
static pthread_mutex_t th_mtx = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
static struct lock_holder s_th_array[MAX_TRACE_THREADS];

void __hidden __lh_clear(void)
{
	mtx_lock(&th_mtx);
	libc.memset(s_th_array, 0, sizeof(s_th_array));
	mtx_unlock(&th_mtx);
}

static inline struct lock_holder *__lh_lookup(int tid)
{
	int i;
	for (i = 0; i < MAX_TRACE_THREADS; i++) {
		if (lh_valid(&s_th_array[i]) && (int)s_th_array[i].tid == tid) {
			s_th_array[i].refcnt += 1;
			if (s_th_array[i].refcnt > 1) {
				libc_log("W:LIBC:sym(\"%s\") has recursively called libc from \"%s\" (refcnt=%d)",
					 symbol, s_th_array[i].sym, s_th_array[i].refcnt);
			}
			return &s_th_array[i]; /* alreay have one! */
		}
	}
	return NULL;
}

static inline struct lock_holder *__lh_new(const char *symbol, int fastlookup)
{
	int i, tid;
	struct lock_holder *lh;

	tid = libc.gettid();
	if (fastlookup) {
		lh = __lh_lookup(tid);
		if (lh)
			return lh;
	}

	mtx_lock(&th_mtx);
	for (i = 0; i < MAX_TRACE_THREADS; i++) {
		if (!lh_valid(&s_th_array[i])) {
			s_th_array[i].magic = LOCK_TRACE_MAGIC;
			s_th_array[i].next = s_th_array[i].prev = &s_th_array[i];
			s_th_array[i].tid = tid;
			s_th_array[i].sym = symbol;
			s_th_array[i].refcnt = 1;
			mtx_unlock(&th_mtx);
			return &s_th_array[i];
		}
	}
	mtx_unlock(&th_mtx);

	return NULL;
}

static void __lh_free(struct lock_holder *lh)
{
	if (!lh_valid(lh)) {
		void *f = get_log(0);
		libc_log("E:LIBC:Invalid lock_holder @%p!", lh);
		log_flush(f);
		return;
	}

	if (--(lh->refcnt) != 0) {
		void *f = get_log(0);
		libc_log("W:LIBC:someone still holding sym(\"%s\") lock, refcnt=%d",
			 lh->sym, lh->refcnt);
		log_flush(f);
	}
}
#else
void __hidden __lh_clear(void)
{
}
#endif /* LIBC_LOCK_DEBUGGING */

void __hidden tls_release_lh(struct tls_info *tls)
{
	trace_ptr_t lh;

	if (!tls)
		return;
	
	lh = tls->lh;
	if (!lh_valid(lh))
		return;

	tls->lh = NULL;

#ifdef LIBC_LOCK_DEBUGGING
	mtx_lock(&libc_mutex);
	lh_del(lh);
	mtx_unlock(&libc_mutex);
#endif

	lh_free(lh);
}

int __hidden __get_libc(struct tls_info *tls, const char *symbol)
{
	int i;
	trace_ptr_t lh;

	if (!tls)
		return 0;

	lh = tls->lh;

	/* we're already tracing - disable recursion */
	if (lh == (trace_ptr_t)1 || lh_valid(lh))
		return 0;

	tls->lh = (trace_ptr_t)1;

#ifdef LIBC_LOCK_DEBUGGING
	lh = __lh_lookup(libc.gettid());
	if (lh_valid(lh)) {
		void *f = get_log(0);
		libc_log("D:LIBC:(\"%s\") already held by \"%s\" (%d), how did we get here?!",
			 symbol,
			 lh_valid(lh) ? lh_sym(lh) : "<invalid>",
			 lh_valid(lh) ? lh_tid(lh) : (uint32_t)(-1));
		tls->lh = lh;
		return 0;
	}
#endif

	/* acquire a lock_holder structure and add to the list */
	lh = lh_new(symbol, 0);
	tls->lh = lh;

#ifdef LIBC_LOCK_DEBUGGING
	mtx_lock(&libc_mutex);
	lh_add(lh);
	mtx_unlock(&libc_mutex);
#endif

	return 1;
}

void __hidden __put_libc(void)
{
	tls_release_lh(peek_tls());
}

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 *
 * @param symbol The symbol from which wrapped_tracer is being called
 * @param symptr Pointer to the function symbol in the wrapped library
 * @param regs Pointer to saved register values
 * @param stack Pointer to the top of the stack at function entry
 */
int wrapped_tracer(const char *symbol, void *symptr, void *regs, void *stack)
{
	int did_wrap = 0, _err;
	struct tls_info *tls;

	if (!regs || !stack || !symbol)
		return 0;

	/* a libc function was called during libc init (probably from dlopen) */
	if (libc.dso == (void *)1)
		return 0;

	/*
	 * don't trace anything that originates from the wrapped library:
	 * this is an implementation detail, and we don't want it.
	 */
	if (is_in_wrapped_text(((uint32_t *)regs)[REG_LR_IDX], symbol))
		return 0;

	_err = *__errno();
	if (!libc.dso) {
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			BUG(0x31);
	}

	/* initialized once per process */
	setup_wrap_cache();

	tls = get_tls();
	if (!tls)
		return 0;

	if (!__get_libc(tls, symbol)) {
		(*__errno()) = _err;
		return 0;
	}

	tls->info.regs = (uint32_t *)regs;
	tls->info.symbol = symbol;
	tls->info.func = symptr;
	tls->info.stack = stack;
	tls->info.tv.tv_sec = tls->info.tv.tv_usec = 0;
	tls->info.symhash = 0;
	tls->info.symcache = NULL;

	tls->info.should_log = should_log();

	if (tls->info.should_log) {
		void *f;
		libc.gettimeofday(&tls->info.tv, NULL);
		init_dvm(&dvm);
		___open_log(tls, 1, &f);
		if (!f)
			goto out;
		log_backtrace(tls);
	} else if (tls->logfile) {
		/*
		 * We get here is we're not logging, but we have a logfile
		 * open. This happens when we disable tracing. We'll close
		 * the logfile to ensure consistent state.
		 */
		tls_release_logfile(tls);
	}

	/* perform any special actions */
	did_wrap = wrap_special(tls);

out:
	__put_libc();

	/*
	 * reset errno if we didn't wrap, if we _did_ wrap the wrapped_return
	 * function will handle the error value
	 */
	if (!did_wrap)
		(*__errno()) = _err;

	return did_wrap;
}

int __hidden init_libc_iface(struct libc_iface *iface, const char *dso_path)
{
	if (!iface->dso) {
		iface->dso = (void *)1; /* in case dlopen needs any libc symbols */
		iface->dso = dlopen(dso_path, RTLD_NOW | RTLD_LOCAL);
		if (!iface->dso)
			_BUG(0x40);
	}

#if defined(_LIBC) && _LIBC == 1
/*
 * if we're wrapping up libc, then we have to use the table_dlsym to find
 * entry points inside!
 */
#define __dlsym(x,y) table_dlsym(x, y, 1)
#else
#define __dlsym(x,y) dlsym(x, y)
#endif

#define init_sym(iface,req,sym,alt) \
	do { \
		if ((iface)->sym) \
			break; \
		(iface)->sym = (typeof ((iface)->sym))__dlsym((iface)->dso, #sym); \
		if ((iface)->sym) \
			break; \
		(iface)->sym = (typeof ((iface)->sym))__dlsym((iface)->dso, "_" #sym); \
		if ((iface)->sym) \
			break; \
		(iface)->sym = (typeof ((iface)->sym))__dlsym((iface)->dso, #alt); \
		if ((iface)->sym) \
			break; \
		(iface)->sym = (typeof ((iface)->sym))__dlsym((iface)->dso, "_" #alt); \
		if ((iface)->sym) \
			break; \
		if (req) \
			_BUG(0x41); \
	} while (0)

	init_sym(iface, 1, fopen,);
	init_sym(iface, 1, fclose,);
	init_sym(iface, 1, fwrite,);
	init_sym(iface, 1, fread,);
	init_sym(iface, 1, fflush,);
	init_sym(iface, 1, fno, fileno);
	init_sym(iface, 1, fchmod,);
	init_sym(iface, 1, access,);
	init_sym(iface, 1, getpid,);
	init_sym(iface, 1, gettid, __thread_selfid);
	init_sym(iface, 1, nanosleep,);
	init_sym(iface, 1, pthread_key_create,);
	init_sym(iface, 1, pthread_key_delete,);
	init_sym(iface, 1, pthread_getspecific,);
	init_sym(iface, 1, pthread_setspecific,);

#ifdef ANDROID
	init_sym(iface, 1, __pthread_cleanup_push,);
	init_sym(iface, 1, __pthread_cleanup_pop,);
#endif

	init_sym(iface, 0, pthread_mutex_lock,);
	init_sym(iface, 0, pthread_mutex_unlock,);

	init_sym(iface, 1, snprintf,);
	init_sym(iface, 1, printf,);
	init_sym(iface, 1, fprintf,);
	init_sym(iface, 1, strtol,);
	init_sym(iface, 1, memset,);
	init_sym(iface, 1, memcpy,);
	init_sym(iface, 1, malloc,);
	init_sym(iface, 1, free,);
	init_sym(iface, 1, gettimeofday,);
	init_sym(iface, 1, setenv,);
	init_sym(iface, 1, getenv,);

	init_sym(iface, 0, strsignal,);
	init_sym(iface, 0, sigaction,);

	init_sym(iface, 0, __cxa_finalize,);
	init_sym(iface, 0, raise,);
	init_sym(iface, 0, abort,);

	/* backtrace interface */
	init_sym(iface, 0, backtrace,);
	init_sym(iface, 0, backtrace_symbols,);

	/* unwind interface */
	init_sym(iface, 0, _Unwind_GetIP,);
#ifdef __arm__
	init_sym(iface, 0, _Unwind_VRS_Get,);
#endif
	init_sym(iface, 0, _Unwind_Backtrace,);

	if (!progname) {
		void *sym = dlsym(iface->dso, "__progname");
		if (sym)
			progname = *(const char **)sym;
	}

#undef init_sym

	iface->memset(&dvm, 0, sizeof(dvm));

#ifdef LIBC_DEBUG_LOCKING
	iface->lh.next = iface->lh.prev = &(iface->lh);
	iface->lh.tid = 0;
	iface->lh.sym = "[root]";
#endif
	return 0;
}

struct ret_ctx __hidden *get_retmem(struct tls_info *tls)
{
	if (!tls)
		tls = get_tls();
	if (!tls)
		return NULL;
	return &tls->ret;
}
