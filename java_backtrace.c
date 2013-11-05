/*
 * java_backtrace.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */

#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>

#include "wrap_lib.h"
#include "java_backtrace.h"

extern struct libc_iface libc;

struct dvm_iface dvm;


void init_dvm_iface(struct dvm_iface *dvm, const char *dso_path)
{
	dvm->dso = (void *)1;
	return;
}

void get_dvm_backtrace(struct dvm_iface *dvm,
			      struct bt_state *bt_state,
			      struct dvm_bt *dvm_bt)
{
	dvm_bt->count = 0;
	return;
}

void print_dvm_bt(FILE *logf, struct dvm_bt *dvm_bt, struct timeval *tv)
{
	__log_print(tv, logf, "DVM", "BACKTRACE_WILL_GO_HERE");
	return;
}
