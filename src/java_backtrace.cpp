/*
 * java_backtrace.cpp
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#pragma GCC diagnostic ignored "-fpermissive"
#ifdef ANDROID

#include <string>

#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>

#include "wrap_lib.h"
#include "java_backtrace.h"

/*
 * TODO: use libgccdemangle.so to auto-mangle these names?
 */

/*
 * gcc mangled names of:
 * 	void dvmCallMethod(Thread* self, const Method* method,
 * 			   Object* obj, JValue* pResult, ...);
 * and:
 *	void dvmCallMethodA(Thread* self, const Method* method,
 *			    Object* obj,bool fromJni, JValue* pResult,
 *			    const jvalue* args);
 */
#define DVM_CALL_METHOD   "_Z13dvmCallMethodP6ThreadPK6MethodP6ObjectP6JValuez"
#define DVM_CALL_METHOD_A "_Z14dvmCallMethodAP6ThreadPK6MethodP6ObjectbP6JValuePK6jvalue"
#define DVM_CALL_METHOD_V "_Z14dvmCallMethodVP6ThreadPK6MethodP6ObjectbP6JValueSt9__va_list"
#define DVM_CALL_JNI_METHOD     "_Z16dvmCallJNIMethodPKjP6JValuePK6MethodP6Thread"
#define DVM_CALL_JNI_METHOD_CHK "_Z21dvmCheckCallJNIMethodPKjP6JValuePK6MethodP6Thread"

/*
 *
 * gcc mangled names of:
 * 	Thread *dvmThreadSelf();
 * 	int dvmComputeExactFrameDepth(const void* fp);
 * 	void dvmFillStackTraceArray(const void* fp,
 * 				    const struct Method** array,
 * 				    size_t length);
 * 	std::string dvmGetThreadName(struct Thread* thread);
 * 	std::string dvmHumanReadableMethod(const struct Method* method,
 * 					   bool withSignature);
 */
#define sym_DVM_ThreadSelf		_Z13dvmThreadSelfv
#define sym_DVM_ComputeExactFrameDepth	_Z25dvmComputeExactFrameDepthPKv
#define sym_DVM_FillStackTraceArray	_Z22dvmFillStackTraceArrayPKvPPK6Methodj
#define sym_DVM_HumanReadableMethod	_Z22dvmHumanReadableMethodPK6Methodb
#define sym_DVM_GetThreadName		_Z16dvmGetThreadNameP6Thread

struct dvm_iface dvm __hidden;

#define TLS_DVM_STACK_SZ \
	(((MAX_BT_FRAMES) * sizeof(struct Method *)) + (2 * sizeof(int)))

#define dvmstk_last_depth(buf) ((int *)((char *)(buf)))
#define dvmstk_repeat(buf)     ((int *)((char *)(buf) + sizeof(int)))
#define dvmstk_metharr(buf)    ((struct Method **)((char *)(buf) + 2*sizeof(int)))

_static char main_dvmstack[TLS_DVM_STACK_SZ];

_static void *_find_symbol_end(void *sym_start)
{
	Dl_info dli;
	void *sym_end = sym_start;

	/*
	 * This is a bit of a hack: try to find the end of a symbol by
	 * repeatedly calling dladdr() until the symbol name changes...
	 */
	while (1) {
		void *sym = (void *)((char *)sym_end + 4);
		if (dladdr(sym, &dli) == 0)
			break;
		if (dli.dli_saddr != sym_start)
			break;
		sym_end = sym;
	}

	return sym_end;
}

