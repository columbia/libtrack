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

#define FUNC_START(TYPE, LIBNM, NAME,...) \
	TYPE ## _func_start LIBNM, NAME, ## __VA_ARGS__

#define FUNC_END(TYPE, LIBNM, NAME,...) \
	TYPE ## _func_end LIBNM, NAME, ## __VA_ARGS__

#define FUNC(NAME,...) \
	func_entry NAME, ## __VA_ARGS__

#define WRAP_LIB(LIBNM, LIBPATH) \
	wrap_lib LIBNM, LIBPATH

#define WRAP_FUNC(LIBNM, NAME) \
	FUNC_START(wrap, LIBNM, NAME); \
	FUNC_END(wrap, LIBNM, NAME)

#define WRAP_START(LIBNM, NAME) \
	FUNC_START(wrap, LIBNM, NAME)

#define WRAP_END(LIBNM, NAME) \
	FUNC_END(wrap, LIBNM, NAME)

#define CUSTOM_WRAP_FUNC(LIBNM, NAME, PREFIX) \
	FUNC_START(wrap, LIBNM, NAME, PREFIX); \
	FUNC_END(wrap, LIBNM, NAME, PREFIX)

#define PASS_FUNC(LIBNM, NAME) \
	FUNC_START(pass, LIBNM, NAME); \
	FUNC_END(pass, LIBNM, NAME)

#define PASS_START(LIBNM, NAME) \
	FUNC_START(pass, LIBNM, NAME)

#define PASS_END(LIBNM, NAME) \
	FUNC_END(pass, LIBNM, NAME)

#endif /* WRAP_START_H */
