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

extern const char *__progname;

static struct libc_iface libc;

#define _BUG(X) \
	do { \
		*((volatile int *)X) = X; \
	} while (0)

static FILE *get_log(void)
{
	static pthread_key_t log_key = (pthread_key_t)(-1);
	FILE *logf = NULL;

	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			_BUG(0x10);

	if (log_key == (pthread_key_t)(-1))
		libc.pthread_key_create(&log_key, NULL);

	logf = (FILE *)libc.pthread_getspecific(log_key);
	if (!logf) {
		char buf[256];
		libc.snprintf(buf, sizeof(buf), "%s/%d.%d.%s.log",
			      LOGFILE_PATH, libc.getpid(), libc.gettid(), __progname);
		/* libc.printf("Creating logfile: %s\n", buf); */
		logf = libc.fopen(buf, "a+");
		/* libc.printf("\topen=%d\n", libc.fno(logf)); */
		if (!logf)
			return NULL;
		libc.fprintf(logf, "STARTED %d\n", libc.fno(logf));
		libc.pthread_setspecific(log_key, logf);
	}
	return logf;
}

#define libc_log(fmt, ...) \
	do { \
		FILE *f; \
		f = get_log(); \
		if (!f) \
			_BUG(0x99); \
		libc.fprintf(f, fmt "\n", ## __VA_ARGS__ ); \
		/* libc.printf("\tLOG:%d: " fmt "\n", libc.fno(f),  ## __VA_ARGS__); */ \
	} while (0)

#define BUG(X) \
	do { \
		FILE *f; \
		f = get_log(); \
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

	libc_log("lib:%s,handle:%p(%p),sym:%s", libpath, lib_handle,
		 lib_handle ? *lib_handle : NULL, symbol);

	if (!lib_handle)
		BUG(0x21);

	if (!*lib_handle) {
		*lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);
		if (!*lib_handle)
			BUG(0x22);
	}

	sym = dlsym(*lib_handle, symbol);
	if (!sym)
		BUG(0x23);
	return sym;
}

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 * @param symbol The symbol from which wrapped_tracer is being called
 *
 */
void wrapped_tracer(const char *symbol)
{
	static pthread_key_t wrap_key = (pthread_key_t)(-1);
	uint32_t wrapping = 0;
	char buf[128];

	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			BUG(0x30);
	if (wrap_key == (pthread_key_t)(-1)) {
		libc.pthread_key_create(&wrap_key, NULL);
		libc.pthread_setspecific(wrap_key, (const void *)0);
	}

	/* quick check for recursive calls */
	wrapping = (uint32_t)libc.pthread_getspecific(wrap_key);
	if (wrapping)
		return;
	libc.pthread_setspecific(wrap_key, (const void *)1);

	/*
	 * TODO: perform backtrace here
	 */
	libc_log("%s", symbol);

	libc.pthread_setspecific(wrap_key, (const void *)0);
	return;
}

int init_libc_iface(struct libc_iface *iface, const char *dso_path)
{
	if (!iface->dso) {
		iface->dso = dlopen(dso_path, RTLD_NOW | RTLD_LOCAL);
		if (!iface->dso)
			BUG(0x1);
	}
#define init_sym(iface,sym,alt) \
	if (!(iface)->sym) { \
		(iface)->sym = (typeof ((iface)->sym))dlsym((iface)->dso, #sym); \
		if (!(iface)->sym) {\
			(iface)->sym = (typeof ((iface)->sym))dlsym((iface)->dso, #alt); \
			if (!(iface)->sym) \
				BUG(0x2); \
		} \
	}

	init_sym(iface, fopen,);
	init_sym(iface, fclose,);
	init_sym(iface, fwrite,);
	init_sym(iface, fno, fileno);
	init_sym(iface, getpid,);
	init_sym(iface, gettid, __thread_selfid);
	init_sym(iface, pthread_key_create,);
	init_sym(iface, pthread_getspecific,);
	init_sym(iface, pthread_setspecific,);
	init_sym(iface, snprintf,);
	init_sym(iface, printf,);
	init_sym(iface, fprintf,);

	return 0;
}

