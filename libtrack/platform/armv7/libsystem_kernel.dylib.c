/*
 * Symbols needed for libsystem_kernel
 */
#include <dlfcn.h>
#include <pthread.h>
#include <stdint.h>

#include "wrap_lib.h"
#include "wrap_tls.h"

struct ProgramVars;

struct _libkernel_functions {
	/* The following functions are included in version 1 of this structure */
	unsigned long version;
	void* (*dlsym)(void*, const char*);
	void* (*malloc)(size_t);
	void  (*free)(void*);
	void* (*realloc)(void*, size_t);
	void  (*_pthread_exit_if_canceled)(int);

	/* The following functions are included in version 2 of this structure */
	void *(*dlopen)(const char *, int);
	int (*dlclose)(void *);
	int (*dladdr)(const void *, Dl_info *);
	void *reserved4;
	void *reserved5;

	/* The following functions are included in version 3 of this structure */
	void (*pthread_clear_qos_tsd)(mach_port_t);

	/* Subsequent versions must only add pointers! */
};

static struct _libkernel_functions *lc_fcns = NULL;
static void *real_libkernel_dso = NULL;

typedef void (*libkernel_init_func)(struct _libkernel_functions *fns,
				    const char *envp[], const char *apple[],
				    const struct ProgramVars *vars);

void __libkernel_init(struct _libkernel_functions *fns,
		const char *envp[] __attribute__((unused)),
		const char *apple[] __attribute__((unused)),
		const struct ProgramVars *vars __attribute__((unused)))
{
	libkernel_init_func real_init;

	/* stash the pointer */
	lc_fcns = fns;

	if (!lc_fcns->dlopen)
		_BUG(0x777);

	real_init = (libkernel_init_func)wrapped_dlsym(LIBPATH,
						       &real_libkernel_dso,
						       "__libkernel_init");
	if (!real_init)
		_BUG(0x779);

	/* pass the call along to the real libkernel */
	real_init(fns, envp, apple, vars);
}

pthread_t pthread_self(void)
{
	/* :-( */
	return (pthread_t)NULL;
}

volatile int *__error(void)
{
	/* :-( */
	static int __dummy_errno_val__ = 0;
	return &__dummy_errno_val__;
}

volatile int *__errno(void)
{
	return __error();
}

void * __hidden dlopen(const char *path, int mode)
{
	if (lc_fcns && lc_fcns->dlopen)
		return (lc_fcns->dlopen)(path, mode);
	return NULL;
}

int __hidden dlclose(void *dso)
{
	if (lc_fcns && lc_fcns->dlclose)
		return (lc_fcns->dlclose)(dso);
	return -1;
}

int __hidden dladdr(const void *sym, Dl_info *info)
{
	if (lc_fcns && lc_fcns->dladdr)
		return (lc_fcns->dladdr)(sym, info);
	return -1;
}

void * __hidden dlsym(void *dso, const char *sym)
{
	if (lc_fcns && lc_fcns->dlsym)
		return (lc_fcns->dlsym)(dso, sym);
	return NULL;
}


static inline void timespec_sub(struct timespec *a, const struct timespec *b)
{
	a->tv_sec  -= b->tv_sec;
	a->tv_nsec -= b->tv_nsec;
	if (a->tv_nsec < 0) {
		a->tv_nsec += 1000000000;
		a->tv_sec  -= 1;
	}
}

static inline void log_posixtime(struct tls_info *tls, const char *sym,
				 struct timespec *start, struct timespec *end)
{
	struct timespec posix_time = *end;
	timespec_sub(&posix_time, start);
	bt_printf(tls, "LOG:T:%s:%lu.%lu", sym,
		  (unsigned long)posix_time.tv_sec,
		  (unsigned long)posix_time.tv_nsec);
}

/**
 * @wrapped_return - carefully pull a stored return value from TLS and return
 *                   to the original caller
 *
 * TODO:
 * Right now, we always return a 32-bit number. This won't work for large
 * return value functions...
 */
uint32_t wrapped_return(void)
{
	/* record this ASAP */
	struct timespec posix_end;
	libc.clock_gettime(CLOCK_THREAD_CPUTIME_ID, &posix_end);

	{
		struct tls_info *tls;
		struct ret_ctx *ret;
		uint32_t rval, err = (*__errno());

		tls = get_tls();
		ret = get_retmem(tls);
		if (!ret)
			BUG_MSG(0x4311, "No TLS return value!");

		if (tls->info.log_time) {
			rval = 0; /* handled by arch_wrapped_return */
			log_posixtime(tls, ret->sym,
				      &ret->posix_start, &posix_end);
			tls->info.log_time = 0;
		} else {
			err = ret->_errno;
			rval = ret->u.u32[0];
		}

		(*__errno()) = err;
		return rval;
	}
}

#include "libsystem_kernel_wrap_cache.c"
