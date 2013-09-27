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

abort_msg_t **__abort_message_ptr;
Elf32_auxv_t *__libc_auxv = NULL;

// ------------------------------------------------------------------
//
// From bionic/libc_init_common.cpp
//
// ------------------------------------------------------------------


extern "C" unsigned __get_sp(void);
extern "C" int __system_properties_init(void);

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

  /*
  // Get the main thread from TLS and add it to the thread list.
  pthread_internal_t* main_thread = __get_thread();
  main_thread->allocated_on_heap = false;
  _pthread_internal_add(main_thread);
  __system_properties_init(); // Requires 'environ'.
  */
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

// We flag the __libc_preinit function as a constructor to ensure
// that its address is listed in libc.so's .init_array section.
// This ensures that the function is called by the dynamic linker
// as soon as the shared library is loaded.
__attribute__((constructor)) static void __libc_preinit() {
  /*
   * load up the actual libc to call its constructor
   */
  void *libc_dso = dlopen(LIBC_PATH, RTLD_NOW | RTLD_LOCAL);
  if (!libc_dso)
    return;

  // Read the kernel argument block pointer from TLS.
  void* tls = const_cast<void*>(__get_tls());
  KernelArgumentBlock** args_slot = &reinterpret_cast<KernelArgumentBlock**>(tls)[TLS_SLOT_BIONIC_PREINIT];
  KernelArgumentBlock* args = *args_slot;

  // Clear the slot so no other initializer sees its value.
  // __libc_init_common() will change the TLS area so the old one won't be accessible anyway.
  *args_slot = NULL;

  __libc_init_common(*args);

  // Hooks for the debug malloc and pthread libraries to let them know that we're starting up.
  // pthread_debug_init();
  //malloc_debug_init();
}

__LIBC_HIDDEN__ void __libc_postfini() {
  // A hook for the debug malloc library to let it know that we're shutting down.
  malloc_debug_fini();
}

