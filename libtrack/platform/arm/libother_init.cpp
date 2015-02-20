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
#include <sys/cdefs.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "wrap_lib.h"

void *real_libc_dso = NULL;
extern const char *progname;

/* -------------------------------------------------------------------
 *
 * From bionic/libc_init_dynamic.cpp
 *
 */

__attribute__((constructor)) static void __libc_preinit()
{

	init_libc_iface(&libc, LIBC_PATH);
}
