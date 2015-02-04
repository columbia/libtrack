/*
 * wrap_tls.h
 * Copyright (C) 2014 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#ifndef WRAP_TLS_H
#define WRAP_TLS_H

#include "wrap_lib.h"
#include <pthread.h>

#define TLS_MAX_STRING_LEN 256

#ifndef ANDROID
static inline void _pth_cleanup_push(__pthread_cleanup_t *handler, __pthread_cleanup_func_t func, void *arg)
{
	pthread_t __self = pthread_self();
	handler->__routine = func;
	handler->__arg = arg;
	handler->__next = __self->__cleanup_stack;
	__self->__cleanup_stack = handler;
}

static inline void _pth_cleanup_pop(__pthread_cleanup_t *handler, int execute)
{
	pthread_t __self = pthread_self();
	__self->__cleanup_stack = handler->__next;
	if (execute)
		(handler->__routine)(handler->__arg);
}
#else
#define _pth_cleanup_push libc.__pthread_cleanup_push
#define _pth_cleanup_pop  libc.__pthread_cleanup_pop
#endif

struct tls_info {
	char logname[TLS_MAX_STRING_LEN];
	void *logfile;

	void *logbuffer;

	void *btcache;

	char dvm_threadname[TLS_MAX_STRING_LEN];
	void *dvmstack;

	struct ret_ctx ret;
	struct log_info info;

	__pthread_cleanup_t pth_cleanup;
	int should_cleanup;
#ifdef __APPLE__
	unsigned int thread_self;
#endif
};

#define wsym(TLS) \
	((TLS)->info.symbol)

extern void init_tls(void);

extern struct tls_info *get_tls(void);
extern struct tls_info *peek_tls(void);

extern void clear_tls(int release_key);

extern void tls_release_logfile(struct tls_info *tls);
extern void tls_release_logbuffer(struct tls_info *tls);
extern void tls_release_btcache(struct tls_info *tls);
extern void tls_release_dvmstack(struct tls_info *tls);

#endif
