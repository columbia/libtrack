/*
 * backtrace.c
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Glue to wrap up a library (including possibly libc) and trace certain
 * functions within that library.
 */
#include <dlfcn.h>
#include <unwind.h>
#include <sys/types.h>

#include "wrap_lib.h"

extern struct libc_iface libc;

#define FRAMES_TO_SKIP 2
#define MAX_BT_FRAMES 64

struct bt_info {
	void *addr;
	const char *symbol;
	void *symaddr;
	const char *libname;
	void *libstart;
};

struct bt_frame {
	struct bt_info pc;
};

struct bt_state {
	struct bt_frame frame[MAX_BT_FRAMES];
	int count;
	int nskip;
	FILE *f;
};

static inline void print_info(FILE *f, int count, const char *pfx,
			      struct bt_info *info)
{
	const char *sym;
	unsigned long ofst;
	char c;
	if (!info->symaddr) {
		c = '+';
		ofst = (unsigned long)info->addr -
			(unsigned long)info->libstart;
	} else if ((unsigned long)info->addr >
		   (unsigned long)info->symaddr) {
		c = '+';
		ofst = (unsigned long)info->addr -
			(unsigned long)info->symaddr;
	} else {
		c = '-';
		ofst = (unsigned long)info->symaddr -
			(unsigned long)info->addr;
	}
	sym = info->symbol;
	if (!sym)
		sym = "??";
	if (pfx)
		libc.fprintf(f, " :%d(%s):0x%x:%s:%c0x%x:%s(%p):\n",
			     count, pfx, (unsigned int)info->addr,
			     info->symbol ? info->symbol : "??",
			     c, ofst, info->libname, info->libstart);
	else
		libc.fprintf(f, " :%d:0x%x:%s:%c0x%x:%s(%p):\n",
			     count, (unsigned int)info->addr,
			     info->symbol ? info->symbol : "??",
			     c, ofst, info->libname, info->libstart);
}

static void print_bt_state(struct bt_state *state, struct timeval *tv)
{
	int count;
	struct bt_frame *frame;
	unsigned long ofst;
	char c;
	const char *sym;

	__log_print(tv, state->f, "BT", "START");
	for (count = 0; count < state->count; count++) {
		frame = &state->frame[count];
		print_info(state->f, count, NULL, &frame->pc);
	}
	log_print(state->f, BT, "END");
}

static void std_backtrace(FILE *logf, const char *sym, struct timeval *tv)
{
	struct bt_state state;
	void *frames[MAX_BT_FRAMES];
	struct bt_frame *frame;
	int count;
	Dl_info info;

	libc.memset(&state, 0, sizeof(state));
	state.f = logf;

	state.count = libc.backtrace(frames, MAX_BT_FRAMES);

	for (count = 0; count < state.count; count++) {
		frame = &state.frame[count];
		if (dladdr(frames[count], &info) != 0) {
			frame->pc.addr = frames[count];
			frame->pc.symbol = info.dli_sname;
			frame->pc.symaddr = info.dli_saddr;
			frame->pc.libname = info.dli_fname;
			frame->pc.libstart = info.dli_fbase;
		}
	}

	print_bt_state(&state, tv);
}

#ifdef __arm__
static inline uintptr_t __Unwind_GetIP(_Unwind_Context* ctx)
{
	uint32_t val;
	if (!libc._Unwind_VRS_Get)
		_BUG(0xA0);
	libc._Unwind_VRS_Get(ctx, _UVRSC_CORE, 15,/* 15 == pc (UNWIND_IP_REG) */
			     _UVRSD_UINT32, &val);
	return val; /* & ~1; */ /* thumb bit */
}
#else
#define __Unwind_GetIP(ctx) \
	(uintptr_t)(libc._Unwind_GetIP(ctx))
#endif

/*
 * unwind backtrace code adapted from:
 * 	bionic/libc/bionic/debug_stacktrace.cpp
 *
 */
static _Unwind_Reason_Code trace_func(__unwind_context* context, void* arg)
{
	struct bt_state *state = (struct bt_state *)arg;
	struct bt_frame *frame;
	uintptr_t ip;
	Dl_info info;

	ip = __Unwind_GetIP(context);

	/* The first stack frame is:
	 *	log_backtrace
	 * and the second is:
	 *	wrapped_tracer
	 * skip them both
	 */
	if (ip != 0 && state->nskip < FRAMES_TO_SKIP) {
		state->nskip++;
		return _URC_NO_REASON;
	}

	frame = &state->frame[state->count];

#ifdef __arm__
	/*
	 * The instruction pointer is pointing at the instruction after the
	 * bl(x), and the _Unwind_Backtrace routine already masks the Thumb
	 * mode indicator (LSB in PC). So we need to do a quick check here
	 * to find out if the previous instruction is a Thumb-mode BLX(2).
	 * If so subtract 2 otherwise 4 from PC.
	 */
	/* on ARM, we fixed GetIP to _not_ mask the thumb bit! */
	if (ip & 0x1)
		ip = (ip & ~0x1) - 2;
	else
		ip -= 4;

#endif

	frame->pc.addr = (void *)ip;
	if (dladdr((void *)ip, &info) != 0) {
		frame->pc.symbol = info.dli_sname;
		frame->pc.symaddr = info.dli_saddr;
		frame->pc.libname = info.dli_fname;
		frame->pc.libstart = info.dli_fbase;
	}

	state->count++;

	if (state->count >= MAX_BT_FRAMES)
		return _URC_END_OF_STACK;
	return _URC_NO_REASON;
}


static void unwind_backtrace(FILE *logf, const char *sym, struct timeval *tv)
{
	struct bt_state state;

	libc.memset(&state, 0, sizeof(state));
	state.f = logf;

	libc._Unwind_Backtrace(trace_func, &state);

	print_bt_state(&state, tv);
}

void __attribute__((visibility("hidden")))
log_backtrace(FILE *logf, const char *sym, uint32_t *regs, struct timeval *tv)
{

	/* TODO: maybe print out function arguments? */

	if (libc.backtrace)
		std_backtrace(logf, sym, tv);
	else if (libc._Unwind_Backtrace)
		unwind_backtrace(logf, sym, tv);
	else
		__log_print(tv, logf, "CALL", "%s", sym);
}
