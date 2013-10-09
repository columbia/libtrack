/*
 * libc_wrappers.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Specially handled libc entry points
 *
 */

#include "wrap_lib.h"

extern int local_strcmp(const char *s1, const char *s2);
extern pthread_key_t wrap_key;

typedef void (*handler_func)(const char *sym, uint32_t *regs, uint32_t *stack);

static void handle_exec(const char *sym, uint32_t *regs, uint32_t *stack);
static void handle_fork(const char *sym, uint32_t *regs, uint32_t *stack);
static void handle_vfork(const char *sym, uint32_t *regs, uint32_t *stack);
static void handle___fork(const char *sym, uint32_t *regs, uint32_t *stack);

void __attribute__((visibility("hidden")))
wrap_special(const char *symbol, uint32_t *regs, uint32_t *stack)
{
	handler_func f = NULL;

	if (!symbol)
		return;
	if (local_strcmp("exec", symbol) == 0)
		f = handle_exec;
	else if (local_strcmp("vfork", symbol) == 0)
		f = handle_vfork;
	else if (local_strcmp("fork", symbol) == 0)
		f = handle_fork;
	else if (local_strcmp("__fork", symbol) == 0)
		f = handle___fork;

	if (f)
		f(symbol, regs, stack);
}


void handle_exec(const char *sym, uint32_t *regs, uint32_t *stack)
{
	if (local_strcmp("execle", sym) == 0)
		libc_log("ERROR:No support for execle!");
	libc_log("EXEC:%s:\n", sym);
	libc.setenv("LD_PRELOAD", LIB_PATH "/" _str(_IBNAM_), 1);
	/* libc.setenv("LD_DEBUG", "3", 1); */
	libc.pthread_setspecific(wrap_key, (const void *)0);
	close_libc_iface();
	return;
}

void handle_fork(const char *sym, uint32_t *regs, uint32_t *stack)
{
	libc_log("ERROR:fork not working yet!");
}

void handle_vfork(const char *sym, uint32_t *regs, uint32_t *stack)
{
	libc_log("ERROR:vfork not working yet!");
}

void handle___fork(const char *sym, uint32_t *regs, uint32_t *stack)
{
	libc_log("ERROR:__fork not working yet!");
}
