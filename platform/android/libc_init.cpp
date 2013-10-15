/*
 * libc_init.cpp
 * Derived from bionic/libc_init_* from the Android Open Source Project
 *
 */

#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <asm/page.h>
#include <sys/auxv.h>
#include <sys/cdefs.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "bionic_tls.h"
#include "wrap_lib.h"

void *real_libc_dso = NULL;
const char *progname = NULL;

/* -------------------------------------------------------------------
 *
 * From bionic/libc_init_common.h
 *
 */
typedef struct {
	void (**preinit_array)(void);
	void (**init_array)(void);
	void (**fini_array)(void);
} structors_array_t;

typedef __noreturn void (*init_func)(void *,
				     void (*)(void),
				     int (*)(int, char **, char **),
				     structors_array_t const * const);

extern "C"
__noreturn void __libc_init(void* raw_args,
                            void (*onexit)(void),
                            int (*slingshot)(int, char**, char**),
                            structors_array_t const * const structors);

/* -------------------------------------------------------------------
 *
 * From bionic/libc_init_dynamic.cpp
 *
 */

// We flag the __libc_preinit function as a constructor to ensure
// that its address is listed in libc.so's .init_array section.
// This ensures that the function is called by the dynamic linker
// as soon as the shared library is loaded.
__attribute__((constructor)) static void __libc_preinit()
{
	void *sym;

	/*
	 * don't clear the kernel args slot: we need the real libc's
	 * initializer to see it and clear it. We force the dynamic loader
	 * to initialize the real libc (and all its constructors) by
	 * opening / loading it now.
	 */
	real_libc_dso = dlopen(LIBC_PATH, RTLD_NOW | RTLD_GLOBAL);
	if (!real_libc_dso)
		_BUG(0x111);
	sym = dlsym(real_libc_dso, "__progname");
	if (sym)
		progname = *(const char **)sym;
	(void)wrapped_tracer("__constructor__(__libc_preinit)", NULL, 0, NULL);
}

extern "C"
__noreturn void __libc_init(void* raw_args,
			    void (*onexit)(void),
			    int (*slingshot)(int, char**, char**),
			    structors_array_t const * const structors)
{
	init_func real_init;

	real_init = (init_func)wrapped_dlsym(LIBC_PATH,
					     &real_libc_dso,
					     "__libc_init");
	if (!real_init)
		_BUG(0x777);

	/* pass the call along to the real libc */
	real_init(raw_args, onexit, slingshot, structors);
}

/* -------------------------------------------------------------------
 *
 * From bionic/__errno.c
 *
 */
volatile int*  __errno( void )
{
	return  &((volatile int*)__get_tls())[TLS_SLOT_ERRNO];
}

