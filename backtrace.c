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
#include "backtrace.h"
#include "java_backtrace.h"

extern struct libc_iface libc;

#ifdef ANDROID
extern struct dvm_iface  dvm;
#else
static struct dvm_iface  dvm;
#endif

#define FRAMES_TO_SKIP 2

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
		/*
		if (frame->lr || frame->sp || frame->r7)
			libc.fprintf(state->f, " :%d:LR=0x%08x,SP=0x%08x,R7=0x%08x\n",
				     count, frame->lr, frame->sp, frame->r7);
		 */
	}
	if (state->count == 1 && state->lr.addr)
		print_info(state->f, state->count, "LR", &state->lr);

	if (state->dvm_bt && state->dvm_bt->count > 0)
		print_dvm_bt(&dvm, state->f, state->dvm_bt, tv);

	log_print(state->f, BT, "END");
}

static void std_backtrace(FILE *logf, struct log_info *info)
{
	struct bt_state state;
	void *frames[MAX_BT_FRAMES];
	struct bt_frame *frame;
	int count;
	Dl_info dli;

	libc.memset(&state, 0, sizeof(state));
	state.f = logf;

	state.count = libc.backtrace(frames, MAX_BT_FRAMES);

	for (count = 0; count < state.count; count++) {
		frame = &state.frame[count];
		if (dladdr(frames[count], &dli) != 0) {
			frame->pc.addr = frames[count];
			frame->pc.symbol = dli.dli_sname;
			frame->pc.symaddr = dli.dli_saddr;
			frame->pc.libname = dli.dli_fname;
			frame->pc.libstart = dli.dli_fbase;
		}
	}

	state.lr.addr = (void *)info->regs[12];
	if (state.lr.addr && dladdr((void *)info->regs[12], &dli) != 0) {
		state.lr.symbol = dli.dli_sname;
		state.lr.symaddr = dli.dli_saddr;
		state.lr.libname = dli.dli_fname;
		state.lr.libstart = dli.dli_fbase;
	}

	print_bt_state(&state, &info->tv);
}

#ifdef __arm__
static inline uintptr_t __Unwind_GetIP(__unwind_context *ctx)
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

	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 14,
			     _UVRSD_UINT32, &frame->lr);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 13,
			     _UVRSD_UINT32, &frame->sp);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 7,
			     _UVRSD_UINT32, &frame->r7);
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

static inline int is_same_stack(struct bt_frame *current, void **last, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		if (current[i].pc.addr != last[i])
			return 0;
	}
	return 1;
}


static void unwind_backtrace(FILE *logf, struct log_info *info)
{
	Dl_info dli;
	int i;
	struct bt_state state;
	struct dvm_bt dvm_bt;

	libc.memset(&state, 0, sizeof(state));
	libc.memset(&dvm_bt, 0, sizeof(dvm_bt));

	state.f = logf;
	state.dvm_bt = &dvm_bt;

	libc._Unwind_Backtrace(trace_func, &state);

	/* check the backtrace to see if it's the same as the previous one */
	if (*(info->last_stack_depth) == state.count) {
		if (is_same_stack(state.frame, info->last_stack, state.count)) {
			/*
			 * these stacks are the same - bump a counter and
			 * don't print anything yet
			 */
			*(info->last_stack_cnt) += 1;

			/*
			 * TODO: here we are making the assumption that an
			 * identical native backtrace is equivalent to an
			 * identical Java/Dalvik backtrace.
			 * THIS MAY NOT BE TRUE!
			 */
			return;
		}
	}
	/*
	 * the current stack is a new one:
	 *     check the last stack count - if it's > 1, print a repeat message
	 *     reset the stats and keep the PCs for next time
	 */
	if (*(info->last_stack_cnt) > 1)
		__log_print(&info->tv, state.f, "BT", "REPEAT:%d:",
			    *(info->last_stack_cnt));

	*(info->last_stack_cnt) = 1;
	*(info->last_stack_depth) = state.count;
	for (i = 0; i < state.count; i++)
		info->last_stack[i] = state.frame[i].pc.addr;

	/* if we only have 1 stack frame, then look at the link register */
	if (state.count == 1) {
		state.lr.addr = (void *)info->regs[12];
		if (state.lr.addr && dladdr((void *)info->regs[12], &dli) != 0) {
			state.lr.symbol = dli.dli_sname;
			state.lr.symaddr = dli.dli_saddr;
			state.lr.libname = dli.dli_fname;
			state.lr.libstart = dli.dli_fbase;
		}
	}

	get_dvm_backtrace(&dvm, &state, &dvm_bt);
	print_bt_state(&state, &info->tv);
}

pthread_key_t s_last_stack_key = (pthread_key_t)-1;

void __attribute__((visibility("hidden")))
log_backtrace(FILE *logf, struct log_info *info)
{
	char *last_stack = NULL;

	if (s_last_stack_key == -1)
		if (libc.pthread_key_create(&s_last_stack_key, NULL) != 0)
			return;

	last_stack = libc.pthread_getspecific(s_last_stack_key);
	if (!last_stack) {
		int sz = ((MAX_BT_FRAMES) * sizeof(void *)) + (2 * sizeof(int));
		last_stack = (char *)libc.malloc(sz);
		if (!last_stack)
			return;
		libc.memset(last_stack, 0, sz);
		libc.pthread_setspecific(s_last_stack_key, (void *)last_stack);
	}
	info->last_stack_depth = (int *)last_stack;
	info->last_stack_cnt = (int *)(last_stack + sizeof(int));
	info->last_stack = (void **)(last_stack + 2*sizeof(int));

	/* initialize Dalvik VM backtracing */
	if (!dvm.dso)
		init_dvm_iface(&dvm, DVM_DFLT_DSO_PATH);

	/* TODO: maybe print out function arguments? */
	if (libc.backtrace)
		std_backtrace(logf, info);
	else if (libc._Unwind_Backtrace)
		unwind_backtrace(logf, info);
	else
		__log_print(&info->tv, logf, "CALL", "%s", info->symbol);
}
