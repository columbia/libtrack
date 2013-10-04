/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#include <stdio.h>
#include <pthread.h>
#include <unwind.h>
#include <sys/cdefs.h>

#if defined(ANDROID)
#	define LIB_PATH "/system/lib"
#	define LIBC_NAME "_ibc_so"
#	define LOGFILE_PATH "/data/local/tmp"
#elif defined(__APPLE__)
#	define LIB_PATH "/usr/lib/system"
#	define LIBC_NAME "_ibsystem_kernel_dylib"
#	define LOGFILE_PATH "/tmp"
#else
#	define LIB_PATH "/lib"
#	define LIBC_NAME "_ibc_so"
#	define LOGFILE_PATH "/tmp"
#endif

#define LIBC_PATH LIB_PATH "/" LIBC_NAME

#define _BUG(X) \
	do { \
		*((volatile int *)X) = X; \
	} while (0)

__BEGIN_DECLS

#ifdef HAVE_UNWIND_CONTEXT_STRUCT
typedef struct _Unwind_Context __unwind_context;
#else
typedef _Unwind_Context __unwind_context;
#endif
typedef _Unwind_Reason_Code (*bt_func)(__unwind_context* context, void* arg);


struct libc_iface {
	void *dso;

	FILE *(*fopen)(const char *pathname, const char *mode);
	int (*fclose)(FILE *f);
	ssize_t (*fwrite)(const void *buf, size_t size, size_t nitems, FILE *f);
	int (*fno)(FILE *f);

	pid_t (*getpid)(void);
	uint32_t (*gettid)(void);

	int (*pthread_key_create)(pthread_key_t *key, void (*destructor)(void *));
	void *(*pthread_getspecific)(pthread_key_t key);
	int (*pthread_setspecific)(pthread_key_t key, const void *val);

	int (*snprintf)(char *str, size_t size, const char *format, ...);
	int (*printf)(const char *fmt, ...);
	int (*fprintf)(FILE *f, const char *fmt, ...);

	void *(*memset)(void *b, int c, size_t len);
	void *(*malloc)(size_t size);
	void (*free)(void *ptr);

	/* backtrace interface */
	int (*backtrace)(void **buffer, int size);
	char ** (*backtrace_symbols)(void *const *buffer, int size);

	/* unwind interface */
	uintptr_t (*_Unwind_GetIP)(__unwind_context *ctx);
#ifdef __arm__
	_Unwind_VRS_Result (*_Unwind_VRS_Get)(_Unwind_Context *context,
					      _Unwind_VRS_RegClass regclass,
					      uint32_t regno,
					      _Unwind_VRS_DataRepresentation representation,
					      void *valuep);
#endif
	uintptr_t (*_Unwind_Backtrace)(bt_func func, void *arg);
};

extern int init_libc_iface(struct libc_iface *iface, const char *dso_path);

extern void *wrapped_dlsym(const char *libpath, void **lib_handle, const char *symbol);

extern void wrapped_tracer(const char *symbol);

__END_DECLS
#endif
