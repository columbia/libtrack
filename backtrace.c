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

#define FRAMES_TO_SKIP 3
#define MAX_BT_FRAMES 64

struct bt_frame {
	void *pc;
	const char *symbol;
	void *symaddr;
	const char *libname;
	void *libstart;
};

struct bt_state {
	struct bt_frame frame[MAX_BT_FRAMES];
	int count;
	int nskip;
	FILE *f;
};

static void print_bt_state(struct bt_state *state, struct timeval *tv)
{
	int count;
	struct bt_frame *frame;
	unsigned long ofst;
	char c;
	const char *sym;

	libc.fprintf(state->f, "BT:START:%lu.%lu\n",
		     (unsigned long)tv->tv_sec, (unsigned long)tv->tv_usec);
	for (count = 0; count <= state->count; count++) {
		frame = &state->frame[count];
		if (!frame->symaddr) {
			c = '+';
			ofst = (unsigned long)frame->pc -
				(unsigned long)frame->libstart;
		} else if ((unsigned long)frame->pc >
			   (unsigned long)frame->symaddr) {
			c = '+';
			ofst = (unsigned long)frame->pc -
				(unsigned long)frame->symaddr;
		} else {
			c = '-';
			ofst = (unsigned long)frame->symaddr -
				(unsigned long)frame->pc;
		}
		sym = frame->symbol;
		if (!sym)
			sym = "??";
		libc.fprintf(state->f, "  :%d:0x%x:%s:%c0x%x:%s(%p):\n",
			     count, frame->pc, sym, c, ofst,
			     frame->libname, frame->libstart);
	}
	libc.fprintf(state->f, "BT:END\n");
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
			frame->pc = frames[count];
			frame->symbol = info.dli_sname;
			frame->symaddr = info.dli_saddr;
			frame->libname = info.dli_fname;
			frame->libstart = info.dli_fbase;
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
	return val & ~1; /* thumb bit */
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

#ifdef __arm__
	/*
	 * The instruction pointer is pointing at the instruction after the
	 * bl(x), and the _Unwind_Backtrace routine already masks the Thumb
	 * mode indicator (LSB in PC). So we need to do a quick check here
	 * to find out if the previous instruction is a Thumb-mode BLX(2).
	 * If so subtract 2 otherwise 4 from PC.
	 */
	if (ip != 0) {
		short* ptr = (short *)ip;
		/* Thumb BLX(2) */
		if ((*(ptr-1) & 0xff80) == 0x4780)
			ip -= 2;
		else
			ip -= 4;
	}
#endif

	frame = &state->frame[state->count];
	frame->pc = (void *)ip;

	if (dladdr((void *)ip, &info) != 0) {
		frame->symbol = info.dli_sname;
		frame->symaddr = info.dli_saddr;
		frame->libname = info.dli_fname;
		frame->libstart = info.dli_fbase;
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
log_backtrace(FILE *logf, const char *sym, uint32_t *regs, uint32_t *stack)
{
	struct timeval tv;

	libc.gettimeofday(&tv, NULL);

	/* TODO: maybe print out function arguments? */

	if (libc.backtrace)
		std_backtrace(logf, sym, &tv);
	else if (libc._Unwind_Backtrace)
		unwind_backtrace(logf, sym, &tv);
	else
		libc.fprintf(logf, "CALL:%s\n", sym);
}
