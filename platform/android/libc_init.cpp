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

#define LIBC_PATH "/system/lib/_ibc_so"

extern "C" void wrapped_tracer(const char *symbol);

void *real_libc_dso;

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
 * From bionic/libc_init_common.cpp
 *
 */
#if 0
/* TODO: connect this... */
extern int __isthreaded __attribute__((weak_import));

// Not public, but well-known in the BSDs.
extern const char *__progname __attribute__((weak_import));

extern char **environ __attribute__((weak_import));
extern uintptr_t __stack_chk_guard __attribute__((weak_import));
extern Elf32_auxv_t *__libc_auxv __attribute__((weak_import));

// Declared in <asm/page.h>.
extern unsigned int __page_size __attribute__((weak_import));
extern unsigned int __page_shift __attribute__((weak_import));

struct glue {
	struct	glue *next;
	int	niobs;
	FILE	*iobs;
};
extern struct glue __sglue __attribute__((weak_import));
extern FILE __sF[3] __attribute__((weak_import));

prop_area *__system_property_area__ __attribute__((weak_import));

static void __libc_init_bridge(void)
{
	void *sym;

	/*
	 * do __progname without memcpy: it's the first
	 * time we're touching the real libc, and the __progname
	 * value will be used to create the logfile on the first
	 * wrapped invocation (see wrap_lib.c)
	 */
	sym = dlsym(real_libc_dso, "__progname");
	__progname = *(const char **)sym;

#define init_sym(name) \
	sym = dlsym(real_libc_dso, #name); \
	memcpy((void *)(&(name)), sym, sizeof(name));
	
	// initialize our own copies of real_libc's globals
	// by grabbing the real symbols out of the already-loaded lib
	init_sym(environ);
	init_sym(__stack_chk_guard);
	init_sym(__sF);
	init_sym(__sglue);
	init_sym(__system_property_area__);
}
#endif

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
		*((volatile int *)0x111) = 0x111; /* SEGFAULT */

	/*
	sym = dlsym(real_libc_dso, "__progname");
	__progname = *(const char **)sym;
	*/

	/* initialize some of our own copies of libc global variables */
	//__libc_init_bridge();
}

extern "C"
__noreturn void __libc_init(void* raw_args,
			    void (*onexit)(void),
			    int (*slingshot)(int, char**, char**),
			    structors_array_t const * const structors)
{
	init_func real_init = (init_func)dlsym(real_libc_dso, "__libc_init");
	if (!real_init)
		*((volatile int *)0x777) = 0x777; /* SEGFAULT */

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

