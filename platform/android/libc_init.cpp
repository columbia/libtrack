/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "libc_init_common.h"
#include "bionic_tls.h"

#include <asm/page.h>
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/auxv.h>
#include <unistd.h>

#include "atexit.h"
#include "bionic_auxv.h"
#include "bionic_ssp.h"
#include "KernelArgumentBlock.h"
#include "pthread_internal.h"

#define LIBC_PATH "/system/lib/libc_real.so"

extern "C" void wrapped_tracer(const char *symbol);

// ------------------------------------------------------------------
//
// From bionic/libc_init_common.cpp
//
// ------------------------------------------------------------------

static void *real_libc_dso;

// Not public, but well-known in the BSDs.
const char* __progname;

char** environ;
uintptr_t __stack_chk_guard = 0;
Elf32_auxv_t *__libc_auxv = NULL;

// Declared in <asm/page.h>.
unsigned int __page_size = PAGE_SIZE;
unsigned int __page_shift = PAGE_SHIFT;

static void __libc_init_bridge(/*KernelArgumentBlock& args */)
{
	void *sym;

	/*
	 * do __progname manually as it's probably the first
	 * time we're touching the real libc, and its value
	 * will be used to create the logfile!
	 */
	sym = dlsym(real_libc_dso, "__progname");
	__progname = *(const char **)sym;

#define init_sym(name) \
	sym = dlsym(real_libc_dso, #name); \
	memcpy((void *)(&(name)), sym, sizeof(name));
	
	// initialize our own copies of real_libc's globals
	// by grabbing the real symbols out of the already-loaded lib
	//init_sym(__progname);
	init_sym(environ);
	init_sym(__stack_chk_guard);
}

// ------------------------------------------------------------------
//
// From bionic/libc_init_dynamic.cpp
//
// ------------------------------------------------------------------

// We flag the __libc_preinit function as a constructor to ensure
// that its address is listed in libc.so's .init_array section.
// This ensures that the function is called by the dynamic linker
// as soon as the shared library is loaded.
__attribute__((constructor)) static void __libc_preinit()
{
	/*
	 * dont' clear the kernel args slot: we need the real libc's initializer to
	 * see it and clear it. We force the dynamic loader to initialize the real
	 * libc (and all its constructors) by opening it now.
	 */
	real_libc_dso = dlopen(LIBC_PATH, RTLD_NOW | RTLD_LOCAL);
	if (!real_libc_dso)
		*((volatile int *)0x111) = 0x111;

	/* initialize some of our own copies of libc global variables */
	__libc_init_bridge();
}

typedef void (*init_func)(void *,
			  void (*)(void),
			  int (*)(int, char **, char **),
			  structors_array_t const * const);

struct glue {
	struct	glue *next;
	int	niobs;
	FILE	*iobs;
};
extern struct glue __sglue;
extern FILE __sF[3];

__noreturn void __libc_init(void* raw_args,
			    void (*onexit)(void),
			    int (*slingshot)(int, char**, char**),
			    structors_array_t const * const structors)
{
	init_func lci = (init_func)dlsym(real_libc_dso, "__libc_init");
	if (!lci)
		*((volatile int *)0x77) = 0x77; /* SEGFAULT */

	/* can we move these into __libc_init_bridge? */
	FILE *lc_sF = (FILE *)dlsym(real_libc_dso, "__sF");
	memcpy((void *)__sF, lc_sF, sizeof(__sF));

	struct glue *lc_sg = (struct glue *)dlsym(real_libc_dso, "__sglue");
	memcpy((void *)&__sglue, lc_sg, sizeof(__sglue));

	/* pass the call along to the real libc */
	lci(raw_args, onexit, slingshot, structors);
}
