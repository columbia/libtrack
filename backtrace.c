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

#define MAX_BT_FRAMES 64
struct bt_state {
	void *frames[MAX_BT_FRAMES];
	const char **symbols;
	int count;

	int nskip;
	FILE *f;
};

static inline void print_bt_state(struct bt_state *state)
{
	int count = state->count;
	const char *sym;
	libc.fprintf(state->f, "BT:START\n");
	while (count--) {
		sym = state->symbols[count];
		if (!sym)
			sym = "??";
		libc.fprintf(state->f, "  :%d:0x%x:%s:\n",
			     count, state->frames[count], sym);
	}
	libc.fprintf(state->f, "BT:END\n");
}

static void std_backtrace(FILE *logf, const char *sym)
{
	struct bt_state state;

	libc.memset(&state, 0, sizeof(state));
	state.f = logf;

	state.count = libc.backtrace(state.frames, MAX_BT_FRAMES);
	state.symbols = (const char **)libc.backtrace_symbols(state.frames,
							      state.count);

	print_bt_state(&state);
	libc.free(state.symbols);
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
	uintptr_t ip;
	Dl_info info;

	ip = __Unwind_GetIP(context);

	/* The first stack frame is:
	 *	log_backtrace
	 * and the second is:
	 *	wrapped_tracer
	 * skip them both
	 */
	if (ip != 0 && state->nskip < 2) {
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

	state->frames[state->count] = (void *)ip;

	if (dladdr((void *)ip, &info) != 0) {
		/*
		 * TODO: this doesn't account for PC offset
		 *       e.g., when info.dli_saddr != ip
		 */
		state->symbols[state->count] = info.dli_sname;
	}

	state->count++;

	if (state->count >= MAX_BT_FRAMES)
		return _URC_END_OF_STACK;
	return _URC_NO_REASON;
}


static void unwind_backtrace(FILE *logf, const char *sym)
{
	struct bt_state state;

	libc.memset(&state, 0, sizeof(state));
	state.symbols = malloc(MAX_BT_FRAMES * sizeof(char *));
	libc.memset(state.symbols, 0, MAX_BT_FRAMES * sizeof(char *));
	state.f = logf;

	libc._Unwind_Backtrace(trace_func, &state);

	print_bt_state(&state);
	libc.free(state.symbols);
}

void __attribute__((visibility("hidden")))
log_backtrace(FILE *logf, const char *sym)
{
	if (libc.backtrace)
		std_backtrace(logf, sym);
	else if (libc._Unwind_Backtrace)
		unwind_backtrace(logf, sym);
	else
		libc.fprintf(logf, "ST:%s\n", sym);
}
