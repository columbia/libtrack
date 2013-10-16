/*
 * libc_wrappers.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Specially handled libc entry points
 *
 */
#include <unistd.h>
#include <sys/types.h>

#include "wrap_lib.h"

extern int local_strcmp(const char *s1, const char *s2);
extern int local_strncmp(const char *s1, const char *s2, size_t n);
extern pthread_key_t wrap_key;

typedef int (*handler_func)(const char *sym, uint32_t *regs, int slots, uint32_t *stack);

static int handle_exit(const char *sym, uint32_t *regs, int slots, uint32_t *stack);
static int handle_exec(const char *sym, uint32_t *regs, int slots, uint32_t *stack);
static int handle_fork(const char *sym, uint32_t *regs, int slots, uint32_t *stack);

/**
 * @wrap_special - handle the wrapping of special functions
 *
 * @param symbol The symbol name being wrapped
 * @param regs Pointer to memory holding saved register state
 * @param stack Pointer to stack memory associated with original call
 *
 * This function should return:
 *	0 if nothing special is to happen
 *	>0 if it handled the actual wrap call
 *	1 if it handled the actual wrap call
 *	>1 if it handled the wrap call, but is allowed to adjust TLS
 */
int __attribute__((visibility("hidden")))
wrap_special(const char *symbol, uint32_t *regs, int slots, uint32_t *stack)
{
	handler_func f = NULL;
	char fc;

	if (!symbol)
		return 0;

	fc = symbol[0];
	switch (fc) {
	case 'e':
		if (local_strcmp("exit", symbol) == 0)
			f = handle_exit;
		else if (local_strncmp("exec", symbol, 4) == 0)
			f = handle_exec;
		break;
	case 'f':
		if (local_strcmp("fork", symbol) == 0)
			f = handle_fork;
		break;
	case '_':
		if (local_strcmp("_exit", symbol) == 0)
			f = handle_exit;
		break;
	case 'v':
		if (local_strcmp("vfork", symbol) == 0)
			f = handle_fork;
		break;
	default:
		break;
	}

	if (f)
		return f(symbol, regs, slots, stack);
	return 0;
}

static void flush_and_close(const char *msg, const char *sym, uint32_t *regs, int slots)
{
	FILE *f;
	f = get_log(1);
	log_print(f, LOG, "I:%s %s(%d,%d,%d,%d)", msg, sym,
		     regs[0], regs[1], regs[2], regs[3]);
	libc.fflush(f);
	libc.fclose(f);
}

int handle_exit(const char *sym, uint32_t *regs, int slots, uint32_t *stack)
{
	flush_and_close("EXIT", sym, regs, slots);
	return 0;
}

int handle_fork(const char *sym, uint32_t *regs, int slots, uint32_t *stack)
{
	flush_and_close("FORK", sym, regs, slots);
	return 0;
}

static const char *wrap_ld_preload(const char *old_val)
{
	size_t sz = 0, old_sz = 0;
	const char *p;
	const char *ld_preload = LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME);
	size_t ldp_sz = sizeof(LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME));

	if (!old_val) {
		p = "LD_PRELOAD=" LIB_PATH "/" _str(_IBNAM_)
				  ":" LIB_PATH "/" _str(LIBNAME);
		goto out;
	}

	p = old_val;
	while (*p) p++;
	old_sz = (size_t)(p - old_val); /* doesn't include NULL terminator */

	p = libc.malloc(old_sz + ldp_sz + 1); /* +1 for ':' */
	if (!p)
		return NULL;

	libc.memcpy((void *)p, (void *)old_val, old_sz);
	((char *)p)[old_sz] = ':';
	libc.memcpy((void *)(p + old_sz + 1), (void *)ld_preload, ldp_sz);

out:
	libc_log("I:New LD_PRELOAD value '%s'", p);
	return p;
}

static const char **wrap_environ(const char **old_env)
{
	int n, sz = 1; /* NULL */
	const char **p = old_env;
	const char **new_env = NULL;
	int add_ldpreload = 1;

	/* the number of vars we'll be adding */
	n = 1; /* LD_PRELOAD */

	if (!old_env)
		goto alloc_new;

	/* get number of env vars */
	while (*p) {
		/* libc_log("I:env[]=%s", *p); */
		if (local_strncmp(*p,"LD_PRELOAD", 10) == 0) {
			/* add our path to the preload list */
			*p = wrap_ld_preload(*p);
			/* shortcut: we modified the pointer in-place */
			new_env = old_env;
		}
		sz++;
		p++;
	}

	if (new_env)
		return new_env;

alloc_new:
	new_env = (const char **)libc.malloc((sz + n) * sizeof(*p));
	if (!new_env) {
		libc_log("E:No memory for new env!");
		return old_env;
	}
	libc.memset(new_env, 0, (sz + n) * sizeof(*p));

	new_env[0] = wrap_ld_preload(NULL);

	/* copy over old pointers */
	while (old_env && sz--)
		new_env[n+sz] = old_env[sz];

	return new_env;
}

static void setup_exec_env(void)
{
	const char *ld_preload = LIB_PATH "/" _str(_IBNAM_)
				 ":" LIB_PATH "/" _str(LIBNAME);
	libc.setenv("LD_PRELOAD", ld_preload, 1);
	libc_log("I:New LD_PRELOAD value '%s'", ld_preload);
	/* libc.setenv("LD_DEBUG", "3", 1); */
}

int handle_exec(const char *sym, uint32_t *regs, int slots, uint32_t *stack)
{
	libc_log("I:%s:%s:", sym, (const char *)regs[0]);

	if (local_strcmp("execle", sym) == 0)
		libc_log("E:No support for execle!");

	if (local_strcmp("execve", sym) == 0)
		regs[2] = (uint32_t)wrap_environ((const char **)regs[2]);
	else
		setup_exec_env();

	libc.fflush(get_log(0));
	//close_libc_iface();

	return 0;
}
