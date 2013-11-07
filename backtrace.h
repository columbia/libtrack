/*
 * backtrace.h
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Glue to wrap up a library (including possibly libc) and trace certain
 * functions within that library.
 */
#ifndef WRAPPER_BACKTRACE_H
#define WRAPPER_BACKTRACE_H

#include "wrap_lib.h"

#define MAX_BT_FRAMES 128

/*
struct bt_info {
	void *addr;
	const char *symbol;
	void *symaddr;
	const char *libname;
	void *libstart;
};
*/

struct bt_frame {
	//struct bt_info pc;
	void *pc;
#ifdef VERBOSE_FRAME_INFO
	unsigned long reg[4]
	unsigned long lr;
	unsigned long sp;
#endif
};

struct dvm_bt;

struct bt_state {
	struct bt_frame frame[MAX_BT_FRAMES];
	int count;
	int nskip;
	struct dvm_bt *dvm_bt;
	FILE *f;
};

#endif /* WRAPPER_BACKTRACE_H */
