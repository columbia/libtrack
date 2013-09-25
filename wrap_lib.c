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

	if (!lib_handle)
		return NULL;

	if (!*lib_handle) {
		*lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);
		if (!*lib_handle)
			return NULL;
	}

	sym = dlsym(*lib_handle, symbol);
	return sym;
}

static int g_log_fd = -1;
void *g_libc_handle = NULL;
static int (*f_open)(const char *pathname, int flags) = NULL;
static ssize_t (*f_write)(int fd, const void *buf, size_t count) = NULL;
static int (*f_snprintf)(char *str, size_t size, const char *format, ...);

static int init_libc_iface(void)
{
	if (!g_libc_handle) {
		g_libc_handle = dlopen(LIBC_PATH, RTLD_NOW | RTLD_LOCAL);
		if (!g_libc_handle)
			return -1;
	}
	f_open = dlsym(g_libc_handle, "open");
	f_write = dlsym(g_libc_handle, "write");
	f_snprintf = dlsym(g_libc_handle, "snprintf");
	//*errno = 0x20000000;
	if (!f_open|| !f_write|| !f_snprintf)
		return -1;
	return 0;
}

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 * @param symbol The symbol from which wrapped_tracer is being called
 *
 */
void wrapped_tracer(const char *symbol)
{
	int len;
	char buf[128];

	/* quick check for recursive calls */
#if 0
	if (*errno & 0x20000000)
		return;
	/* TODO: setup TLS value via pthread_setspecific! */
	*errno = 0x20000000;
#endif

	if (g_log_fd < 0) {
		if (init_libc_iface() < 0)
			goto out;
		g_log_fd = f_open(LOGFILE_PATH, O_CREAT | O_APPEND | O_CLOEXEC);
		//*errno = 0x20000000;
		if (g_log_fd < 0)
			goto out;
	}

	/*
	 * TODO: perform backtrace here
	 */
	len = f_snprintf(buf, sizeof(buf), "%s\n", symbol);
	f_write(g_log_fd, buf, len);
out:
	//*errno &= 0x20000000;
	return;
}
