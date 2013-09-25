/*
 * wrap_lib.h
 * Copyright (C) 2013 Jeremy C. Andrus
 */
#ifndef WRAP_LIB_H
#define WRAP_LIB_H

#if defined(ANDROID)
#define LIBC_PATH "/system/lib/libc_real.so"
#define LOGFILE_PATH "/data/local/syscalls.log"
#elif defined(__APPLE__)
#define LIBC_PATH "/usr/lib/system/libsystem_kernel_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#else
#define LIBC_PATH "/lib/libc_real.so"
#define LOGFILE_PATH "/tmp/syscalls.log"
#endif

#endif
