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
#include "wrap_tls.h"

//#define BT_DONT_WRITE_LOG

#define MAX_BT_FRAMES 128
#define MAX_LINE_LEN  256

struct bt_frame {
	void *pc;
	unsigned long sp;
#ifdef VERBOSE_FRAME_INFO
	unsigned long reg[4]
	unsigned long lr;
#endif
};

struct dvm_bt;

struct bt_state {
	struct bt_frame frame[MAX_BT_FRAMES];
	int count;
	int nskip;
	struct dvm_bt *dvm_bt;
	void *f;
};

struct bt_line {
	void     *sym;
	uint32_t  usage;
	char      str[MAX_LINE_LEN];
};

#define BT_CACHE_BITS 9
#define BT_CACHE_SZ   (1 << BT_CACHE_BITS)
#define BT_CACHE_MSK  (BT_CACHE_SZ - 1)

static inline uint16_t bt_hash(void *sym)
{
	uint16_t a, b;
	a = (uint32_t)(sym) & 0xFFFF;
	b = ((uint32_t)(sym) >> 16) & 0xFFFF;
	return (  (a & BT_CACHE_MSK)
		+ ((a >> BT_CACHE_BITS) & BT_CACHE_MSK)
		+ (b & BT_CACHE_MSK)
		+ ((b >> BT_CACHE_BITS) & BT_CACHE_MSK)) & BT_CACHE_MSK;
}

/*
 * With a 256 byte line, this is approximately 528k per thread
 */
struct bt_line_cache {
	int usage;
	int hit;
	int miss;
	struct bt_line c[BT_CACHE_SZ][2];
};


extern struct bt_line *bt_cache_fetch(void *sym, struct bt_line_cache **cache_out);

extern void log_backtrace(struct tls_info *tls);

#define __bt_logpos(buf) \
	((int *)(buf))

#define __bt_logbuf(buf) \
	((char *)((char *)(buf) + sizeof(int)))

#define __bt_last_stack_depth(buf) \
	((int *)((char *)(buf) + (sizeof(int)) + LOG_BUFFER_SIZE))

#define __bt_last_stack_cnt(buf) \
	((int *)((char *)(buf) + (2 * sizeof(int)) + LOG_BUFFER_SIZE))

#define __bt_last_stack(buf) \
	((void *)((char *)(buf) + (3 * sizeof(int)) + LOG_BUFFER_SIZE))

#endif /* WRAPPER_BACKTRACE_H */
