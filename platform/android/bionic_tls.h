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
#ifndef _SYS_TLS_H
#define _SYS_TLS_H

#include <sys/cdefs.h>

__BEGIN_DECLS

/** WARNING WARNING WARNING
 **
 ** This header file is *NOT* part of the public Bionic ABI/API
 ** and should not be used/included by user-serviceable parts of
 ** the system (e.g. applications).
 **
 ** It is only provided here for the benefit of the system dynamic
 ** linker and the OpenGL sub-system (which needs to access the
 ** pre-allocated slot directly for performance reason).
 **/

/* Well-known TLS slots. What data goes in which slot is arbitrary unless otherwise noted. */
enum {
  TLS_SLOT_SELF = 0, /* The kernel requires this specific slot for x86. */
  TLS_SLOT_THREAD_ID,
  TLS_SLOT_ERRNO,

  /* These two aren't used by bionic itself, but allow the graphics code to
   * access TLS directly rather than using the pthread API. */
  TLS_SLOT_OPENGL_API = 3,
  TLS_SLOT_OPENGL = 4,

  /* This slot is only used to pass information from the dynamic linker to
   * libc.so when the C library is loaded in to memory. The C runtime init
   * function will then clear it. Since its use is extremely temporary,
   * we reuse an existing location that isn't needed during libc startup. */
  TLS_SLOT_BIONIC_PREINIT = TLS_SLOT_OPENGL_API,

  TLS_SLOT_STACK_GUARD = 5, /* GCC requires this specific slot for x86. */
  TLS_SLOT_DLERROR,

  TLS_SLOT_FIRST_USER_SLOT /* Must come last! */
};

/*
 * Maximum number of elements in the TLS array.
 * POSIX says this must be at least 128, but Android has traditionally had only 64, minus those
 * ones used internally by bionic itself.
 * There are two kinds of slot used internally by bionic --- there are the well-known slots
 * enumerated above, and then there are those that are allocated during startup by calls to
 * pthread_key_create; grep for GLOBAL_INIT_THREAD_LOCAL_BUFFER to find those. We need to manually
 * maintain that second number, but pthread_test will fail if we forget.
 */
#define GLOBAL_INIT_THREAD_LOCAL_BUFFER_COUNT 4
#define BIONIC_TLS_SLOTS 64

/* syscall only, do not call directly */
extern int __set_tls(void* ptr);

/* get the TLS */
#if defined(__arm__)
# define __get_tls() \
    ({ register unsigned int __val asm("r0"); \
       asm ("mrc p15, 0, r0, c13, c0, 3" : "=r"(__val) ); \
       (volatile void*)__val; })
#elif defined(__mips__)
# define __get_tls() \
    ({ register unsigned int __val asm("v1");   \
        asm (                                   \
            "   .set    push\n"                 \
            "   .set    mips32r2\n"             \
            "   rdhwr   %0,$29\n"               \
            "   .set    pop\n"                  \
            : "=r"(__val)                       \
            );                                  \
        (volatile void*)__val; })
#elif defined(__i386__)
# define __get_tls() \
    ({ register void* __val; \
       asm ("movl %%gs:0, %0" : "=r"(__val)); \
       (volatile void*) __val; })
#else
#error unsupported architecture
#endif

/* return the stack base and size, used by our malloc debugger */
extern void* __get_stack_base(int* p_stack_size);

__END_DECLS

#if defined(__cplusplus)
struct KernelArgumentBlock;
extern __LIBC_HIDDEN__ void __libc_init_tls(KernelArgumentBlock& args);
#endif

#endif /* _SYS_TLS_H */
