/*
 * wrap_tls.c
 * Copyright (C) 2014 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#include <pthread.h>

#include "wrap_tls.h"
#include "wrap_lib.h"

#ifdef HAVE_SIGHANDLER
extern void setup_special_sighandler(int sig);
#else
static void setup_special_sighandler(int sig)
{
	(void)sig;
	return;
}
#endif

static pthread_key_t s_wrap_tls_key = (pthread_key_t)-1;

static struct tls_info main_tls;

static void __free_tls(struct tls_info *tls);
static void thread_tls_cleanup(void *arg);

/*
 * This function will be called after a fork(), from the child process
 */
static void tls_init_child(int acquire)
{
	struct tls_info *tls;

	if (s_wrap_tls_key == (pthread_key_t)(-1))
		return;

	/*
	 * we need to clear out our TLS values, close the log file
	 * and re-start wrapper book keeping.
	 */
	tls = (struct tls_info *)libc.pthread_getspecific(s_wrap_tls_key);
	if (tls) {
		if (tls->should_cleanup) {
			tls->should_cleanup = 0;
			_pth_cleanup_pop(&tls->pth_cleanup, 0);
		}
		__free_tls(tls);
	}

	libc.pthread_key_delete(s_wrap_tls_key);
	s_wrap_tls_key = (pthread_key_t)(-1);
	libc.memset(&main_tls, 0, sizeof(main_tls));

	if (!acquire)
		return;

	init_tls();
}

void __hidden init_tls(void)
{
	if (s_wrap_tls_key == (pthread_key_t)(-1)) {
		if (libc.pthread_key_create(&s_wrap_tls_key, NULL) != 0)
			return;
		libc.pthread_setspecific(s_wrap_tls_key, NULL);
	}
}

static struct tls_info *__get_tls(int acquire, int reset)
{
	struct tls_info *tls = NULL;

	if (libc.forking && libc.forking != libc.getpid()) {
		/* we forked and we're the child, so we need to do a bit of cleanup */
		tls_init_child(acquire);
		libc.forking = 0;
	}

	if (s_wrap_tls_key == (pthread_key_t)(-1)) {
		/* don't create pthread keys if we're not
		 * supposed to allocate memory */
		if (!acquire)
			return NULL;
		init_tls();
	}

	tls = (struct tls_info *)libc.pthread_getspecific(s_wrap_tls_key);
	if (tls)
		goto out;

	if (!acquire)
		goto out;

	if (is_main()) {
		tls = &main_tls;
		libc.memset(tls, 0, sizeof(*tls));
	} else {
		tls = (struct tls_info *)libc.malloc(sizeof(*tls));
		libc.memset(tls, 0, sizeof(*tls));
		_pth_cleanup_push(&tls->pth_cleanup, thread_tls_cleanup, tls);
		tls->should_cleanup = 1;
	}

	if (!tls)
		goto out;

	/*
	 * This signal handler will flush logs!
	 */
	setup_special_sighandler(SIGUSR2);

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

#ifdef __APPLE__
extern unsigned int _raw_task_self(void);
extern unsigned int _raw_mach_port_deallocate(unsigned int target, unsigned int name);
#endif

static void __free_tls(struct tls_info *tls)
{
	if (!tls)
		return;

	/* clear out this thread's TLS values */
	tls_release_dvmstack(tls);
	tls_release_btcache(tls);
	tls_release_logbuffer(tls);
	tls_release_logfile(tls);

	libc.memset(tls, 0, sizeof(*tls));

#ifdef __APPLE__
	if (tls->thread_self) {
		_raw_mach_port_deallocate(_raw_task_self(), tls->thread_self);
		tls->thread_self = 0;
	}
#endif

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
		_pth_cleanup_pop(&tls->pth_cleanup, 0);
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

	if (!__set_wrapping())
		return;

	tls = __get_tls(0, 1);
	if (!tls)
		goto out;

	if ((void *)tls != arg) {
		/* has the tls key been cleared already?! */
		goto out;
	}

	__free_tls(tls);

out:
	__clear_wrapping();
	return;
}

