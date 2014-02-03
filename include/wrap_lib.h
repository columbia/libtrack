/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <unwind.h>
#include <sys/cdefs.h>

#include "libz.h"

#define ___str(x) #x
#define __str(x) ___str(x)
#define _str(x) __str(x)

#define ARRAY_SZ(arr) \
	(sizeof(arr) / sizeof((arr)[0]))

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

__BEGIN_DECLS

#if defined(HAVE_UNWIND_CONTEXT_STRUCT) || defined(__clang__)
typedef struct _Unwind_Context __unwind_context;
#else
typedef _Unwind_Context __unwind_context;
#endif
typedef _Unwind_Reason_Code (*bt_func)(__unwind_context* context, void* arg);


struct libc_iface {
	void *dso;
	int   wrap_cache;

	FILE *(*fopen)(const char *pathname, const char *mode);
	int (*fclose)(FILE *f);
	ssize_t (*fwrite)(const void *buf, size_t size, size_t nitems, FILE *f);
	ssize_t (*fread)(void *buf, size_t size, size_t nitems, FILE *f);
	int (*fflush)(FILE *f);
	int (*fno)(FILE *f);
	int (*fchmod)(int fd, mode_t mode);
	int (*access)(const char *path, int amode);

	pid_t (*getpid)(void);
	uint32_t (*gettid)(void);

	int (*pthread_key_create)(pthread_key_t *key, void (*destructor)(void *));
	int (*pthread_key_delete)(pthread_key_t key);
	void *(*pthread_getspecific)(pthread_key_t key);
	int (*pthread_setspecific)(pthread_key_t key, const void *val);

	int (*pthread_mutex_lock)(pthread_mutex_t *mutex);
	int (*pthread_mutex_unlock)(pthread_mutex_t *mutex);

	int (*snprintf)(char *str, size_t size, const char *format, ...);
	int (*printf)(const char *fmt, ...);
	int (*fprintf)(FILE *f, const char *fmt, ...);
	long (*strtol)(const char *str, char **endptr, int base);

	void *(*memset)(void *b, int c, size_t len);
	void *(*memcpy)(void *dst, const void *src, size_t len);
	void *(*malloc)(size_t size);
	void (*free)(void *ptr);

	char *(*getenv)(const char *name);
	int (*setenv)(const char *name, const char *value, int overwrite);

	int (*gettimeofday)(struct timeval *tp, void *tzp);

	int (*sigaction)(int sig, const struct sigaction *act,
			 struct sigaction *oact);
	char *(*strsignal)(int sig);

	void (*__cxa_finalize)(void *dso);
	int (*raise)(int sig);
	void (*abort)(void);

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

extern int setup_tls_retval(void);

extern void *wrapped_dlsym(const char *libpath, void **lib_handle, const char *symbol);

extern int wrapped_tracer(const char *symbol, void *symptr, void *regs, void *stack);

extern void *get_log(int release);

extern void __delete_pth_key(pthread_key_t *key);

extern volatile int*  __errno(void);

#define LOG_BUFFER_SIZE (66 * 1024)

struct log_info {
	const char *symbol;
	void *func;
	uint32_t *regs;
	void *stack;
	struct timeval tv;

	uint8_t should_log;
	uint8_t symhash;
	void *symcache;

	void **last_stack;
	int   *last_stack_depth;
	int   *last_stack_cnt;

