/*
 * libz.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Glue to wrap up a library (including possibly libc) and trace certain
 * functions within that library.
 */
#include <dlfcn.h>
#include <sys/types.h>

#include "libz.h"
#include "wrap_lib.h"

struct zlib_iface zlib;


void init_zlib_iface(struct zlib_iface *zlib, const char *path)
{
	if (zlib->dso == (void *)1)
		return;

	if (!zlib->dso) {
		zlib->valid = 0;
		zlib->dso = (void *)1;
		zlib->dso = dlopen(path, RTLD_NOW | RTLD_LOCAL);
		if (!zlib->dso)
			_BUG(0x40);
	}

#define init_sym(zlib, sym) \
	do { \
		if ((zlib)->sym) \
			break; \
		(zlib)->sym = (typeof ((zlib)->sym))dlsym((zlib)->dso, #sym); \
		if ((zlib)->sym) \
			break; \
		(zlib)->sym = (typeof ((zlib)->sym))dlsym((zlib)->dso, "_" #sym); \
		if ((zlib)->sym) \
			break; \
		goto out_err; \
	} while (0)

	init_sym(zlib, gzdopen);
	init_sym(zlib, gzsetparams);
	init_sym(zlib, gzwrite);
	init_sym(zlib, gzprintf);
	init_sym(zlib, gzflush);
	init_sym(zlib, gzclose);

#undef init_sym

	zlib->valid = 1;
	return;

out_err:
	dlclose(zlib->dso);
	libc.memset(zlib, 0, sizeof(*zlib));
	zlib->dso = (void *)1; /* to prevent further init attempts */
}

void close_zlib_iface(struct zlib_iface *zlib)
{
	void *dso;
	if (!zlib->dso)
		return;

	dso = zlib->dso;
	libc.memset(zlib, 0, sizeof(*zlib));
	zlib->dso = (void *)1;
	dlclose(dso);
	zlib->dso = NULL;
}
