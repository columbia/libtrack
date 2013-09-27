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

static struct libc_iface libc = {
	.dso = NULL,
	.open = NULL,
	.write = NULL,
	.fflush = NULL,
	.snprintf = NULL,
};

static int get_logfd(void)
{
	static int s_log_fd = -1;
	if (s_log_fd < 0) {
		if (!libc.dso)
			if (init_libc_iface(&libc, LIBC_PATH) < 0)
				return -1;
		s_log_fd = libc.open(LOGFILE_PATH, O_CREAT | O_APPEND | O_CLOEXEC);
		if (s_log_fd < 0)
			return -1;
	}
	return s_log_fd;
}

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
	int fd;
	void *sym;

	fd = get_logfd();
	if (fd >= 0) {
		int len;
		char buf[256];
		len = libc.snprintf(buf, sizeof(buf),
				    "lib:%s,handle:%p(%p),sym:%s\n", libpath,
				    lib_handle, lib_handle ? *lib_handle : NULL,
				    symbol);
		libc.write(fd, buf, len);
		libc.fflush(NULL);
	} else {
		*((volatile int *)0) = 1;
	}

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

/**
 * @wrapped_tracer Default tracing function that stores a backtrace
 * @param symbol The symbol from which wrapped_tracer is being called
 *
 */
void wrapped_tracer(const char *symbol)
{
	int len, fd;
	char buf[128];

	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			goto out_crash;
	/* quick check for recursive calls */
	if (errno & 0x20000000)
		return;
	/* TODO: setup TLS value via pthread_setspecific! */
	errno |= 0x20000000;

	fd = get_logfd();
	if (fd < 0)
		goto out;
	errno |= 0x20000000;

	/*
	 * TODO: perform backtrace here
	 */
	len = libc.snprintf(buf, sizeof(buf), "%s\n", symbol);
	libc.write(fd, buf, len);
	libc.fflush(NULL);
out:
	errno &= 0x20000000;
	return;

out_crash:
	*((volatile int *)0) = 1;
	return;
}

int init_libc_iface(struct libc_iface *iface, const char *dso_path)
{
	if (!iface->dso) {
		iface->dso = dlopen(dso_path, RTLD_NOW | RTLD_LOCAL);
		if (!iface->dso)
			return -1;
	}
#define init_sym(iface,sym) \
	if (!(iface)->sym) \
		(iface)->sym = dlsym((iface)->dso, #sym)

	init_sym(iface, open);
	init_sym(iface, write);
	init_sym(iface, fflush);
	init_sym(iface, snprintf);

	if (!iface->open || !iface->write || !iface->snprintf)
		return -1;

	errno |= 0x20000000;
	return 0;
}

