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

abort_msg_t **__abort_message_ptr;
Elf32_auxv_t *__libc_auxv = NULL;

// ------------------------------------------------------------------
//
// From bionic/libc_init_common.cpp
//
// ------------------------------------------------------------------

// Not public, but well-known in the BSDs.
const char* __progname;

// Declared in <unistd.h>.
char** environ;

// Declared in <private/bionic_ssp.h>.
uintptr_t __stack_chk_guard = 0;

// Declared in <asm/page.h>.
unsigned int __page_size = PAGE_SIZE;
unsigned int __page_shift = PAGE_SHIFT;

extern "C" unsigned long int getauxval(unsigned long int type) {
  for (Elf32_auxv_t* v = __libc_auxv; v->a_type != AT_NULL; ++v) {
    if (v->a_type == type) {
      return v->a_un.a_val;
    }
  }
  return 0;
}

void __libc_init_common(KernelArgumentBlock& args) {
  // just initialize our own copies of the globa variables
  environ = args.envp;
  errno = 0;
  __libc_auxv = args.auxv;
  __progname = args.argv[0] ? args.argv[0] : "<unknown>";
  __abort_message_ptr = args.abort_message_ptr;

  // AT_RANDOM is a pointer to 16 bytes of randomness on the stack.
  __stack_chk_guard = *reinterpret_cast<uintptr_t*>(getauxval(AT_RANDOM));
}

extern "C" {
  //extern void pthread_debug_init(void);
  extern void malloc_debug_init(void);
  extern void malloc_debug_fini(void);
};

// ------------------------------------------------------------------
//
// From bionic/libc_init_dynamic.cpp
//
// ------------------------------------------------------------------

// This function is called from the executable's _start entry point
// (see arch-$ARCH/bionic/crtbegin_dynamic.S), which is itself
// called by the dynamic linker after it has loaded all shared
// libraries the executable depends on.
//
// Note that the dynamic linker has also run all constructors in the
// executable at this point.
__noreturn void __libc_init(void* raw_args,
			    void (*onexit)(void),
			    int (*slingshot)(int, char**, char**),
			    structors_array_t const * const structors)
{
	void (*exit_f)(int status) = NULL;
	void *libc_dso = dlopen(LIBC_PATH, RTLD_NOW | RTLD_LOCAL);
	if (!libc_dso) {
		*((volatile int *)0) = 1;
	}
	exit_f = (void (*)(int))dlsym(libc_dso, "exit");
	if (!exit_f) {
		*((volatile int *)0) = 1;
	}

	KernelArgumentBlock args(raw_args);

	// Several Linux ABIs don't pass the onexit pointer, and the ones that
	// do never use it.  Therefore, we ignore it.

	// The executable may have its own destructors listed in its .fini_array
	// so we need to ensure that these are called when the program exits
	// normally.
	if (structors->fini_array) {
		__cxa_atexit(__libc_fini,structors->fini_array,NULL);
	}

	exit_f(slingshot(args.argc, args.argv, args.envp));
}

// We flag the __libc_preinit function as a constructor to ensure
// that its address is listed in libc.so's .init_array section.
// This ensures that the function is called by the dynamic linker
// as soon as the shared library is loaded.
__attribute__((constructor)) static void __libc_preinit() {
  /*
   * load up the actual libc to call its constructor
   */
  // Read the kernel argument block pointer from TLS.
  void* tls = const_cast<void*>(__get_tls());
  KernelArgumentBlock** args_slot = &reinterpret_cast<KernelArgumentBlock**>(tls)[TLS_SLOT_BIONIC_PREINIT];
  KernelArgumentBlock* args = *args_slot;

  // Clear the slot so no other initializer sees its value.
  // __libc_init_common() will change the TLS area so the old one won't be accessible anyway.
  //*args_slot = NULL;

  void *libc_dso = dlopen(LIBC_PATH, RTLD_NOW | RTLD_LOCAL);
  if (!libc_dso)
    return;
  wrapped_tracer("__libc_preinit:start");

  __libc_init_common(*args);
  wrapped_tracer("__libc_preinit:end");

  // Hooks for the debug malloc and pthread libraries to let them know that we're starting up.
  // pthread_debug_init();
  //malloc_debug_init();
}

__LIBC_HIDDEN__ void __libc_postfini() {
  // A hook for the debug malloc library to let it know that we're shutting down.
  malloc_debug_fini();
}

