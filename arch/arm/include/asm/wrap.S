/*
 * arch/arm/include/asm/wrap.S
 * Copyright (C) 2012-2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * Apple's iOS assembler is not quite GNU compatible. This file attempts to
 * compile under both. For a method of merging the two see:
 *        http://psellos.com/2012/08/2012.08.arm-as-to-ios-4.html
 */
#define __concat(_a,_b) _a##_b
#define  _concat(_a,_b) __concat(_a,_b)
#define   concat(_a,_b)  _concat(_a,_b)

/*
 * Apple compatibility macros from:
 * http://psellos.com/2012/08/2012.08.arm-as-to-ios-4.html
 */
#if defined(__APPLE__)
#define LBL(s) concat(L,s)
#define MACRO0(nm)			.macro nm
#define MACRO1(nm, arg0)		.macro nm
#define MACRO2(nm, arg0, arg1)		.macro nm
#define MACRO3(nm, arg0, arg1, arg2)	.macro nm
#define marg(x,arg,pos)			concat(x,pos)
#define _marg(arg,pos)			pos
#define _amarg(arg,pos)			#pos
#define _FN(x) concat(_,x)
#define ENTRY(x) \
	.text; .align 4; .globl _FN(x);  _FN(x):
#define FUNC_LBL(x) \
	.text; .align 4; .globl _FN(x);  _FN(x):
#define END(x)
#if defined(MODEL_armv6)
        .machine  armv6
        .macro  cbz
        cmp     $0, #0
        beq     $1
        .endm
#else
        .machine  armv7
#endif
        .macro  .type
        .endm
        .macro  .size
        .endm
	.macro  .save
	.endm
#else /* non-Apple assembler (presumably GNU) */
#define LBL(s) .L ## s
#define MACRO0(nm)			.macro nm
#define MACRO1(nm, arg0)		.macro nm arg0
#define MACRO2(nm, arg0, arg1)		.macro nm arg0 arg1
#define MACRO3(nm, arg0, arg1, arg2)	.macro nm arg0 arg1 arg2
#define marg(x,arg,pos)			concat(x,arg)
#define _marg(arg,pos)			arg
#define _amarg(arg,pos)			#arg
#define _FN(x) concat(,x)
#define ENTRY(x) \
	.text; .align 4; .globl _FN(x); .type _FN(x),#function; _FN(x): .fnstart
#define FUNC_LBL(x) \
	.text; .align 4; .globl _FN(x); .type _FN(x),#function; _FN(x):
#define END(x) \
	.fnend; .size _FN(x), .-_FN(x)
#endif
/* End Apple compatibility macros */

/*
 * @wrap_lib
 *
 */
	/* .macro wrap_lib  $0 = libname, $1 = path */
	MACRO2(wrap_lib, libname, path)
	.section bss
	.align 4
	.globl marg(__libhandle_,\libname,$0)
marg(__libhandle_,\libname,$0):
	.word 0

	.align 4
	.globl marg(__wraplib_str_,\libname,$0)
marg(__wraplib_str_,\libname,$0):
	.asciz _amarg(\libname,$0)

	.align 4
	.globl marg(__wraplib_path_,\libname,$0)
marg(__wraplib_path_,\libname,$0):
	.asciz _amarg(\path,$1)
	.endm

/*
 * @symaddr - grab the address of a symbol using PC-relative addressing
 *
 * This annoying little macro is needed because Apple's assembler doesn't
 * do handy things like this for you... grrrrr.
 */
	MACRO2(symaddr, reg, symname) /* $0 = reg, $1 = symname */
	movw	_marg(\reg,$0), #:lower16:(_marg(\symname,$1) - . - 16)
	movt	_marg(\reg,$0), #:upper16:(_marg(\symname,$1) - . - 12)
	add	_marg(\reg,$0), pc
	.endm


/*
 * @save_caller_state - Save/copy arguments and prep for pass-thru function call
 *
 * At the end of the macro, 'rptr' will point to the saved value of the
 * caller's r0 (on the stack), and sp will point to a copy of the stack
 * registers.
 *
 * TODO: set the frame pointer properly for easier debugging...
 */
	MACRO1(save_caller_state, reg) /* $0 = reg */
	push	{lr}
	add	lr, sp, #4	/* lr points to stack at time of func entry */
	push	{r0-r12}
	add	_marg(\reg,$0), lr, #64	/* 64-bytes back into the caller's stack */
	/* copy the caller's stack state */
	ldmda	_marg(\reg,$0)!, {r1-r8}
	stmdb	sp!, {r1-r8}
	ldmda	_marg(\reg,$0)!, {r1-r8}
	stmdb	sp!, {r1-r8}
	ldr	_marg(\reg,$0), [lr]	/* get top of orig stack! (extra 4 bytes) */
	stmdb	sp!, {_marg(\reg,$0)}
	sub	_marg(\reg,$0), lr, #(4 + (13 * 4)) /* \reg = saved r0 (13 regs + lr) */
	.endm /* save_caller_state */


