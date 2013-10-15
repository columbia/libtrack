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
 * Apple compatibility macros adapted from:
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
#define FUNC_LBL(x) \
	.text; .align 4; .globl _FN(x);  _FN(x):
#define ENTRY(x) \
	FUNC_LBL(x); \
	.arm
#define END(x)
#define STRING(nm, val) \
	.text; .globl nm; nm: .asciz val

	.macro unwind_linkage
	.endm
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
#define FUNC_LBL(x) \
	.text; .align 4; .globl _FN(x); _FN(x):
#define ENTRY(x) \
	FUNC_LBL(x); \
	.arm; .fnstart
#define END(x) \
	.type _FN(x), %function; .fnend; .size _FN(x), .-_FN(x)
#define STRING(nm, val) \
	.text; .globl nm; nm: .asciz val

	.macro unwind_linkage
	.save {lr}
	/*
	.save {r0-r11,lr}
	.pad #68
	*/
	.endm
#endif
/* End Apple compatibility macros */

/*
 * @get_tls - get the TLS pointer value into a given register
 */
	MACRO1(get_tls,reg) /* $0 = rptr */
	mrc	p15, 0, _marg(\reg,$0), c13, c0, 3	/* get TLS pointer into reg arg $0 */
	.endm

/*
 * @wrap_lib
 *
 */
	/* .macro wrap_lib  $0 = libname, $1 = path */
	MACRO2(wrap_lib, libname, path)
	.bss
	.align 4
	.globl marg(__libhandle_,\libname,$0)
marg(__libhandle_,\libname,$0):
	.word 0
