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
	MACRO0(get_wrapping_adr)
	symaddr	ip, s_wrapping_key
	ldr	ip, [ip]
	cmp	ip, #0
	beq	1f
	stmfd	sp!, {lr}
	get_tls lr
	ldr	ip, [lr, ip, lsl #2] /* ip = TLS[s_wrapping_key] */
	ldmfd	sp!, {lr}
1:
	.endm

/*
 * @set_wrapping_adr - set a thread-local address for (re)storing register state
 *
 * puts the address into the 'ip' register
 */
	MACRO1(set_wrapping_adr, reg)
	stmfd	sp!, {r11,lr}
	symaddr	lr, s_wrapping_key
	ldr	lr, [lr]
	cmp	lr, #0
	blt	1f
	get_tls r11
	str	_marg(\reg,$0), [r11, lr, lsl #2] /* TLS[s_wrapping_key] = \reg */
1:	ldmfd	sp!, {r11,lr}
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
	get_wrapping_adr
	cmp	ip, #0
	beq	3f
	stmfd	ip!, {r0-r11,lr}	/* emulate a stack push */
	push	{lr}			/* pop before calling the real function */
	set_wrapping_adr ip
	mov	_marg(\reg,$0), ip	/* ip = saved r0 */
	b	4f

3:
	stmfd	sp!, {r0-r11,lr}
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


/*
 * @restore_caller_state - undo what 'save_caller_state' did
 *
 * TODO: restore the frame pointer
 */
	MACRO1(restore_caller_state, reg) /* $0 = rptr */
	get_wrapping_adr
	cmp	ip, #0
	beq	8f
	/* bit0 == flag from the caller: TLS is valid, but uninitialized. */
	tst	ip, #1
	bic	ip, ip, #1
	beq	7f			/* flag _not_ set */

	/* flags is set: reset the TLS value, and unwind the stack */
	set_wrapping_adr ip
	b	8f			/* unwind the stack */

7:	ldm	ip!, {r0-r11,lr}	/* emulate a stack pop */
	set_wrapping_adr ip
	b	9f

8:	mov	sp, _marg(\reg,$0) /* jumps over all saved stack space */
	pop	{r0-r11,lr} /* overwrites \rptr! */
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
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	6f
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r5]
	mov	r5, r0
5:
	/* call any defined "tracing" function */
#ifdef WRAP_TRACE_FUNC
	/* prototype:
	   void wrapper(const char *symbol, void *regs, void *stack);
	 */
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	mov	r1, r4
	mov	r2, sp
	blx	_FN(WRAP_TRACE_FUNC)
#endif
	/* restore registers and make the original function call */
	pop	{lr}		/* pushed in save_caller_state */
	ldmia	r4, {r0-r3}
	blx	r5
	stmia	r4, {r0-r3}	/* overwrite r0-r3 on the stored orig regs */

	/* call any defined "postlude" function */
#ifdef WRAP_POSTLUDE
	/* prototype:
	   void postlude(const char *sym, uint32_t rval0,
			 uint32_t rval1, uint32_t rval2);
	 */
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(WRAP_POSTLUDE)
#endif
	/* restore stack and register state (including function return value) */
6:	restore_caller_state r4
	bx	lr
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
	save_caller_state r4

	/* lookup wrapped func address */
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	ldr	r5, [r5]
	cmp	r5, #0
	bne	5f
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	blx	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	6f
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r5]
	mov	r5, r0
5:
	/* restore registers and make the original function call */
	pop	{lr}		/* pushed in save_caller_state */
	ldmia	r4, {r0-r3}
	blx	r5
	stmia	r4, {r0-r3}	/* overwrite r0-r3 on the stored orig regs */

6:
	/* restore stack and register state (including function return value) */
	restore_caller_state r4
	bx	lr
END(_marg(\wrapsym,$1))
	.endm