	char  *log_buffer;
	int   *log_pos;
};

/*
 * TODO: this should probably be platform/arch specific...
 */
#define MAX_SYMBOL_LEN 256
struct ret_ctx {
	/* for now we'll have space for 4 32-bit registers */
	union {
		uint64_t u64[2];
		uint32_t u32[4];
		uint16_t u16[8];
		uint8_t  u8[16];
	} u;
	char symmod[MAX_SYMBOL_LEN];
	const char *sym;
};

extern void setup_retmem(void);
extern void clear_retmem(int release_key);
extern struct ret_ctx *get_retmem(void);

extern void setup_tracing(void);
extern void clear_tracing(int release_key);

#define mtx_lock(mtx) \
	if (libc.pthread_mutex_lock && libc.pthread_mutex_unlock) \
		libc.pthread_mutex_lock(mtx)

#define mtx_unlock(mtx) \
	if (libc.pthread_mutex_lock && libc.pthread_mutex_unlock) \
		libc.pthread_mutex_unlock(mtx)

#define __bt_printf(info, fmt, ...) \
do { \
	if ((info)->log_buffer && (*(info)->log_pos < LOG_BUFFER_SIZE)) { \
		int __len = libc.snprintf((info)->log_buffer + *(info)->log_pos, \
					  LOG_BUFFER_SIZE - *(info)->log_pos, \
					  fmt, ## __VA_ARGS__ ); \
		*(info)->log_pos += __len; \
	} else { \
		libc_log("E:Buffer overrun!"); \
	} \
} while (0)

#define bt_printf(info, fmt, ...) \
	__bt_printf(info, "%lu.%lu:" fmt, \
		    (unsigned long)((info)->tv.tv_sec), \
		    (unsigned long)((info)->tv.tv_usec), ## __VA_ARGS__ )

#define bt_flush(info, logf) \
	if (*((info)->log_pos) > 0) { \
		if (zlib.valid) \
			zlib.gzwrite((struct gzFile *)(logf), \
				     (info)->log_buffer, *(info)->log_pos); \
		else \
			libc.fwrite((info)->log_buffer, \
				    *((info)->log_pos), 1, (FILE *)(logf)); \
		*(info)->log_pos = 0; \
	}


#define __log_print_raw(tvptr, f, fmt, ...) \
	do { \
	if (zlib.valid) \
		zlib.gzprintf((struct gzFile *)(f), "%lu.%lu:" fmt, \
			     (unsigned long)(tvptr)->tv_sec, \
			     (unsigned long)(tvptr)->tv_usec, ## __VA_ARGS__ ); \
	else \
		libc.fprintf((FILE *)(f), "%lu.%lu:" fmt, \
			     (unsigned long)(tvptr)->tv_sec, \
			     (unsigned long)(tvptr)->tv_usec, ## __VA_ARGS__ ); \
	} while (0)

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
		void *f; \
		f = get_log(0); \
		if (f) \
			log_print(f, LOG, fmt, ## __VA_ARGS__ ); \
	} while (0)

#define log_flush(f) \
	do { \
	if (zlib.valid) \
		zlib.gzflush((struct gzFile *)(f), Z_SYNC_FLUSH); \
	else \
		libc.fflush((FILE *)f); \
	} while (0)

#define lnk_dbg(msg) \
	do { \
		extern void *real_libc_dso; \
		(void)dlsym(real_libc_dso, "LOG:" msg); \
	} while (0)

static inline void libc_close_log(void)
{
	void *f;
	f = get_log(1);
	if (f) {
		log_print(f, LOG, "END");
		if (zlib.valid) {
			zlib.gzflush((struct gzFile *)f, Z_FINISH);
			zlib.gzclose_w((struct gzFile *)f);
		} else {
			libc.fflush((FILE *)f);
			libc.fclose((FILE *)f);
		}
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

extern int cached_pid;

static inline int should_log(void)
{
	int r1;
	char buf[10];
	FILE *f;

	r1 = libc.access(ENABLE_LOG_PATH, F_OK) == 0;
	if (!r1){
		if (cached_pid)
			libc_close_log();
		cached_pid = 0;
		(*__errno()) = 0;
		return 0;
	}
	if (!cached_pid &&
	    (f=libc.fopen(ENABLE_LOG_PATH, "r")) != NULL){
		libc.fread(buf, 1, sizeof(buf), f);
		cached_pid = libc.strtol(buf, NULL, 10);
		if (!cached_pid)
			cached_pid = -1;
		libc.fclose(f);
	}

	(*__errno()) = 0;
	if (!cached_pid)
		return 0;
	if (cached_pid > 0)
		return libc.getpid() == cached_pid;
	return 1;
}

#define _BUG(X) \
	do { \
		if (libc.fflush) \
			libc.fflush(NULL); \
		*((volatile int *)X) = X; \
	} while (0)

#define BUG(X) \
	do { \
		void *f; \
		f = get_log(1); \
		if (f) { \
			log_print(f, _BUG_, "(0x%x) at %s:%d", X, __FILE__, __LINE__); \
			log_flush(f); \
			if (zlib.valid) \
				zlib.gzclose_w((struct gzFile *)f); \
			else \
				libc.fclose((FILE *)(f)); \
		} \
		_BUG(X); \
	} while (0)

#define BUG_MSG(X,fmt,...) \
	do { \
		void *f; \
		f = get_log(1); \
		if (f) { \
			log_print(f, _BUG_, "(0x%x) at %s:%d", X, __FILE__, __LINE__); \
			log_print(f, _BUG_, fmt, ## __VA_ARGS__ ); \
			log_flush(f); \
			if (zlib.valid) \
				zlib.gzclose_w((struct gzFile *)f); \
			else \
				libc.fclose((FILE *)(f)); \
		} \
		_BUG(X); \
	} while (0)

#ifdef _LIBC
#define SYMERR(X) \
	_BUG(X)
#else
#define SYMERR(X) \
	BUG(X)
#endif

__END_DECLS
#endif