STRING(marg(__wraplib_str_,\libname,$0), _amarg(\libname,$0))
STRING(marg(__wraplib_path_,\libname,$0), _amarg(\path,$1))
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
 * @get_wrapping_adr - get a thread-local address for (re)storing register state
 *
 * puts the address into the 'ip' register
 */
	MACRO2(get_wrapping_adr, reg, tmp) /* $0 = reg, $1 = tmp */
	symaddr	_marg(\reg,$0), s_wrapping_key
	ldr	_marg(\reg,$0), [_marg(\reg,$0)]
	cmp	_marg(\reg,$0), #0
	beq	0f
	get_tls _marg(\tmp,$1)
	/* load: reg = TLS[s_wrapping_key] */
	ldr	_marg(\reg,$0), [_marg(\tmp,$1), _marg(\reg,$0), lsl #2]
0:
	.endm

/*
 * @set_wrapping_adr - set a thread-local address for (re)storing register state
 *
 * puts the address into the 'ip' register
 */
	MACRO3(set_wrapping_adr, reg, tmp1, tmp2)
	symaddr	_marg(\tmp1,$1), s_wrapping_key
	ldr	_marg(\tmp1,$1), [_marg(\tmp1,$1)]
	cmp	_marg(\tmp1,$1), #0
	blt	1f
	get_tls _marg(\tmp2,$2)
	/* TLS[s_wrapping_key] = reg */
	str	_marg(\reg,$0), [_marg(\tmp2,$2), _marg(\tmp1,$1), lsl #2]
1:
	.endm

/*
 * @save_caller_state - Save/copy arguments and prep for pass-thru function call
 *
 * At the end of the macro, 'rptr' will point to the saved value of the
 * caller's r0 (on the stack), and sp will point to a copy of the stack
 * registers.
 */
	MACRO1(save_caller_state, reg) /* $0 = reg */
	unwind_linkage
	push	{lr}
	get_wrapping_adr ip, lr
	cmp	ip, #0
	beq	3f
	stmfd	ip!, {r0-r11}		/* emulate a stack push */
	set_wrapping_adr ip, r0, r1
	mov	_marg(\reg,$0), ip	/* ip = saved r0 */
	ldr	lr, [sp, #4]		/* restore original lr */
	b	4f

3:
	push	{r0-r11}
	add	lr, sp, #(13 * 4)	/* lr points to stack at time of func entry */
	add	ip, lr, #64	/* 64-bytes back into the caller's stack */
	/* copy the caller's stack state */
	ldmda	ip!, {r1-r8}
	stmdb	sp!, {r1-r8}
	ldmda	ip!, {r1-r8}
	stmdb	sp!, {r1-r8}
	ldr	ip, [lr]	/* get top of orig stack (extra 4 bytes) */
	stmdb	sp!, {ip}
	sub	lr, #(13 * 4) /* lr = saved r0 */
	mov	_marg(\reg,$0), lr
	ldr	lr, [lr, #(12 * 4)]	/* restore original lr */
4:
	.endm /* save_caller_state */


/**
 * @restore_caller_state - undo what 'save_caller_state' did
 *
 * @param reg register pointing to memory (stack or TLS) holding
 *            saved register state
 */
	MACRO1(restore_caller_state, reg) /* $0 = rptr */
	push	{ip}		/* save this as it may be used outside the macro */
	get_wrapping_adr ip, r0
	cmp	ip, #0
	beq	7f

	/* bit0 == flag from the caller: TLS is valid, but uninitialized. */
	tst	ip, #1
	bic	ip, ip, #1
	beq	8f		/* flag _not_ set: restore from TLS */

	/* flags is set: reset the TLS value, and unwind the stack */
	set_wrapping_adr ip, r0, r1
7:	pop	{ip}
	mov	sp, _marg(\reg,$0)	/* jumps over all saved stack space */
	pop	{r0-r11,lr}		/* overwrites \rptr! */
	b	9f

8:	/* pop register state from the TLS "stack" */
	ldm	ip!, {r0-r11}	/* emulate a stack pop */
	push	{r0}
	set_wrapping_adr ip, lr, r0
	pop	{r0,ip,lr}
9:
	.endm

/*
 * @func_alias - output the start of a function
 */
	MACRO2(func_alias, sym, pfx)
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
	.bss
	.align 4
marg(__wrapsym_,\wrapsym,$1):
	.word 0
STRING(marg(__wrapstr_,\wrapsym,$1), _amarg(\wrapsym,$1))
	.endm


	MACRO3(wrap_func_end, wraplib, wrapsym, pfx)
ENTRY(_marg(\pfx,$2)_marg(\wrapsym,$1))
	/* save caller args, put pointer to r0 (on stack) in r4 */
	save_caller_state r4

	/* lookup wrapped func address */
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	ldr	r5, [r5]
	cmp	r5, #0
	bne	5f
	mov	r5, lr	/* save the original lr in r5 */
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	6f	/* will branch to original lr */
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r5]
	mov	r5, r0

5:	/* call any defined "tracing" function */
#ifdef WRAP_TRACE_FUNC
	/* prototype:
	   void wrapper(const char *symbol, void *regs, void *stack);
	 */
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	mov	r1, r4
	mov	r2, #13		/* keep this in-sync with save_caller_state */
	mov	r3, sp
	blx	_FN(WRAP_TRACE_FUNC)
#endif
	/* restore registers and make the original function call */
6:	mov	ip, r5
	restore_caller_state r4
	bx	ip
END(_marg(\pfx,$2)_marg(\wrapsym,$1))
	.endm /* wrap_func */

/*
 * @pass_func - Create an entry point that calls an entry point with the
 *              same name in a different library
 */
	MACRO2(pass_func_start, wraplib, wrapsym)
	.bss
	.align 4
marg(__wrapsym_,\wrapsym,$1):
	.word 0
STRING(marg(__wrapstr_,\wrapsym,$1), _amarg(\wrapsym,$1))
	.endm

	MACRO2(pass_func_end, wraplib, wrapsym)
ENTRY(_marg(\wrapsym,$1))
	/* lookup wrapped func address */
	symaddr	ip, marg(__wrapsym_,\wrapsym,$1)
	ldr	ip, [ip]
	cmp	ip, #0
	bne	6f
	/* search for the symbol and cache it */
	save_caller_state r4
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	mov	r5, lr
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	moveq	ip, r5	/* original lr (return to caller) */
	beq	5f
	/* cache the symbol for next time */
	symaddr	ip, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [ip]
	mov	ip, r0
5:	restore_caller_state r4
6:	bx	ip
END(_marg(\wrapsym,$1))
	.endm
