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

static int g_log_fd = -1;
static struct libc_iface libc;

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
	if (!libc.dso)
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			goto out_noerrno;
	if (get_errno(&libc) & 0x20000000)
		return;
	/* TODO: setup TLS value via pthread_setspecific! */
	mod_errno(&libc, |=, 0x20000000);

	if (g_log_fd < 0) {
		if (init_libc_iface(&libc, LIBC_PATH) < 0)
			goto out;
		g_log_fd = libc.open(LOGFILE_PATH, O_CREAT | O_APPEND | O_CLOEXEC);
		mod_errno(&libc, |=, 0x20000000);
		if (g_log_fd < 0)
			goto out;
	}

	/*
	 * TODO: perform backtrace here
	 */
	len = libc.snprintf(buf, sizeof(buf), "%s\n", symbol);
	libc.write(g_log_fd, buf, len);
out:
	mod_errno(&libc, &=, 0x20000000);
out_noerrno:
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
	init_sym(iface, snprintf);
	init_sym(iface, errno);
	init_sym(iface, __errno);

	if (!iface->open || !iface->write || !iface->snprintf)
		return -1;
	if (!iface->errno && !iface->__errno)
		return -1;

	mod_errno(iface, |=, 0x20000000);
	return 0;
}

