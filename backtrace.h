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
#define MAX_LINE_LEN  256

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

struct bt_line {
	void     *sym;
	uint32_t  usage;
	char      str[MAX_LINE_LEN];
};

#define BT_CACHE_BITS 10
#define BT_CACHE_SZ   (1 << BT_CACHE_BITS)
#define BT_CACHE_MSK  (BT_CACHE_SZ - 1)

static inline uint16_t bt_hash(void *sym)
{
	uint16_t a, b;
	a = (uint32_t)(sym) & 0xFFFF;
	b = ((uint32_t)(sym) >> 16) & 0xFFFF;
	return ((a >> 2) + (b & 0x3FF) + ((b >> 10) & 0x3F)) & BT_CACHE_MSK;
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


struct bt_line *bt_cache_fetch(void *sym, struct bt_line_cache **cache_out);

#endif /* WRAPPER_BACKTRACE_H */
