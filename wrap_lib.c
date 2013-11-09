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

#include "wrap_lib.h"

const char *progname = NULL;

/* from backtrace.c */
extern void log_backtrace(void *logf, struct log_info *info);

/* lib-specific wrapping handlers (e.g. [v]fork in libc) */
#ifdef HAVE_WRAP_SPECIAL
extern int wrap_special(struct log_info *info);
#else
static inline int wrap_special(struct log_info *info)
{
	(void)info;
	return 0;
}
#endif

const char __attribute__((visibility("hidden")))
* local_strrchr(const char *str, int c)
{
	const char *s = str;
	while (*s++);
	while (--s > str)
		if ((int)*s == c)
			return s;
	return NULL;
}

int __attribute__((visibility("hidden")))
local_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int __attribute__((visibility("hidden")))
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

struct libc_iface libc __attribute__((visibility("hidden")));

/*
 * Symbol table / information
 *
 */
#undef SAVED
#undef SYM
#define SAVED(addr,name) #name
#define SYM(addr,name)
static const char *wrapped_sym=
#include "real_syms.h"
;
#undef SAVED
#undef SYM

#define SAVED(addr,name)
#define SYM(addr,name) { #name, (unsigned long)(addr) },
struct symbol {
	const char *name;
	unsigned long offset;
} sym_table[] = {
#include "real_syms.h"
	{ NULL, 0 },
};

static Dl_info wrapped_dli;

pthread_key_t s_wrapping_key __attribute__((visibility("hidden")));

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


pthread_key_t log_key = (pthread_key_t)(-1);

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
	log_print(logf, LOG, "BEGIN");
	libc.fflush(logf);
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
	zlib.gzsetparams(gzlogf, Z_BEST_COMPRESSION, Z_DEFAULT_STRATEGY);
	log_print(gzlogf, LOG, "BEGIN");
	zlib.gzflush(gzlogf, Z_FULL_FLUSH);
	return gzlogf;
}

void __attribute__((visibility("hidden"))) *get_log(int release)
{
	void *f;

	if (!libc.dso) {
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			_BUG(0x10);
		/*
		else
			setup_tls_stack(1, NULL, 0);
		 */
	}
	if (!zlib.dso)
		init_zlib_iface(&zlib, ZLIB_DFLT_PATH);

	if (log_key == (pthread_key_t)(-1)) {
		libc.pthread_key_create(&log_key, NULL);
		libc.pthread_setspecific(log_key, NULL);
	}

	f = libc.pthread_getspecific(log_key);
	if (!f) {
		if (zlib.valid) {
			f = (void *)__open_gzlogfile();
			if (!f) {
				zlib.valid = 0;
				f = (void *)__open_stdlogfile();
				log_print(f, LOG, "E:Failed to open libz!");
			}
		} else
			f = (void *)__open_stdlogfile();
		libc.pthread_setspecific(log_key, f);
	}
	if (release)
		libc.pthread_setspecific(log_key, NULL);
	return f;
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

static pthread_key_t s_tracing_key = (pthread_key_t)(-1);

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 *
 * @param symbol The symbol from which wrapped_tracer is being called
 * @param regs Pointer to saved register values
 * @param slots Number of register slots saved in @c regs
 * @param stack Pointer to the top of the stack at function entry
 */
int wrapped_tracer(const char *symbol, void *regs, int slots, void *stack)
{
	int ret = 0;
	void *logf;
	struct log_info li;

	if (!libc.dso) {
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			BUG(0x30);
		/*
		else
			setup_tls_stack((!regs && !stack), NULL, 0);
		 */
	}

	/* we're already tracing - disable recursive tracing! */
	if (libc.pthread_getspecific(s_tracing_key))
		return 0;
	libc.pthread_setspecific(s_tracing_key, (void *)1);

	li.symbol = symbol;
	li.regs = (uint32_t *)regs;
	li.slots = slots;
	li.stack = stack;
	li.tv.tv_sec = li.tv.tv_usec = 0;

	if (should_log()) {
		libc.gettimeofday(&li.tv, NULL);
		logf = get_log(0);
		if (!logf)
			goto out;
		if (!regs && !stack) {
			log_print(logf, CALL, "%s", symbol);
			log_flush(logf);
			goto out;
		}

		log_backtrace(logf, &li);
	} else if (libc.pthread_getspecific(log_key)) {
		libc.fflush(NULL); /* flush the entire process' logs */
		libc_close_log();
	}

	ret = wrap_special(&li);
out:
	(*__errno()) = 0; /* reset errno: libc functions could have set it! */
	libc.pthread_setspecific(s_tracing_key, NULL);
	return ret;
}

int init_libc_iface(struct libc_iface *iface, const char *dso_path)
{
	if (!iface->dso) {
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
	init_sym(iface, 1, pthread_key_create,);
	init_sym(iface, 1, pthread_getspecific,);
	init_sym(iface, 1, pthread_setspecific,);
	init_sym(iface, 1, snprintf,);
	init_sym(iface, 1, printf,);
	init_sym(iface, 1, fprintf,);
	init_sym(iface, 1, memset,);
	init_sym(iface, 1, memcpy,);
	init_sym(iface, 1, malloc,);
	init_sym(iface, 1, free,);
	init_sym(iface, 1, gettimeofday,);
	init_sym(iface, 1, setenv,);
	init_sym(iface, 1, getenv,);

	init_sym(iface, 0, strsignal,);

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

	if (s_tracing_key == (pthread_key_t)(-1)) {
		iface->pthread_key_create(&s_tracing_key, NULL);
		iface->pthread_setspecific(s_tracing_key, NULL);
	}

	return 0;
}

#if 0
void setup_tls_stack(int align, void *regs, int slots)
{
	static size_t CTX_SZ = PAGE_SIZE;
	void *mem, *stack_start;

	if (!s_wrapping_key)
		if (libc.pthread_key_create(&s_wrapping_key, NULL) != 0)
			return;
	mem = libc.pthread_getspecific(s_wrapping_key);
	if (mem) {
		libc.pthread_setspecific(s_wrapping_key, NULL);
		libc.free(mem);
	}

	/* setup space for the wrapping code to save register state */
	mem = libc.malloc(CTX_SZ);
	if (!mem)
		return;
	libc.memset(mem, 0, CTX_SZ);
	stack_start = (char *)mem + CTX_SZ - sizeof(void *);
	((uint32_t *)stack_start)[1] = 0x5a5a5a5a; /* "stack" canary */

	if (regs) {
		uint32_t *stk = (uint32_t *)stack_start;
		while (slots--)
			*stk-- = ((uint32_t *)regs)[slots];
		//libc.memcpy(stk, regs, slots * sizeof(*stk));
		stack_start = (void *)stk;
	}

	/* flag to let the assembly know we just set this up */
	if (!align)
		stack_start = (void *)((unsigned long)stack_start | 0x1);

	if (libc.pthread_setspecific(s_wrapping_key, stack_start) < 0) {
		libc.free(mem);
		return;
	}
}
#endif
