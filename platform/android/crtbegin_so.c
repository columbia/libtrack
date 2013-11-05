/*
 * Copyright (C) 2012 The Android Open Source Project
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
#include "bionic_tls.h"
#include "wrap_lib.h"

extern void *__dso_handle;

__attribute__((visibility("hidden"),destructor))
void __on_dlclose() {
	if (libc.dso && libc.__cxa_finalize)
		libc.__cxa_finalize(&__dso_handle);
}

#ifndef CRT_LEGACY_WORKAROUND
__attribute__ ((visibility ("hidden")))
#endif
__attribute__ ((section (".bss")))
void *__dso_handle = (void *) 0;

/* -------------------------------------------------------------------
 *
 * From bionic/__errno.c
 *
 */
volatile int*  __errno( void )
{
	return  &((volatile int*)__get_tls())[TLS_SLOT_ERRNO];
}

#ifndef _LIBC
void *memcpy(void *dst, const void *src, size_t len)
{
	return libc.memcpy(dst, src, len);
}

int raise(int sig)
{
	return libc.raise(sig);
}

void abort(void)
{
	while (1)
		libc.abort();
}
#endif
