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

extern const char *progname; /* comes from real libc */

/* from backtrace.c */
extern void log_backtrace(FILE *logf, const char *sym,
			  uint32_t *regs, uint32_t *stack);

/* lib-specific wrapping handlers (e.g. [v]fork in libc) */
extern void wrap_special(const char *symbol, uint32_t *regs, uint32_t *stack);

int __attribute__((visibility("hidden")))
local_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
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
static void *table_dlsym(void *dso, const char *sym)
{
	struct symbol *symbol;

	if (!wrapped_dli.dli_fbase) {
		void *sym;
		/* get the address of a symbol we know exists in the library */
		sym = dlsym(dso, wrapped_sym);
		if (!sym)
			_BUG(0x1);
		if (dladdr(sym, &wrapped_dli) == 0)
			_BUG(0x2);
	}

	for (symbol = &sym_table[0]; symbol->name; symbol++) {
		if (local_strcmp(symbol->name, sym) == 0)
			break;
	}
	if (!symbol->name)
		return NULL;

	return (void *)((char *)wrapped_dli.dli_fbase + symbol->offset);
}

FILE __attribute__((visibility("hidden"))) *get_log(int release)
{
	static pthread_key_t log_key = (pthread_key_t)(-1);
	FILE *logf = NULL;

	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH, 0) < 0)
			_BUG(0x10);

	if (log_key == (pthread_key_t)(-1))
		libc.pthread_key_create(&log_key, NULL);

	logf = (FILE *)libc.pthread_getspecific(log_key);
	if (!logf) {
		char buf[256];
		struct timeval tv;
		libc.snprintf(buf, sizeof(buf), "%s/%d.%d.%s.log",
			      LOGFILE_PATH, libc.getpid(),
			      libc.gettid(), progname);
		logf = libc.fopen(buf, "a+");
		if (!logf)
			return NULL;
		libc.gettimeofday(&tv, NULL);
		libc.fprintf(logf, "BEGIN:%lu.%lu\n", (unsigned long)tv.tv_sec,
			     (unsigned long)tv.tv_usec);
		libc.fflush(logf);
		libc.pthread_setspecific(log_key, logf);
	}
	if (release)
		libc.pthread_setspecific(log_key, NULL);
	return logf;
}

#define BUG(X) \
	do { \
		FILE *f; \
		f = get_log(0); \
		if (f) { \
			libc_log("BUG(0x%x) at %s:%d\n", X, __FILE__, __LINE__); \
			libc.fclose(f); \
		} \
		_BUG(X); \
	} while (0)

/**
 * @wrapped_dlsym Locate a symbol within a library, possibly loading the lib.
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

	/*
	libc_log("lib:%s,handle:%p(%p),sym:%s", libpath, lib_handle,
		 lib_handle ? *lib_handle : NULL, symbol);
	 */
	if (!lib_handle)
		BUG(0x21);

	if (!*lib_handle) {
		*lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);
		if (!*lib_handle)
			BUG(0x22);
	}

	sym = table_dlsym(*lib_handle, symbol);
	if (!sym)
		BUG(0x23);
	return sym;
}

pthread_key_t wrap_key __attribute__((visibility("hidden"))) = (pthread_key_t)(-1);

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 * @param symbol The symbol from which wrapped_tracer is being called
 *
 */
void wrapped_tracer(const char *symbol, void *regs, void *stack)
{
	uint32_t wrapping = 0;
	int startup = (!regs && !stack);

	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH, startup) < 0)
			BUG(0x30);
	if (startup) {
		get_log(0); /* start the log file and exit (no backtrace) */
		return;
	}

	if (wrap_key == (pthread_key_t)(-1)) {
		libc.pthread_key_create(&wrap_key, NULL);
		libc.pthread_setspecific(wrap_key, (const void *)0);
	}

	/* quick check for recursive calls */
	wrapping = (uint32_t)libc.pthread_getspecific(wrap_key);
	if (wrapping)
		return;

	libc.pthread_setspecific(wrap_key, (const void *)1);

	log_backtrace(get_log(0), symbol, (uint32_t *)regs, (uint32_t *)stack);

	wrap_special(symbol, regs, stack);

	libc.pthread_setspecific(wrap_key, (const void *)0);
	return;
}

int init_libc_iface(struct libc_iface *iface, const char *dso_path, int align)
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
#define __dlsym table_dlsym
#else
#define __dlsym dlsym
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
	init_sym(iface, 1, fflush,);
	init_sym(iface, 1, fno, fileno);
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

	/* backtrace interface */
	init_sym(iface, 0, backtrace,);
	init_sym(iface, 0, backtrace_symbols,);

	/* unwind interface */
	init_sym(iface, 0, _Unwind_GetIP,);
#ifdef __arm__
	init_sym(iface, 0, _Unwind_VRS_Get,);
#endif
	init_sym(iface, 0, _Unwind_Backtrace,);


	/* TODO: refactor this into a function (to be called from special libc
	 * wrappers for functions like fork() and pthread_create()
	 */

	/* setup space for the wrapping code to save register state */
	if (!s_wrapping_key) {
		static size_t CTX_SZ = PAGE_SIZE;
		void *mem, *stack_start;

		mem = libc.malloc(CTX_SZ);
		if (!mem)
			return 0;
		libc.memset(mem, 0, CTX_SZ);
		stack_start = (char *)mem + CTX_SZ - sizeof(void *);
		/* flag to let the assembly know we just set this up */
		if (!align)
			stack_start = (void *)((unsigned long)stack_start | 0x1);
		libc.pthread_key_create(&s_wrapping_key, NULL);
		if (libc.pthread_setspecific(s_wrapping_key, stack_start) < 0) {
			libc.free(mem);
			return 0;
		}
	}

	return 0;
}

void close_libc_iface(void)
{
	FILE *f;
	struct timeval tv;

	if (!libc.dso)
		return;
	f = get_log(1);
	if (f) {
		libc.gettimeofday(&tv, NULL);
		libc.fprintf(f, "END:%lu.%lu\n", (unsigned long)tv.tv_sec,
			    (unsigned long)tv.tv_usec);
		libc.fflush(f);
		libc.fclose(f);
	}
	dlclose(libc.dso);
	libc.dso = NULL;
}
