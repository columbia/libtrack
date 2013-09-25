/*
 * wrap_start.h
 * Copyright (C) 2012-2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Instantiate wrapper entry points
 *
 */
#ifndef WRAP_START_H
#define WRAP_START_H

#ifndef __ASSEMBLY__
#error "This file should only be included in ARM assembly files"
#endif

#include "wrap.S"

#define WRAP_LIB(LIBNM, LIBPATH) \
	wrap_lib LIBNM, LIBPATH

#define WRAP_FUNC(LIBNM, FUNC) \
	wrap_func LIBNM, FUNC

#define CUSTOM_WRAP_FUNC(LIBNM, FUNC, PREFIX) \
	wrap_func LIBNM, FUNC, PREFIX

#define PASS_FUNC(LIBNM, FUNC) \
	pass_func LIBNM, FUNC

#endif /* WRAP_START_H */
