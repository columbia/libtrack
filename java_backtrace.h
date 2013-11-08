/*
 * java_backtrace.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef JAVA_BACKTRACE_H
#define JAVA_BACKTRACE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#ifdef ANDROID

#include <stdint.h>
#include "backtrace.h"

#ifndef DVM_BT_GET_SIGNATURE
#define DVM_BT_GET_SIGNATURE false
#endif

#define DVM_DFLT_DSO_PATH "/system/lib/libdvm.so"

#if defined(HAVE_ENDIAN_H)
# include <endian.h>
#else /*not HAVE_ENDIAN_H*/
# define __BIG_ENDIAN 4321
# define __LITTLE_ENDIAN 1234
# if defined(HAVE_LITTLE_ENDIAN)
#  define __BYTE_ORDER __LITTLE_ENDIAN
# else
#  define __BYTE_ORDER __BIG_ENDIAN
# endif
#endif /*not HAVE_ENDIAN_H*/

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;
typedef int8_t   s1;
typedef int16_t  s2;
typedef int32_t  s4;
typedef int64_t  s8;

struct Object;
struct Method;
struct DvmDex;

typedef union _JValue {
#if defined(HAVE_LITTLE_ENDIAN)
    u1      z;
    s1      b;
    u2      c;
    s2      s;
    s4      i;
    s8      j;
    float   f;
    double  d;
    struct Object *l;
#endif
#if defined(HAVE_BIG_ENDIAN)
    struct {
        u1    _z[3];
        u1    z;
    };
    struct {
        s1    _b[3];
        s1    b;
    };
    struct {
        u2    _c;
        u2    c;
    };
    struct {
        s2    _s;
        s2    s;
    };
    s4      i;
    s8      j;
    float   f;
    double  d;
    void   *l;
#endif
} JValue;

struct InterpSaveState {
    const uint16_t      *pc;         // Dalvik PC
    uint32_t            *curFrame;   // Dalvik frame pointer
    const struct Method *method;    // Method being executed
    struct DvmDex       *methodClassDex;
    JValue               retval;
    void                *bailPtr;
    int                  debugTrackedRefStart;
    struct InterpSaveState *prev;  // To follow nested activations
} __attribute__ ((__packed__));

struct Thread {
	struct InterpSaveState interpSave;
	uint32_t threadId;
	/* XXX: stuff we don't care about */
};

#if 0
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
#endif

struct dvm_bt {
	int count;
	struct Method *mlist[MAX_BT_FRAMES];
};

struct dvm_iface {
	void *dso;

	void *dvmCallMethodSym[3][2];

	struct Thread *(*dvmThreadSelf)(void);

	int (*dvmComputeExactFrameDepth)(const void* fp);

	void (*dvmFillStackTraceArray)(const void* fp,
				       const struct Method** array,
				       size_t length);
#ifdef __cplusplus
	std::string (*dvmGetThreadName)(struct Thread* thread);
	std::string (*dvmHumanReadableMethod)(const struct Method* method,
					      bool withSignature);
#else
	void *dvmGetThreadName;
	void *dvmHumanReadableMethod;
#endif

#if 0
	/* Dalvik debug interface: doesn't work... */
	void (*dvmDbgConnected)(void);
	void (*dvmDbgDisconnected)(void);

	ObjectId (*dvmDbgGetThreadSelfId)(void);
	/* result must be free'd */
	char *(*dvmDbgGetThreadName)(ObjectId threadId);

	int (*dvmDbgGetThreadFrameCount)(ObjectId threadId);

	int (*dvmDbgGetThreadFrame)(ObjectId threadId, int num,
				    FrameId *pFrameId,
				    struct JdwpLocation *pLoc);

	const char *(*dvmDbgGetSignature)(RefTypeId refTypeId);

	const char *(*dvmDbgGetMethodName)(RefTypeId refTypeId, MethodId id);
#endif
};

extern void init_dvm_iface(struct dvm_iface *dvm, const char *dso_path);

extern void close_dvm_iface(struct dvm_iface *dvm);

extern void get_dvm_backtrace(struct dvm_iface *dvm,
			      struct bt_state *bt_state,
			      struct dvm_bt *dvm_bt);

extern void print_dvm_bt(struct dvm_iface *dvm, struct dvm_bt *dvm_bt,
			 struct log_info *info);

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

static void close_dvm_iface(struct dvm_iface *dvm)
{
	if (dvm)
		dvm->dso = 0;
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

static inline void print_dvm_bt(struct dvm_iface *dvm, FILE *logf,
				struct dvm_bt *dvm_bt, struct timeval *tv)
{
	(void)logf;
	(void)dvm_bt;
	(void)tv;
	return;
}

#endif /* ANDROID */

__END_DECLS

#endif /* JAVA_BACKTRACE_H */
