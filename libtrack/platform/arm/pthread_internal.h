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
#ifndef _PTHREAD_INTERNAL_H_
#define _PTHREAD_INTERNAL_H_

#include <pthread.h>
#include <stdbool.h>

__BEGIN_DECLS

typedef struct pthread_internal_t
{
    struct pthread_internal_t*  next;
    struct pthread_internal_t*  prev;
    pthread_attr_t              attr;
    pid_t                       tid;
    bool                        allocated_on_heap;
    pthread_cond_t              join_cond;
    int                         join_count;
    void*                       return_value;
    int                         internal_flags;
    __pthread_cleanup_t*        cleanup_stack;
    void**                      tls;         /* thread-local storage area */

    /*
     * The dynamic linker implements dlerror(3), which makes it hard for us to implement this
     * per-thread buffer by simply using malloc(3) and free(3).
     */
#define __BIONIC_DLERROR_BUFFER_SIZE 512
    char dlerror_buffer[__BIONIC_DLERROR_BUFFER_SIZE];
} pthread_internal_t;

int _init_thread(pthread_internal_t* thread, bool add_to_thread_list);
void __init_tls(pthread_internal_t* thread);
void _pthread_internal_add(pthread_internal_t* thread);
pthread_internal_t* __get_thread(void);

__LIBC_HIDDEN__ void pthread_key_clean_all(void);
__LIBC_HIDDEN__ void _pthread_internal_remove_locked(pthread_internal_t* thread);

#define PTHREAD_ATTR_FLAG_DETACHED      0x00000001
#define PTHREAD_ATTR_FLAG_USER_STACK    0x00000002

__LIBC_HIDDEN__ extern pthread_internal_t* gThreadList;
__LIBC_HIDDEN__ extern pthread_mutex_t gThreadListLock;

/* needed by posix-timers.c */

static __inline__ void timespec_add( struct timespec*  a, const struct timespec*  b )
{
    a->tv_sec  += b->tv_sec;
    a->tv_nsec += b->tv_nsec;
    if (a->tv_nsec >= 1000000000) {
        a->tv_nsec -= 1000000000;
        a->tv_sec  += 1;
    }
}

static  __inline__ void timespec_sub( struct timespec*  a, const struct timespec*  b )
{
    a->tv_sec  -= b->tv_sec;
    a->tv_nsec -= b->tv_nsec;
    if (a->tv_nsec < 0) {
        a->tv_nsec += 1000000000;
        a->tv_sec  -= 1;
    }
}

static  __inline__ void timespec_zero( struct timespec*  a )
{
    a->tv_sec = a->tv_nsec = 0;
}

static  __inline__ int timespec_is_zero( const struct timespec*  a )
{
    return (a->tv_sec == 0 && a->tv_nsec == 0);
}

static  __inline__ int timespec_cmp( const struct timespec*  a, const struct timespec*  b )
{
    if (a->tv_sec  < b->tv_sec)  return -1;
    if (a->tv_sec  > b->tv_sec)  return +1;
    if (a->tv_nsec < b->tv_nsec) return -1;
    if (a->tv_nsec > b->tv_nsec) return +1;
    return 0;
}

static  __inline__ int timespec_cmp0( const struct timespec*  a )
{
    if (a->tv_sec < 0) return -1;
    if (a->tv_sec > 0) return +1;
    if (a->tv_nsec < 0) return -1;
    if (a->tv_nsec > 0) return +1;
    return 0;
}

extern int  __pthread_cond_timedwait(pthread_cond_t*,
                                     pthread_mutex_t*,
                                     const struct timespec*,
                                     clockid_t);

extern int  __pthread_cond_timedwait_relative(pthread_cond_t*,
                                              pthread_mutex_t*,
                                              const struct timespec*);

/* needed by fork.c */
extern void __timer_table_start_stop(int  stop);
extern void __bionic_atfork_run_prepare();
extern void __bionic_atfork_run_child();
extern void __bionic_atfork_run_parent();

__END_DECLS

#endif /* _PTHREAD_INTERNAL_H_ */