/*
 * @restore_caller_state - undo what 'save_caller_state' did
 *
 * TODO: restore the frame pointer
 */
	MACRO1(restore_caller_state, reg) /* $0 = rptr */
	mov	sp, _marg(\reg,$0) /* jumps over all saved stack space */
	pop	{r0-r12} /* overwrites \rptr! */
	pop	{lr}
	.endm

/*
 * @get_tls - get the TLS pointer value into a given register
 */
	MACRO1(get_tls,reg) /* $0 = rptr */
	mrc	p15, 0, _marg(\reg,$0), c13, c0, 3	/* get TLS pointer into reg arg $0 */
	.endm

/*
 * @func_entry - output the start of a function
 */
	MACRO2(func_entry, sym, pfx)
FUNC_LBL(_marg(\pfx,$1)_marg(\sym,$0))
	.endm
	
/*
 * @wrap_func - Create a wrapper entry point for a given symbol
 *
 * Given a symbol, "symname", this macro will create an entry point named
 * "elf_symname" which will automagically load the associated ELF library,
 * lookup the symbol, juggle the arguments and stack pointer, and then jump
 * into the ELF code! It also takes care of return values such that a caller
 * should be able to invoke "elf_symname" exactly as if calling "symname" in
 * the ELF library directly.
 */
	MACRO3(wrap_func_start, wraplib, wrapsym, pfx)
	.section bss
	.align 4
marg(__wrapstr_,\wrapsym,$1):
	.asciz _amarg(\wrapsym,$1)

	.align 4
marg(__wrapsym_,\wrapsym,$1):
	.word 0
	.endm

	MACRO3(wrap_func_end, wraplib, wrapsym, pfx)
ENTRY(_marg(\pfx,$2)_marg(\wrapsym,$1))
	/* save caller args, put pointer to r0 (on stack) in r10 */
	save_caller_state r10	

	/* lookup wrapped func address */
	symaddr	r11, marg(__wrapsym_,\wrapsym,$1)
	ldr	r11, [r11]
	cmp	r11, #0
	bne	1f
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	2f
	symaddr	r11, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r11]
	mov	r11, r0
1:
	/* call any defined "tracing" function */
#ifdef WRAP_TRACE_FUNC
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(WRAP_TRACE_FUNC)
#endif
	/* restore registers and make the original function call */
	ldmia	r10, {r0-r3}
	blx	r11
	stmia	r10, {r0-r3}	/* overwrite r0-r3 on the stored orig regs */

	/* call any defined "postlude" function */
#ifdef WRAP_POSTLUDE
	/* prototype: void postlude(const char *sym, uint32_t rval0, uint32_t rval1, uint32_t rval2) */
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(WRAP_POSTLUDE)
#endif
	/* restore stack and register state (including function return value) */
2:	restore_caller_state r10
	bx	lr
END(_marg(\pfx,$2)_marg(\wrapsym,$1))
	.endm /* wrap_func */

/*
 * @pass_func - Create an entry point that calls an entry point with the
 *              same name in a different library
 */
	MACRO2(pass_func_start, wraplib, wrapsym)
	.section bss
	.align 4
marg(__wrapstr_,\wrapsym,$1):
	.asciz _amarg(\wrapsym,$1)

	.align 4
marg(__wrapsym_,\wrapsym,$1):
	.word 0
	.endm

	MACRO2(pass_func_end, wraplib, wrapsym)
ENTRY(_marg(\wrapsym,$1))
	mov	ip, sp
	.save	{r0-r7, r10, r11}
	stmfd	sp!, {r0-r7, r10, r11}
	mov	r10, ip

	/* lookup wrapped func address */
	symaddr	r11, marg(__wrapsym_,\wrapsym,$1)
	ldr	r11, [r11]
	cmp	r11, #0
	bne	1f
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	2f
	symaddr	r11, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r11]
	mov	r11, r0
1:
	/* restore registers and make the original function call */
	/* NOTE: stack pointer is not in the correct place!! */
	ldmfd   ip, {r0, r1, r2, r3, r4, r5, r6}
	blx	r11

	/* save the possible return values in r0-r3 */
	stmia	r10, {r0-r3}	/* overwrite r0-r3 on the stored orig regs */

	/* restore stack and register state (including function return value) */
2:	
	ldmfd   sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r10, r11}
	bx	lr
END(_marg(\wrapsym,$1))
	.endm
