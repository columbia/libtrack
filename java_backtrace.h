/*
 * java_backtrace.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef JAVA_BACKTRACE_H
#define JAVA_BACKTRACE_H

#ifdef ANDROID

#include <stdint.h>
#include "backtrace.h"

#define DVM_DFLT_DSO_PATH "/system/lib/libdvm.so"

struct Thread;

typedef uint64_t ObjectId;
typedef uint64_t RefTypeId;
typedef uint64_t FrameId;
typedef uint32_t MethodId;

struct JdwpLocation {
    uint8_t     typeTag;	/* class or interface? */
    RefTypeId   classId;	/* method->clazz */
    MethodId    methodId;	/* method in which "idx" resides */
    uint64_t    idx;		/* relative index into code block */
};

struct dvm_frame {
	FrameId id;
	const char *class_name;
	const char *method_name;
};

struct dvm_bt {
	char *thread_name;	/* should be free'd */
	int count;
	struct dvm_frame frame[MAX_BT_FRAMES];
};

struct dvm_iface {
	void *dso;

	void *dvmCallMethodSym;

	ObjectId (*dvmDbgGetThreadSelfId)(void);

	int (*dvmDbgGetThreadFrameCount)(ObjectId threadId);

	int (*dvmDbgGetThreadFrame)(ObjectId threadId, int num,
				    FrameId *pFrameId,
				    struct JdwpLocation *pLoc);

	const char *(*dvmDbgGetSignature)(RefTypeId refTypeId);

	const char *(*dvmDbgGetMethodName)(RefTypeId refTypeId, MethodId id);

	/* result must be free'd */
	char *(*dvmDbgGetThreadName)(ObjectId threadId);
};

extern void init_dvm_iface(struct dvm_iface *dvm, const char *dso_path);

extern void get_dvm_backtrace(struct dvm_iface *dvm,
			      struct bt_state *bt_state,
			      struct dvm_bt *dvm_bt);

extern void print_dvm_bt(FILE *logf, struct dvm_bt *dvm_bt, struct timeval *tv);

#else /* !ANDROID */

#define DVM_DFLT_DSO_PATH "/dont/use/this/path"

struct dvm_iface {
	char dso;
};

struct dvm_bt {
	char count;
};

static inline void init_dvm_iface(struct dvm_iface *dvm, const char *dso_path)
{
	(void)dso_path;
	if (dvm)
		dvm->dso = 1;
	return;
}

static inline void get_dvm_backtrace(struct dvm_iface *dvm,
				     struct bt_state *bt_state,
				     struct dvm_bt *dvm_bt)
{
	(void)dvm;
	(void)bt_state;
	dvm_bt->count = 0;
	return;
}

static inline void print_dvm_bt(FILE *logf, struct dvm_bt *dvm_bt,
				struct timeval *tv)
{
	(void)logf;
	(void)dvm_bt;
	(void)tv;
	return;
}

#endif /* ANDROID */

#endif /* JAVA_BACKTRACE_H */
