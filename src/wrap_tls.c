/*
 * wrap_tls.c
 * Copyright (C) 2014 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#include <pthread.h>

#include "wrap_tls.h"
#include "wrap_lib.h"

static pthread_key_t s_wrap_tls_key = (pthread_key_t)-1;

static struct tls_info main_tls;

static void __free_tls(struct tls_info *tls);
static void thread_tls_cleanup(void *arg);

extern void __lh_clear(void);

/*
 * This function will be called after a fork(), from the child process
 */
//static
void tls_init_child(void)
{
	struct tls_info *tls;

	if (s_wrap_tls_key == (pthread_key_t)(-1))
		return;

	/*
	 * we need to clear out our TLS values, close the log file
	 * and re-start wrapper book keeping.
	 */
	tls = (struct tls_info *)libc.pthread_getspecific(s_wrap_tls_key);
	if (tls)
		__free_tls(tls);

	libc.pthread_key_delete(s_wrap_tls_key);
	s_wrap_tls_key = (pthread_key_t)(-1);
	libc.memset(&main_tls, 0, sizeof(main_tls));

	__lh_clear();

	if (libc.pthread_key_create(&s_wrap_tls_key, NULL) != 0)
		return;
	libc.pthread_setspecific(s_wrap_tls_key, NULL);
}

void __hidden init_tls(void)
{
	if (s_wrap_tls_key == (pthread_key_t)(-1)) {
		if (libc.pthread_key_create(&s_wrap_tls_key, NULL) != 0)
			return;
		libc.pthread_setspecific(s_wrap_tls_key, NULL);
	}

	/* the parent of a fork - no need to do anything */
	if (!libc.forking || libc.forking == libc.getpid())
	    return;

	/* we forked and we're the child, so we need to do a bit of cleanup */
	tls_init_child();
	if (should_log()) {
		void *f = get_log(0);
		libc_log("I:FORKED");
	}
}

static struct tls_info *__get_tls(int acquire, int reset)
{
	struct tls_info *tls = NULL;

	if (s_wrap_tls_key == (pthread_key_t)(-1)) {
		if (!acquire)
			return NULL;
		init_tls();
	}

	tls = (struct tls_info *)libc.pthread_getspecific(s_wrap_tls_key);
	if (tls)
		goto out;

	if (!acquire)
		goto out;

	if (is_main())
		tls = &main_tls;
	else
		tls = (struct tls_info *)libc.malloc(sizeof(*tls));
	if (!tls)
		goto out;

	libc.memset(tls, 0, sizeof(*tls));

	libc.__pthread_cleanup_push(&tls->pth_cleanup, thread_tls_cleanup, tls);
	tls->should_cleanup = 1;

	libc.pthread_setspecific(s_wrap_tls_key, (void *)tls);

out:
	if (reset)
		libc.pthread_setspecific(s_wrap_tls_key, NULL);

	return tls;
}

struct tls_info *get_tls(void)
{
	return __get_tls(1, 0);
}

struct tls_info *peek_tls(void)
{
	return __get_tls(0, 0);
}

static void __free_tls(struct tls_info *tls)
{
	if (!tls)
		return;

	/* clear out this thread's TLS values */
	if (should_log())
		bt_printf(tls, "D:CLEARING TLS\n");
	tls_release_dvmstack(tls);
	tls_release_btcache(tls);
	tls_release_logbuffer(tls);
	tls_release_logfile(tls);
	tls_release_lh(tls);

	libc.memset(tls, 0, sizeof(*tls));

	if (tls != &main_tls)
		libc.free(tls);
}

void clear_tls(int release_key)
{
	struct tls_info *tls;

	tls = __get_tls(0, 1);
	if (!tls)
		return;

	if (tls->should_cleanup) {
		tls->should_cleanup = 0;
		libc.__pthread_cleanup_pop(&tls->pth_cleanup, 0);
	}

	__free_tls(tls);

	if (release_key) {
		libc.pthread_key_delete(s_wrap_tls_key);
		s_wrap_tls_key = (pthread_key_t)(-1);
	}
}

static void thread_tls_cleanup(void *arg)
{
	struct tls_info *tls;

	tls = __get_tls(0, 1);
	if (!tls)
		return;

	if ((void *)tls != arg) {
		/* has the tls key been cleared already?! */
		return;
	}

	__free_tls(tls);
}

