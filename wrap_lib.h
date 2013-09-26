/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#if defined(ANDROID)
#define LIBC_PATH "/system/lib/libc_real.so"
#define LOGFILE_PATH "/data/local/syscalls.log"
#elif defined(__APPLE__)
#define LIBC_PATH "/usr/lib/system/libsystem_kernel_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#else
#define LIBC_PATH "/lib/libc_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#endif

#ifdef errno
#undef errno
#endif

struct libc_iface {
	void *dso;

	int (*open)(const char *pathname, int flags);
	ssize_t (*write)(int fd, const void *buf, size_t count);
	int (*snprintf)(char *str, size_t size, const char *format, ...);

	int *errno;
	int * (*__errno)(void);
};

extern int init_libc_iface(struct libc_iface *iface, const char *dso_path);

#define get_errno(libc) \
	((libc)->errno ? *(libc)->errno : \
	 ((libc)->__errno ? *((libc)->__errno()) : *((int *)0)))

#define mod_errno(libc, op, val) \
	do { \
		if ((libc)->errno) \
			*(libc)->errno op val; \
		else if ((libc)->__errno) \
			*((libc)->__errno()) op val; \
	} while (0)

#define set_errno(libc, val) \
	mod_errno(libc, =, val)

#endif
