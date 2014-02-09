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

struct tls_info {
	char logname[TLS_MAX_STRING_LEN];
	void *logfile;

	void *logbuffer;

	void *btcache;

	char dvm_threadname[TLS_MAX_STRING_LEN];
	void *dvmstack;

	struct ret_ctx ret;
	struct log_info info;

#ifdef ANDROID
	__pthread_cleanup_t pth_cleanup;
	int should_cleanup;
#endif

	trace_ptr_t lh;
};

extern void init_tls(void);

extern struct tls_info *get_tls(void);
extern struct tls_info *peek_tls(void);

extern void clear_tls(int release_key);

extern void tls_release_logfile(struct tls_info *tls);
extern void tls_release_logbuffer(struct tls_info *tls);
extern void tls_release_btcache(struct tls_info *tls);
extern void tls_release_dvmstack(struct tls_info *tls);
extern void tls_release_lh(struct tls_info *tls);

#endif
