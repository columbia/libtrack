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

//#define OUTPUT_CACHE_STATS

/*
 * Unwound stack frame:
 *	<TRACE_FUNC (isn't counted)>
 *	unwind_backtrace
 *	log_backtrace
 *	wrapped_tracer
 * skip them all
 */
#define FRAMES_TO_SKIP 3

extern struct libc_iface libc;

#ifdef ANDROID
extern struct dvm_iface  dvm;
#else
static struct dvm_iface  dvm;
#endif

/*
 * TODO: add some locking, and make the cache global!
 */
static pthread_key_t s_line_cache_key = (pthread_key_t)(-1);

static struct bt_line_cache *get_bt_line_cache(void)
{
	struct bt_line_cache *cache;

	if (s_line_cache_key == (pthread_key_t)(-1))
		if (libc.pthread_key_create(&s_line_cache_key, NULL) != 0)
			return NULL;

	cache = (struct bt_line_cache *)libc.pthread_getspecific(s_line_cache_key);
	if (cache)
		return cache;

	cache = (struct bt_line_cache *)libc.malloc(sizeof(*cache));
	if (!cache)
		return NULL;
	libc.memset(cache, 0, sizeof(*cache));
	libc.pthread_setspecific(s_line_cache_key, cache);
	return cache;
}

void bt_flush_cache(void)
{
	void *cache;

	if (s_line_cache_key == (pthread_key_t)(-1))
		if (libc.pthread_key_create(&s_line_cache_key, NULL) != 0)
			return;

	cache = libc.pthread_getspecific(s_line_cache_key);
	if (cache) {
		libc.free(cache);
		libc.pthread_setspecific(s_line_cache_key, NULL);
	}
}

struct bt_line *bt_cache_fetch(void *sym, struct bt_line_cache **cache_out)
{
	struct bt_line_cache *cache;
	struct bt_line *l;
	uint16_t idx;

	cache = get_bt_line_cache();
	if (!cache)
		return NULL;

	idx = bt_hash(sym);
	if (cache_out)
		*cache_out = cache;

	l = cache->c[idx];
	if (l[0].sym == sym) {
		cache->hit++;
		l[0].usage++;
		return &l[0];
	}
	if (l[1].sym == sym) {
		cache->hit++;
		l[1].usage++;
		return &l[1];
	}

	cache->miss++;
	if (!l[0].sym) {
		cache->usage++;
		return &l[0];
	}
	if (!l[1].sym) {
		cache->usage++;
		return &l[1];
	}

	/* both levels of cache are full - evict the least recently used */
	if (l[0].usage < l[1].usage) {
		l[0].usage++;
		return &l[0];
	}
	l[1].usage++;
	return &l[1];
}

static inline void print_info(struct log_info *info, int count, void *sym)
{
	unsigned long ofst;
	char c;
	struct bt_line_cache *cache = NULL;
	struct bt_line *cline;
	Dl_info dli;

	cline = bt_cache_fetch(sym, &cache);
	if (!cline)
		goto do_lookup;

#ifdef OUTPUT_CACHE_STATS
	if (cache &&
	    ((cache->hit + cache->miss) % 1024 == 0))
		__bt_printf(info, " :CACHE_STATS:U[%d]:H[%d]:M[%d]\n",
			    cache->usage, cache->hit, cache->miss);
#endif

	if (cline->sym == sym) { /* cache hit! */
		__bt_printf(info, " :%d:%s", count, cline->str);
		return;
	}

	cline->sym = sym;

do_lookup:
	if (dladdr(sym, &dli) == 0)
		libc.memset(&dli, 0, sizeof(dli));

	if (!dli.dli_saddr) {
		c = '+';
		ofst = (unsigned long)sym -
			(unsigned long)dli.dli_fbase;
	} else if ((unsigned long)sym >
		   (unsigned long)dli.dli_saddr) {
		c = '+';
		ofst = (unsigned long)sym -
			(unsigned long)dli.dli_saddr;
	} else {
		c = '-';
		ofst = (unsigned long)dli.dli_saddr -
			(unsigned long)sym;
	}

	if (cline) {
		libc.snprintf(cline->str, MAX_LINE_LEN,
			      "%x:%s:%c0x%x:%s(%p):\n",
			      (unsigned int)sym,
			      dli.dli_sname ? dli.dli_sname : "??",
			      c, ofst, dli.dli_fname, dli.dli_fbase);
		__bt_printf(info, " :%d:%s", count, cline->str);
		return;
	}

	__bt_printf(info, " :%d:0x%x:%s:%c0x%x:%s(%p):\n",
		    count, (unsigned int)sym,
		    dli.dli_sname ? dli.dli_sname : "??",
		    c, ofst, dli.dli_fname, dli.dli_fbase);
}

