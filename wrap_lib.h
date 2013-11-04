/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#include <dlfcn.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <unwind.h>
#include <sys/cdefs.h>

#define ___str(x) #x
#define __str(x) ___str(x)
#define _str(x) __str(x)

#define EN_LOG_FILE "enable_trace_logs"

#if defined(ANDROID)
#  define LIB_PATH "/system/lib"
#  if defined(_LIBC) && _LIBC == 1
#    define LIBC_NAME "_ibc_so"
#  else
#    define LIBC_NAME "libc.so"
#  endif
#  define LOGFILE_PATH "/data/trace_logs"
#  define ENABLE_LOG_PATH "/data/" EN_LOG_FILE
#elif defined(__APPLE__)
#  define LIB_PATH "/usr/lib/system"
#  if defined(_LIBC) && _LIBC == 1
#    define LIBC_NAME "_ibc_dylib"
#  else
#    define LIBC_NAME "libc.dylib"
#  endif
#  define LOGFILE_PATH "/tmp/trace_logs"
#  define ENABLE_LOG_PATH "/tmp/" EN_LOG_FILE
#else
#  define LIB_PATH "/lib"
#  if defined(_LIBC) && _LIBC == 1
#    define LIBC_NAME "_ibc_so"
#  else
#    define LIBC_NAME "_ibc_so"
#  endif
#  define LOGFILE_PATH "/tmp/trace_logs"
#  define ENABLE_LOG_PATH "/tmp/" EN_LOG_FILE
#endif

#define LIBC_PATH LIB_PATH "/" LIBC_NAME

#define _BUG(X) \
	do { \
		*((volatile int *)X) = X; \
	} while (0)

__BEGIN_DECLS

#if defined(HAVE_UNWIND_CONTEXT_STRUCT) || defined(__clang__)
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
	int (*fflush)(FILE *f);
	int (*fno)(FILE *f);
	int (*fchmod)(int fd, mode_t mode);
	int (*access)(const char *path, int amode);

	pid_t (*getpid)(void);
	uint32_t (*gettid)(void);

	int (*pthread_key_create)(pthread_key_t *key, void (*destructor)(void *));
	void *(*pthread_getspecific)(pthread_key_t key);
	int (*pthread_setspecific)(pthread_key_t key, const void *val);

	int (*snprintf)(char *str, size_t size, const char *format, ...);
	int (*printf)(const char *fmt, ...);
	int (*fprintf)(FILE *f, const char *fmt, ...);

	void *(*memset)(void *b, int c, size_t len);
	void *(*memcpy)(void *dst, void *src, size_t len);
	void *(*malloc)(size_t size);
	void (*free)(void *ptr);

	char *(*getenv)(const char *name);
	int (*setenv)(const char *name, const char *value, int overwrite);

	int (*gettimeofday)(struct timeval *tp, void *tzp);

	char *(*strsignal)(int sig);

	/* backtrace interface */
	int (*backtrace)(void **buffer, int size);
	char ** (*backtrace_symbols)(void *const *buffer, int size);

	/* unwind interface */
	uintptr_t (*_Unwind_GetIP)(__unwind_context *ctx);
#ifdef __arm__
	_Unwind_VRS_Result (*_Unwind_VRS_Get)(__unwind_context *context,
					      _Unwind_VRS_RegClass regclass,
					      uint32_t regno,
					      _Unwind_VRS_DataRepresentation representation,
					      void *valuep);
#endif
	uintptr_t (*_Unwind_Backtrace)(bt_func func, void *arg);
};

extern struct libc_iface libc;

extern int init_libc_iface(struct libc_iface *iface, const char *dso_path);

extern void *wrapped_dlsym(const char *libpath, void **lib_handle, const char *symbol);

extern int wrapped_tracer(const char *symbol, void *regs, int slots, void *stack);

extern void setup_tls_stack(int align, void *regs, int slots);

extern FILE *get_log(int release);

extern volatile int*  __errno(void);

struct log_info {
	const char *symbol;
	uint32_t *regs;
	int slots;
	void *stack;
	struct timeval tv;

	void **last_stack;
	int   *last_stack_depth;
	int   *last_stack_cnt;
};

#define __log_print_raw(tvptr, f, fmt, ...) \
	libc.fprintf(f, "%lu.%lu:" fmt, \
		     (unsigned long)(tvptr)->tv_sec, \
		     (unsigned long)(tvptr)->tv_usec, ## __VA_ARGS__ )

#define __log_print(tvptr, f, key, fmt, ...) \
	__log_print_raw(tvptr, f, key ":" fmt "\n", ## __VA_ARGS__ )

#define log_print(f, key, fmt, ...) \
	do { \
		struct timeval tv; \
		libc.gettimeofday(&tv, NULL); \
		__log_print(&tv, f, #key, fmt, ## __VA_ARGS__ ); \
	} while (0)

#define libc_log(fmt, ...) \
	do { \
		FILE *f; \
		f = get_log(0); \
		if (f) \
			log_print(f, LOG, fmt, ## __VA_ARGS__ ); \
	} while (0)

#define lnk_dbg(msg) \
	do { \
		extern void *real_libc_dso; \
		(void)dlsym(real_libc_dso, "LOG:" msg); \
	} while (0)

static inline void libc_close_log(void)
{
	FILE *f;
	f = get_log(1);
	if (f) {
		log_print(f, LOG, "END");
		libc.fflush(f);
		libc.fclose(f);
	}
}

static inline void libc_close_iface(void)
{
	if (!libc.dso)
		return;
	libc_close_log();
	dlclose(libc.dso);
	libc.dso = NULL;
}

static inline int should_log(void)
{
	int r = libc.access(ENABLE_LOG_PATH, F_OK) == 0;
	(*__errno()) = 0;
	return r;
}

__END_DECLS
#endif
