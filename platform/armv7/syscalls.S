/*
 * Make a platform-specific mach-traps/syscalls without using
 * the standard interfaces.
 *
 * Mach trap numbers: osfmk/kern/syscall_sw.c
 * Mach trap interfaces: osfmk/mach/mach_traps.h
 * BSD syscall numbers: bsd/kern/syscalls.master
 *
 * Syscall interface:
 *     xcrun -sdk iphoneos otool -tvV $(xcrun -sdk iphoneos -show-sdk-path)/usr/lib/system/libsystem_kernel.dylib | vim -
 */

/* __raw_thread_self() */

/* __raw_task_self() */

/* __raw_mach_port_deallocate */