extern "C"
void __hidden init_dvm_iface(struct dvm_iface *dvm, const char *dso_path)
{
	int ii;

	if (dvm->dso)
		return;

	dvm->dso = (void *)1;
	dvm->dso = dlopen(dso_path, RTLD_NOW | RTLD_LOCAL);
	if (!dvm->dso) {
		libc_log("E:Could not open libdvm (%s)!", dso_path);
		return;
	}

	/* initialize the minimal Dalvik debug interface */
#define __init_sym(iface,sym,mem) \
	do { \
		if ((iface)->mem) \
			break; \
		(iface)->mem = dlsym((iface)->dso, #sym); \
		if ((iface)->mem) \
			break; \
		(iface)->mem = dlsym((iface)->dso, "_" #sym); \
		if ((iface)->mem) \
			break; \
		BUG(0xD0); \
	} while (0)
#define _init_sym(iface,sym,mem) \
	__init_sym(iface, sym, mem)
#define init_sym(IFACE,SYM) \
	_init_sym(IFACE, sym_DVM_ ## SYM, dvm ## SYM)

	init_sym(dvm, ThreadSelf);
	init_sym(dvm, ComputeExactFrameDepth);
	init_sym(dvm, FillStackTraceArray);
	init_sym(dvm, GetThreadName);
	init_sym(dvm, HumanReadableMethod);

#undef init_sym
#undef _init_sym
#undef __init_sym

	/*
	 * Now find the functions that indicate
	 * we are within the Java call stack
	 */
	dvm->dvmCallMethodSym[0][0] = dlsym(dvm->dso, DVM_CALL_METHOD);
	dvm->dvmCallMethodSym[1][0] = dlsym(dvm->dso, DVM_CALL_METHOD_A);
	dvm->dvmCallMethodSym[2][0] = dlsym(dvm->dso, DVM_CALL_METHOD_V);
	dvm->dvmCallMethodSym[3][0] = dlsym(dvm->dso, DVM_CALL_JNI_METHOD);
	dvm->dvmCallMethodSym[4][0] = dlsym(dvm->dso, DVM_CALL_JNI_METHOD_CHK);

	/*
	 * note: if either of these fail, then we won't ever find a
	 * java/dalvik backtrace, but we won't risk instability either
	 */
	for (ii = 0; ii < (int)ARRAY_SZ(dvm->dvmCallMethodSym); ii++) {
		if (!dvm->dvmCallMethodSym[ii][0]) {
			libc_log("W:Couldn't find dvmCallMethod[%d] in libdvm.so", ii);
		} else {
			void *end;
			end = _find_symbol_end(dvm->dvmCallMethodSym[ii][0]);
			dvm->dvmCallMethodSym[ii][1] = end;
			/*
			libc_log("I:dvmCallMethod[%d][%p-%p]:", ii,
				 dvm->dvmCallMethodSym[ii][0],
				 dvm->dvmCallMethodSym[ii][1]);
			 */
		}
	}

	dvm->valid = 1;
	return;
}

extern "C"
void __hidden init_dvm(struct dvm_iface *dvm)
{
	if (!dvm)
		return;
	if (!dvm->dso && !dvm->valid)
		init_dvm_iface(dvm, DVM_DFLT_DSO_PATH);
}

extern "C"
void __hidden close_dvm_iface(struct dvm_iface *dvm)
{
	void *dso;

	dso = dvm->dso;
	dvm->valid = 0;
	if (!dvm->dso || dvm->dso == (void *)1)
		return;
	dvm->dso = (void *)1;
	dlclose(dso);
	dvm->dso = NULL;
}

_static inline int _in_range(void *v, void *range[])
{
	if (v >= range[0] && v <= range[1])
		return 1;
	return 0;
}

extern "C"
void __hidden get_dvm_backtrace(struct tls_info *tls, struct dvm_iface *dvm,
				struct bt_state *bt_state, struct dvm_bt *dvm_bt)
{
	int cnt;

	if (!dvm->valid || !tls)
		return;

	dvm_bt->count = 0;

	/*
	 * Search through the native backtrace for the java stack indicators.
	 * It should be faster to search up from the bottom of the stack
	 * because the dvmCallMethod function is generally invoked from
	 * platform-specific assembly quite early in the backtrace.
	 */
	cnt = bt_state->count;
	while (--cnt >= 0) {
		int ii;
		void *addr = bt_state->frame[cnt].pc;
		for (ii = 0; ii < (int)ARRAY_SZ(dvm->dvmCallMethodSym); ii++)
			if (_in_range(addr, dvm->dvmCallMethodSym[ii]))
				goto do_dvm_bt;
	}
	return;

	/*
	 * We have a call stack that's from a Java/Dalvik thread:
	 * get the backtrace!
	 */
do_dvm_bt:
	{
		struct Thread *self;
		uint32_t *fp = NULL;
		char *tname;
		struct Method **mlist;
		int r;

		self = dvm->dvmThreadSelf();
		if (!self)
			return;
		fp = self->interpSave.curFrame;
		if (!fp)
			return;

		/*
		 * There is a bug in dvmGetThreadName() that causes this
		 * to crash when we call it before the thread has a
		 * Java/Dalvik name, but after a Java function has been
		 * invoked. This happens primarily at system boot...
		tname = tls->dvm_threadname;
		if (!tname[0]) {
			int len;
			std::string nm = dvm->dvmGetThreadName(self);
			len = nm.length();
			if (len >= TLS_MAX_STRING_LEN)
				len = TLS_MAX_STRING_LEN - 1;
			libc.memcpy(tname, nm.c_str(), len);
			libc_log("I:DalvikThreadName:%s:", tname);
		}
		*/

		mlist = dvm_bt->mlist;
		dvm_bt->count = dvm->dvmComputeExactFrameDepth(fp);
		if (dvm_bt->count > MAX_BT_FRAMES) {
			/*
			 * we need an array big enough for this frame
			 * because the dvm fill stack array function
			 * doesn't care how big our array really is...
			 */
			mlist = libc.malloc((dvm_bt->count + 1) * sizeof(struct Method *));
			if (!mlist) {
				dvm_bt->count = 0;
				return;
			}
			dvm_bt->count = MAX_BT_FRAMES;
		}

		/*
		 * Grrr. This API doesn't respect the 'length' parameter.
		 * It just sends out an error message (if you're lucky enough
		 * to have copiled without NDEBUG), and continues to mash on
		 * your memory even though it's out of bounds...
		 */
		dvm->dvmFillStackTraceArray(fp, mlist, dvm_bt->count);

		if (mlist != dvm_bt->mlist) {
			/* copy only the portion of data back that fits */
			libc.memcpy(dvm_bt->mlist, mlist,
				    dvm_bt->count * sizeof(struct Method *));
			libc.free(mlist);
		}
	}

	return;
}

_static char *__setup_dvmstack(struct tls_info *tls, int **last_depth,
			       int **last_repeat, struct Method ***last_meth)
{
	char *last_stack;
	if (!tls)
		return NULL;

	last_stack = tls->dvmstack;
	if (!last_stack) {
		if (is_main())
			last_stack = main_dvmstack;
		else
			last_stack = (char *)libc.malloc(TLS_DVM_STACK_SZ);
		if (!last_stack)
			return NULL;
		libc.memset(last_stack, 0, TLS_DVM_STACK_SZ);
		tls->dvmstack = last_stack;
	}

	*last_depth = dvmstk_last_depth(last_stack);
	*last_repeat = dvmstk_repeat(last_stack);
	*last_meth = dvmstk_metharr(last_stack);

	return last_stack;
}

extern "C"
void __hidden tls_release_dvmstack(struct tls_info *tls)
{
	char *stack;

	if (!tls)
		return;

	stack = tls->dvmstack;
	if (!stack)
		return;

	libc.memset(stack, 0, TLS_DVM_STACK_SZ);

	if (stack != main_dvmstack)
		libc.free(tls->dvmstack);

	tls->dvmstack = NULL;
}

_static int compare_traces(struct tls_info *tls,
			   struct dvm_iface *dvm, struct dvm_bt *dvm_bt)
{
	char *last_stack = NULL;
	int ii, ret;
	int *last_depth, *last_repeat;
	struct Method **last_meth;

	last_stack = __setup_dvmstack(tls, &last_depth, &last_repeat, &last_meth);
	if (!last_stack)
		return 0;

	if (*last_depth != dvm_bt->count) {
		/* this is _not_ a repeated trace, save it for next time */
		ret = *last_repeat;
		goto save_current_stack;
	}

	for (ii = 0; ii < *last_depth; ii++) {
		if (last_meth[ii] != dvm_bt->mlist[ii]) {
			/*
			 * It's not a repeated trace, but we had a previously
			 * repeating trace. Save the current stack and return
			 * the number of times the previous stack repeated.
			 */
			ret = *last_repeat;
			goto save_current_stack;
		}
	}

	*last_repeat += 1;
	return -1; /* repeat frame, don't print anything yet */

save_current_stack:
	*last_depth = dvm_bt->count;
	for (ii = 0; ii < *last_depth; ii++)
		last_meth[ii] = dvm_bt->mlist[ii];
	*last_repeat = 1;
	return ret;
}

_static void print_dvm_sym(struct tls_info *tls, struct dvm_iface *dvm,
			  int count, struct Method *m)
{
	struct bt_line_cache *cache = NULL;
	struct bt_line *cline;

	if (!dvm->valid)
		return;

	cline = bt_cache_fetch((void *)m, &cache);
	if (!cline)
		goto do_lookup;

	if (cline->sym == (void *)m) {
		__bt_printf(tls, " :%d:%s", count, cline->str);
		return;
	}

	cline->sym = (void *)m;

do_lookup:
	std::string name;
	name = dvm->dvmHumanReadableMethod(m, DVM_BT_GET_SIGNATURE);
	if (cline) {
		libc.snprintf(cline->str, MAX_LINE_LEN, "%s:\n", name.c_str());
		__bt_printf(tls, " :%d:%s", count, cline->str);
		return;
	}

	__bt_printf(tls, " :%d:%s:\n", count, name.c_str());
}

extern "C"
void __hidden print_dvm_bt(struct tls_info *tls, struct dvm_iface *dvm,
			   struct dvm_bt *dvm_bt)
{
	int ii;

	ii = compare_traces(tls, dvm, dvm_bt);
	if (ii < 0) {
		__bt_printf(tls, "DVM:BT_REPEAT:1:\n");
		return;
	}
	/* else if (ii > 1)
		__bt_printf(tls, "DVM:BT_REPEAT:%d:\n", ii);
	*/

	bt_printf(tls, "DVM:BT_START:%d:\n", dvm_bt->count);
	for (ii = 0; ii < dvm_bt->count; ii++) {
		print_dvm_sym(tls, dvm, ii, dvm_bt->mlist[ii]);
	}

	/* bt_printf(tls, "DVM:BT_END:\n"); */
	return;
}
#endif /* ANDROID */
