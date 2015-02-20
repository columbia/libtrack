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
	.text; .code 32; .align 4; .globl _FN(x); .type _FN(x), %function; _FN(x):
#define ENTRY(x) \
	FUNC_LBL(x); \
	.fnstart
#define END(x) \
	.fnend; .size _FN(x), .-_FN(x)
#define STRING(nm, val) \
	.text; .globl nm; nm: .asciz val

	.macro unwind_linkage
	.save {r0-r11,lr}
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
 * (3 instructions)
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
 * @get_wrapping_tls_val - get a thread-local address for (re)storing register state
 *
 * puts the address into the 'reg' register, stomps on 'tmp' register as well
 */
	MACRO2(get_wrapping_tls_val, reg, tmp) /* $0 = reg, $1 = tmp */
	symaddr	_marg(\reg,$0), s_wrapping_key
	ldr	_marg(\reg,$0), [_marg(\reg,$0)]
	cmp	_marg(\reg,$0), #0
	ble	0f
	get_tls _marg(\tmp,$1)
	/* load: reg = TLS[s_wrapping_key] */
	ldr	_marg(\reg,$0), [_marg(\tmp,$1), _marg(\reg,$0), lsl #2]
0:
	.endm

/*
 * @set_wrapping_tls_val - set a thread-local address for (re)storing register state
 * (8 instructions)
 *
 * puts the address into the 'ip' register
 */
	MACRO3(set_wrapping_tls_val, reg, tmp1, tmp2)
	symaddr	_marg(\tmp1,$1), s_wrapping_key
	ldr	_marg(\tmp1,$1), [_marg(\tmp1,$1)]
	cmp	_marg(\tmp1,$1), #0
	ble	1f
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
	MACRO2(save_caller_state, r0reg, spreg)
	unwind_linkage
	push	{lr}
	mov	lr, sp
	push	{r0-r11}
	mov	_marg(\r0reg,$0), sp
	/* mov	_marg(\nreg,$1), #13 */		/* r0-r11+lr = 13 registers */
	add	_marg(\spreg,$1), lr, #4	/* pointer to incoming stack */
	ldr	lr, [lr]			/* restore original lr */
	.endm /* save_caller_state */


/**
 * @restore_caller_state - undo what 'save_caller_state' did
 *
 * @param reg register pointing to memory (stack or TLS) holding
 *            saved register state
 */
	MACRO1(restore_caller_state, reg) /* $0 = rptr */
	pop	{r0-r11,lr}
	.endm

/*
 * @func_alias - output the start of a function
 */
	MACRO2(func_alias, sym, pfx)
FUNC_LBL(_marg(\pfx,$1)_marg(\sym,$0))
	.endm

/*
 * @arch_wrapped_return - handle low-level bits of return value interposition
 *
 * This function is invoked upon return from a call into the wrapped library.
 * We've forced the LR to be here, and stashed the original LR in a TLS slot.
 * We need to save the return value(s) found in r0-r3, then invoke the
 * wrapped_return function which will log timing information. We can then
 * restore the return values, fetch the original LR from TLS and bump the
 * PC back where it originally came from before calling into this wrapping
 * library.
 */
#ifdef WRAP_RETURN_FUNC
ENTRY(concat(arch_,WRAP_RETURN_FUNC))
	/* push return values: r0-r3 */
	push	{r0-r3}
	symaddr	ip, _FN(WRAP_RETURN_FUNC)
	/*
	 * overhead before gettimeofday: 4 instructions + wrapped_return
	 * preamble (~3 instructions)
	 */
	blx	ip
	get_wrapping_tls_val ip, r3
	/*
	 * reset the TLS slot back to zero
	 * (otherwise we won't ever log again!)
	 */
	mov	r1, #0
	set_wrapping_tls_val r1, r2, r3
	pop	{r0-r3}
	mov	pc, ip
END(concat(arch_,WRAP_RETURN_FUNC))
#endif

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
	/* save caller args:
	 *   put pointer to r0 (on stack) in r4
	 *   put number of registers saved in r6
	 *   put pointer to incoming stack in r8
	 */
	save_caller_state r4, r8

	/* lookup wrapped func address */
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	ldr	r5, [r5]
	cmp	r5, #0
	bne	5f
	mov	r5, lr	/* save the original lr in r5 */
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	bl	_FN(wrapped_dlsym)
	cmp	r0, #0
	beq	6f	/* will branch to original lr */
	symaddr	r5, marg(__wrapsym_,\wrapsym,$1)
	str	r0, [r5]
	mov	r5, r0

5:	/* call any defined "tracing" function */
#ifdef WRAP_TRACE_FUNC
	/* prototype:
	   void wrapped_tracer(const char *symbol, void *symptr,
			void *regs, void *stack);
	 */
	symaddr r0, marg(__wrapstr_,\wrapsym,$1)
	mov	r1, r5 /* pointer to function symbol */
	mov	r2, r4 /* pointer to register set */
	mov	r3, r8 /* stack pointer */
	bl	_FN(WRAP_TRACE_FUNC)
#ifdef WRAP_RETURN_FUNC
	cmp	r0, #0
	beq	7f
	bgt	6f  /* >0 == handled function, return through wrapped_return */
	/*
	 * If we get here, then the tracing function has returned a negative
	 * value which indicates that we're to call the original function,
	 * but return through the wrapped return path
	 * (usually to measure time).
	 */
	/* save the original LR into the wrapping TLS key slot */
	sub	r8, #4		/* original LR (see save_caller_state) */
	ldr	ip, [r8]
	set_wrapping_tls_val ip, r0, r1
	/* replace original LR with arch_wrapped_return */
	symaddr ip, _FN(concat(arch_,WRAP_RETURN_FUNC))
	str	ip, [r8]  /* replace LR: return through arch_wrapped_return! */
	/*
	 * overhead between gettimeofday and actual function invocation:
	 * 20 instructions (including restore_caller_state)
	 */
	b	7f /* call the function (return through arch_wrapped_return) */

6:	symaddr	r5, _FN(WRAP_RETURN_FUNC)
#endif /* WRAP_RETURN_FUNC */
#endif /* WRAP_TRACE_FUNC */
	/* restore registers and make the original function call
	 * (or jump to special return routine) */
7:	mov	ip, r5
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
	save_caller_state r4, r8
	symaddr	r0, marg(__wraplib_path_,\wraplib,$0)
	symaddr	r1, marg(__libhandle_,\wraplib,$0)
	symaddr	r2, marg(__wrapstr_,\wrapsym,$1)
	mov	r5, lr
	bl	_FN(wrapped_dlsym)
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