static void print_bt_state(struct bt_state *state, struct log_info *info)
{
	int count;
	struct bt_frame *frame;
	unsigned long ofst;
	char c;
	const char *sym;

	bt_printf(info, "BT:START:%d:\n", state->count);
	for (count = 0; count < state->count; count++) {
		frame = &state->frame[count];
		print_info(info, count, frame->pc);
#ifdef VERBOSE_FRAME_INFO
		__br_printf(info, " : :R0=0x%08x,R1=0x%08x,R2=0x%08x,"
			     "R3=0x%08x,SP=0x%08x,LR=0x%08x\n",
			     frame->reg[0], frame->reg[1], frame->reg[2],
			     frame->reg[3], frame->sp, frame->lr);
#endif
	}

	if (state->dvm_bt && state->dvm_bt->count > 0)
		print_dvm_bt(&dvm, state->dvm_bt, info);

	/* bt_printf(info, "BT:END:"); */
}

static void __attribute__((noinline))
std_backtrace(void *logf, struct log_info *info)
{
	struct bt_state state;
	void *frames[MAX_BT_FRAMES];
	int count;

	libc.memset(&state, 0, sizeof(state));
	state.f = logf;

	state.count = libc.backtrace(frames, MAX_BT_FRAMES);

	for (count = 0; count < state.count; count++)
		state.frame[count].pc = frames[count];

	print_bt_state(&state, info);
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

	ip = __Unwind_GetIP(context);

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
#ifdef VERBOSE_FRAME_INFO
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 0,
			     _UVRSD_UINT32, &frame->regs[0]);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 1,
			     _UVRSD_UINT32, &frame->regs[1]);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 2,
			     _UVRSD_UINT32, &frame->regs[2]);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 3,
			     _UVRSD_UINT32, &frame->regs[3]);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 14,
			     _UVRSD_UINT32, &frame->lr);
	libc._Unwind_VRS_Get(context, _UVRSC_CORE, 13,
			     _UVRSD_UINT32, &frame->sp);
#endif
#endif

	frame->pc = (void *)ip;

	state->count++;

	if (state->count >= MAX_BT_FRAMES)
		return _URC_END_OF_STACK;
	return _URC_NO_REASON;
}

static inline int is_same_stack(struct bt_frame *current, void **last, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		if (current[i].pc != last[i])
			return 0;
	}
	return 1;
}


static void __attribute__((noinline))
unwind_backtrace(void *logf, struct log_info *info)
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
		bt_printf(info, "BT:REPEAT:%d:\n", *(info->last_stack_cnt));

	*(info->last_stack_cnt) = 1;
	*(info->last_stack_depth) = state.count;
	for (i = 0; i < state.count; i++)
		info->last_stack[i] = state.frame[i].pc;

	get_dvm_backtrace(&dvm, &state, &dvm_bt);

	print_bt_state(&state, info);
}


static pthread_key_t s_log_buffer_key = (pthread_key_t)-1;

void __attribute__((visibility("hidden"))) __attribute__((noinline))
log_backtrace(void *logf, struct log_info *info)
{
	char *buf = NULL;

	if (s_log_buffer_key == -1)
		if (libc.pthread_key_create(&s_log_buffer_key, NULL) != 0)
			return;

	buf = libc.pthread_getspecific(s_log_buffer_key);
	if (!buf) {
		int sz = LOG_BUFFER_SIZE
				+ ((MAX_BT_FRAMES) * sizeof(void *))
				+ (3 * sizeof(int));
		buf = (char *)libc.malloc(sz);
		if (!buf)
			return;
		libc.memset(buf, 0, sz);
		libc.pthread_setspecific(s_log_buffer_key, (void *)buf);
	}
	info->log_buffer = buf;
	info->log_pos = (int *)(buf + LOG_BUFFER_SIZE);
	info->last_stack_depth = (int *)(buf + LOG_BUFFER_SIZE + sizeof(int));
	info->last_stack_cnt = (int *)(buf + LOG_BUFFER_SIZE + 2*sizeof(int));
	info->last_stack = (void **)(buf + LOG_BUFFER_SIZE + 3*sizeof(int));

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

	bt_flush(info, logf);
}

void bt_free_log_buffer(void)
{
	if (s_log_buffer_key != (pthread_key_t)-1) {
		/*
		 * both the parent, and the new thread will
		 * re-create the necessary TLS keys/memory
		 */
		void *mem = libc.pthread_getspecific(s_log_buffer_key);
		if (mem) {
			libc.fflush(NULL);
			libc.free(mem);
			libc.pthread_setspecific(s_log_buffer_key, NULL);
		}
	}
}
