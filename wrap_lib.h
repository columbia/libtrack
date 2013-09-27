/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#if defined(ANDROID)
#define LIBC_PATH "/system/lib/libc_real.so"
#define LOGFILE_PATH "/data/local/tmp/syscalls.log"
#elif defined(__APPLE__)
#define LIBC_PATH "/usr/lib/system/libsystem_kernel_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#else
#define LIBC_PATH "/lib/libc_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#endif

#include <stdio.h>

struct libc_iface {
	void *dso;

	int (*open)(const char *pathname, int flags);
	ssize_t (*write)(int fd, const void *buf, size_t count);
	int (*fflush)(FILE *stream);

	int (*snprintf)(char *str, size_t size, const char *format, ...);
};

extern int init_libc_iface(struct libc_iface *iface, const char *dso_path);

#endif
