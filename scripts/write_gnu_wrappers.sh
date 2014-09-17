#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 prototypes_file"
    exit -1
fi


function echo_header()
{
    echo "#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execinfo.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>
#include <nl_types.h>
#include <crypt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <complex.h>
#include <search.h>
#include <iconv.h>
#include <inttypes.h>
#include <aio.h>
#include <termios.h>
#include <fenv.h>
#include <glob.h>
#include <math.h>
#include <wctype.h>
#include <wchar.h>
#include <mqueue.h>
#include <poll.h>
#include <regex.h>
#include <semaphore.h>
#include <setjmp.h>
#include <wordexp.h>
#include <assert.h>
#include <stdarg.h>
#include <zlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_FRAMES 128
#define NAME_LEN 4096
#define LINE_LEN 4096

extern char *__progname;
volatile int*  __errno(void);

__thread unsigned int entered = 0;
"
}


function echo_fd_type_function()
{
echo "char fd_type(int fd)
{
        struct stat buf;
        static int (*libc_getsockname)(int, struct sockaddr *, socklen_t *);

        if (fstat(fd, &buf) < 0)
                return '?';
        if (S_ISREG(buf.st_mode))
                return 'F';
        if (S_ISDIR(buf.st_mode))
                return 'f';
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
                return 'D';
        if (S_ISFIFO(buf.st_mode))
                return 'P';
        if (S_ISLNK(buf.st_mode))
                return 'l';
        if (S_ISSOCK(buf.st_mode)) {
                struct sockaddr sam;
                int len = sizeof(sam);
                if (!libc_getsockname)
                        libc_getsockname = dlsym(RTLD_NEXT, \"getsockname\");
                if (!libc_getsockname)
                        return '?';
                if (libc_getsockname(fd, (struct sockaddr *)&sam, &len) < 0)
                        return '?';
                if (sam.sa_family == AF_UNIX || sam.sa_family == AF_LOCAL)
                        return 'U';
                return 'S';
        }
        return '?';
}"
echo ""
}


function echo_backtrace_function()
{
    echo "
/*
 * Backtrace glibc functions and log them in a
 * file coresponding to current thread's name.
 */
static void
_backtrace ()
{
        void  *frames[MAX_FRAMES];
        char **bt;
        size_t i, j, nframes;
        FILE *fp;
        char name[NAME_LEN];
        char *lib;
        char *sym;
        char line[LINE_LEN];
        static FILE * (*libc_fopen)(const char *, const char *);
        static int (*libc_fclose)(FILE *);
        static pid_t (*libc_getpid)(void);
        static void  (*libc_free)(void *);
        static int (*libc_backtrace)(void **, int);
        static char ** (*libc_backtrace_symbols)(void *const *, int);
        static int (*libc_sprintf)(char *, const char *, ...);
        static int (*libc_fprintf)(char *, const char *, ...);
        static char * (*libc_strncpy)(char *, const char *, size_t );

        if (!libc_fopen)
            *(void **) (&libc_fopen) = dlsym(RTLD_NEXT, \"fopen\");
        if (!libc_fclose)
            *(void **) (&libc_fclose) = dlsym(RTLD_NEXT, \"fclose\");
        if (!libc_getpid)
            *(void **) (&libc_getpid) = dlsym(RTLD_NEXT, \"getpid\");
        if (!libc_free)
            *(void **) (&libc_free) = dlsym(RTLD_NEXT, \"free\");
        if (!libc_backtrace)
            *(void **) (&libc_backtrace) = dlsym(RTLD_NEXT, \"backtrace\");
        if (!libc_backtrace_symbols)
            *(void **) (&libc_backtrace_symbols) = dlsym(RTLD_NEXT, \"backtrace_symbols\");
        if (!libc_sprintf)
            *(void **) (&libc_sprintf) = dlsym(RTLD_NEXT, \"sprintf\");
        if (!libc_fprintf)
            *(void **) (&libc_fprintf) = dlsym(RTLD_NEXT, \"fprintf\");
        if (!libc_strncpy)
             *(void **) (&libc_strncpy) = dlsym(RTLD_NEXT, \"strncpy\");

        nframes = libc_backtrace(frames, MAX_FRAMES);
        bt = libc_backtrace_symbols(frames, nframes);
        libc_sprintf(name, \"%s.%ld.%ld.log\", \"__progname\",
                     libc_getpid(),syscall(SYS_gettid));
        fp = (libc_fopen)(name, \"a\");
        if (fp == NULL) {
            libc_fprintf(stderr, \"_backtrace: Error while opening: <%s>\n\", name);
            return;
        }
        libc_fprintf(fp, \" T:BT:START:%d:\n\", nframes - 1);
        for (i = 1; i < nframes; i++) {
            libc_strncpy(line, bt[i],LINE_LEN);
            for (j = 0;  j < LINE_LEN; j++)
                if ( line[j] == '(' || line[j] == ' ') {
                    line[j] = '\0';
                    break;
                }
            lib = line;
            if (i > 1) {
                /* Format:  TIMESTAMP::STACKFRAMENO:SYMVAL:SYMNAME:SYMOFFSET:DLINAME:DLIBASE */
                libc_fprintf(fp, \" T::%d:SVAL:??:OFFSET:%s:(DLIBASE):\n\", i, lib);
                continue;
            }
            sym = line + j + 1;
            if (*sym == '+') {
                libc_fprintf(fp, \" T::%d:SVAL:??:OFFSET:%s:(DLIBASE)\n\",
                             i, \"libc.so\");
            } else {
                for (; j < LINE_LEN ; j++) {
                    if (line[j] == '+') {
                        line[j] = '\0';
                        break;
                    }
                }
                libc_fprintf(fp, \" T::%d:SVAL:%s:OFFSET:%s:(DLIBASE)\n\",
                                 i, sym, \"libc.so\");
            }
        }
        //libc_free(bt);
        libc_fclose(fp);
}"
echo ""
}


function echo_backtrace_given_name_function()
{
    echo "
/*
 * Backtrace glibc functions and log them in a
 * file coresponding to current thread's name.
 */
static void
_backtrace_given_name (char *given_name)
{
        void  *frames[MAX_FRAMES];
        char **bt;
        size_t i, j, nframes;
        FILE *fp;
        char name[NAME_LEN];
        char *lib;
        char *sym;
        char line[LINE_LEN];
        static FILE * (*libc_fopen)(const char *, const char *);
        static int (*libc_fclose)(FILE *);
        static pid_t (*libc_getpid)(void);
        static void  (*libc_free)(void *);
        static int (*libc_backtrace)(void **, int);
        static char ** (*libc_backtrace_symbols)(void *const *, int);
        static int (*libc_sprintf)(char *, const char *, ...);
        static int (*libc_fprintf)(char *, const char *, ...);
        static char * (*libc_strncpy)(char *, const char *, size_t );

        if (!libc_fopen)
            *(void **) (&libc_fopen) = dlsym(RTLD_NEXT, \"fopen\");
        if (!libc_fclose)
            *(void **) (&libc_fclose) = dlsym(RTLD_NEXT, \"fclose\");
        if (!libc_getpid)
            *(void **) (&libc_getpid) = dlsym(RTLD_NEXT, \"getpid\");
        if (!libc_free)
            *(void **) (&libc_free) = dlsym(RTLD_NEXT, \"free\");
        if (!libc_backtrace)
            *(void **) (&libc_backtrace) = dlsym(RTLD_NEXT, \"backtrace\");
        if (!libc_backtrace_symbols)
            *(void **) (&libc_backtrace_symbols) = dlsym(RTLD_NEXT, \"backtrace_symbols\");
        if (!libc_sprintf)
            *(void **) (&libc_sprintf) = dlsym(RTLD_NEXT, \"sprintf\");
        if (!libc_fprintf)
            *(void **) (&libc_fprintf) = dlsym(RTLD_NEXT, \"fprintf\");
        if (!libc_strncpy)
             *(void **) (&libc_strncpy) = dlsym(RTLD_NEXT, \"strncpy\");

        nframes = libc_backtrace(frames, MAX_FRAMES);
        bt = libc_backtrace_symbols(frames, nframes);
        libc_sprintf(name, \"%s.%ld.%ld.log\", \"__progname\",
                     libc_getpid(),syscall(SYS_gettid));
        fp = (libc_fopen)(name, \"a\");
        if (fp == NULL) {
            libc_fprintf(stderr, \"_backtrace: Error while opening: <%s>\n\", name);
            return;
        }
        libc_fprintf(fp, \" T:BT:START:%d:\n\", nframes - 1);
        for (i = 1; i < nframes; i++) {
            libc_strncpy(line, bt[i],LINE_LEN);
            for (j = 0;  j < LINE_LEN; j++)
                if ( line[j] == '(' || line[j] == ' ') {
                    line[j] = '\0';
                    break;
                }
            lib = line;
            if (i > 1) {
                /* Format:  TIMESTAMP::STACKFRAMENO:SYMVAL:SYMNAME:SYMOFFSET:DLINAME:DLIBASE */
                libc_fprintf(fp, \" T::%d:SVAL:??:OFFSET:%s:(DLIBASE):\n\", i, lib);
                continue;
            }
            libc_fprintf(fp, \" T::%d:SVAL:%s:OFFSET:%s:(DLIBASE)\n\",
                                 i, given_name, \"libc.so\");
        }
        //libc_free(bt);
        libc_fclose(fp);
}"
echo ""
}


function echo_timespec_sub_function()
{
    echo "
/*
 * Calculate time elapsed from timestamp a to timestamp b
 * and store it to b.
 */
void
_timespec_sub (struct timespec *a, const struct timespec *b)
{
        a->tv_sec  -= b->tv_sec;
        a->tv_nsec -= b->tv_nsec;
        if (a->tv_nsec < 0) {
            a->tv_nsec += 1000000000;
            a->tv_sec  -= 1;
        }
}"
    echo ""
}


function echo_logtime_function()
{
    echo "
/*
 * Log system time spent executing \"funcname\".
 */
void
_logtime (char *funcname, struct timespec end)
{
        FILE *fp;
        char name[NAME_LEN];
        static FILE * (*libc_fopen)(const char *, const char *);
        static int (*libc_fclose)(FILE *);
        static pid_t (*libc_getpid)(void);
        static int (*libc_sprintf)(char *, const char *, ...);
        static int (*libc_fprintf)(char *, const char *, ...);

        if (!libc_fopen)
            *(void **) (&libc_fopen) = dlsym(RTLD_NEXT, \"fopen\");
        if (!libc_fclose)
            *(void **) (&libc_fclose) = dlsym(RTLD_NEXT, \"fclose\");
        if (!libc_getpid)
            *(void **) (&libc_getpid) = dlsym(RTLD_NEXT, \"getpid\");
        if (!libc_sprintf)
            *(void **) (&libc_sprintf) = dlsym(RTLD_NEXT, \"sprintf\");
        if (!libc_fprintf)
            *(void **) (&libc_fprintf) = dlsym(RTLD_NEXT, \"fprintf\");
        libc_sprintf(name, \"%s.%ld.%ld.log\", \"__progname\", libc_getpid(),
                syscall(SYS_gettid));
        fp = libc_fopen(name, \"a\");
        if (fp == NULL) {
            libc_fprintf(stderr, \"_logtime: Error while opening: <%s>\n\", name);
            return;
        }
        libc_fprintf(fp, \" T.T:LOG:T:%s::%lu.%lu\n\", funcname,
                     (unsigned long) end.tv_sec, (unsigned long) end.tv_nsec);
        libc_fclose(fp);
}"
    echo ""
}


function echo_special_wrappers()
{
    echo "

ssize_t
read (int fd, void *buf, size_t count)
{
        struct timespec start, end;
        static ssize_t  (*fn)(int , void *, size_t );
        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
                *(void **)(&fn) = dlsym(RTLD_NEXT, \"read\");
        if (fn == NULL){
                fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"read\");
                goto out;
        }
        ssize_t  rval;
        if (entered == 1) {
                char name[] = \"read_?\";
                name[5] = fd_type(fd);
                _backtrace_given_name(name);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(fd, buf, count);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
                _logtime(name, end);
        } else {
                rval = fn(fd, buf, count);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}



ssize_t
write (int fd, const void *buf, size_t count)
{
        struct timespec start, end;
        static ssize_t  (*fn)(int , const void *, size_t );
        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
               *(void **)(&fn) = dlsym(RTLD_NEXT, \"write\");
        if (fn == NULL){
                fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"write\");
                goto out;
        }
        ssize_t  rval;
        if (entered == 1) {
                char name[] = \"write_?\";
                name[6] = fd_type(fd);
                _backtrace_given_name(name);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(fd, buf, count);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
               _logtime(name, end);
       } else {
               rval = fn(fd, buf, count);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

pid_t
fork (void)
{
        static pid_t  (*fn)(void);
        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
               *(void **)(&fn) = dlsym(RTLD_NEXT, \"fork\");
        if (fn == NULL){
                fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"fork\");
                goto out;
        }
        if (entered == 1)
                _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return  fn();
}




int
pthread_create (pthread_t *thread, const pthread_attr_t *attr,
                void *(*start_routine) (void *), void *arg)
{
        int rval;
        struct timespec start, end;
        static  int (*fn)(pthread_t *, const pthread_attr_t *,
                  void *(*start_routine) (void *), void *arg());

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void **)(&fn) = dlsym(RTLD_NEXT, \"pthread_create\");
        if (fn == NULL) {
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"pthread_create\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(thread, attr, start_routine, arg);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"pthread_create\", end);
        } else {
            rval = fn(thread, attr, start_routine, arg);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

int
glob (const char *pattern, int flags,
      int (*errfunc) (const char *epath, int eerrno), glob_t *pglob)
{
        int rval;
        struct timespec start, end;
        static int (*fn)(const char *, int flags,
                  int (*errfunc) (const char *, int), glob_t *);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"glob\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"glob\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval =  fn(pattern, flags, errfunc, pglob);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"glob\", end);
        } else {
            rval =  fn(pattern, flags, errfunc, pglob);
        }

out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
tdelete (const void *key, void **rootp,
         int (*compar)(const void *, const void *))
{
        void  *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void **,
                     int (*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"tdelete\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"tdelete\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval =  fn(key, rootp, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"tdelete\", end);
        } else {
            rval =  fn(key, rootp, compar);
        }

out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void
qsort_r (void *base, size_t nmemb, size_t size,
         int (*compar)(const void *, const void *, void *), void *arg)
{
        struct timespec start, end;
        static void (*fn)(void *base, size_t, size_t,
                   int (*compar)(const void *, const void *, void *), void *arg);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"qsort_r\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"qsort_r\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            fn(base, nmemb, size, compar, arg);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
        } else {
            fn(base, nmemb, size, compar, arg);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        _logtime(\"qsort_r\", end);
}

void
qsort (void *base, size_t nmemb, size_t size,
       int (*compar)(const void *, const void *))
{
        struct timespec start, end;
        static void (*fn)(void *, size_t, size_t,
                   int (*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"qsort\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"qsort\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            fn(base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
        } else {
            fn(base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        _logtime(\"qsort\", end);
}

void
pthread_cleanup_push (void (*routine)(void *), void *arg)
{
        struct timespec start, end;
        static  void (*fn)(void (*routine)(void *), void *arg);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"pthread_cleanup_push\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"pthread_clean_up_push\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            fn(routine, arg);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
        } else {
            fn(routine, arg);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        _logtime(\"pthread_cleanup_push\", end);
}

void *
lsearch (const void *key, void *base, size_t *nmemb, size_t size,
         int(*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                    int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"lsearch\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"lsearch\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"lsearch\", end);
        } else {
            rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
lfind (const void *key, const void *base, size_t *nmemb, size_t size,
       int(*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                     int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"lfind\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"lfind\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"lfind\", end);
        } else {
             rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                     int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, \"bsearch\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"bsearch\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"bsearch\", end);
        } else {
            rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

int
setjmp (jmp_buf env)
{
       struct timespec start, end;
       static int  (*fn)(jmp_buf );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, \"setjmp\");
       if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"setjmp\");
            goto out;
       }
       int  rval;
       if (entered == 1)
               _backtrace();
       rval = fn(env);
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}


void
longjmp (jmp_buf env, int val)
{
       struct timespec start, end;
       static void  (*fn)(jmp_buf , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, \"longjmp\");
       if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"longjmp\");
            goto out;
       }
       if (entered == 1)
               _backtrace();
       fn(env, val);
out:
       __sync_fetch_and_sub(&entered, 1);
}




static void * (*libc_calloc)(size_t, size_t);
static void * (*temp_calloc)(size_t nmemb, size_t size);
static void (*libc_free)(void *);
static void (*temp_free)(void *);

char tmpbuf[1024];
unsigned long tmppos = 0;
unsigned long tmpallocs = 0;

void* dummy_malloc(size_t size)
{
    if (tmppos + size >= sizeof(tmpbuf))
        exit(1);
    void *retptr = tmpbuf + tmppos;
    tmppos += size;
    ++tmpallocs;
    return retptr;
}

void* dummy_calloc(size_t nmemb, size_t size)
{
    void *ptr = dummy_malloc(nmemb * size);
    unsigned int i = 0;
    for (; i < nmemb * size; ++i)
        *((char*)(ptr + i)) = '\0';
    return ptr;
}

void dummy_free(void *ptr)
{
    return;
}

void *
calloc(size_t nmemb, size_t size)
{
        struct timespec start, end;
        void * rval;

        __sync_fetch_and_add(&entered, 1);
        if (libc_calloc == NULL){
            libc_calloc = dummy_calloc;
            *(void **)(&temp_calloc) = dlsym(RTLD_NEXT, \"calloc\");
            libc_calloc = temp_calloc;
            __sync_fetch_and_sub(&entered, 1);
            return libc_calloc(nmemb, size);
        }
        void * (*fn)(size_t, size_t) = libc_calloc;
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(nmemb, size);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
                _logtime(\"calloc\", end);
        } else {
                rval = fn(nmemb, size);
        }
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}


void
free (void *ptr)
{
        struct timespec start, end;

        __sync_fetch_and_add(&entered, 1);
        if (libc_free == NULL) {
            libc_free = dummy_free;
            *(void **)(&temp_free) = dlsym(RTLD_NEXT, \"free\");
            libc_free = temp_free;
            libc_free(ptr);
            __sync_fetch_and_sub(&entered, 1);
            return;
        }
        void  (*fn)(void *) = libc_free;
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                fn(ptr);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
                _logtime(\"free\", end);
        } else {
            fn(ptr);
        }
        __sync_fetch_and_sub(&entered, 1);
        return;
}

void *
malloc (size_t size)
{
        struct timespec start, end;
        void * rval;

        __sync_fetch_and_add(&entered, 1);
        static void * (*fn)(size_t );
        if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, \"malloc\");
        if (fn == NULL) {
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"malloc\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"malloc\", end);
        } else {
            rval = fn(size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
realloc (void *ptr, size_t size)
{
        void * rval;
        struct timespec start, end;
        static void * (*fn)(void *, size_t);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, \"realloc\");
        if (fn == NULL) {
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"realloc\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(ptr, size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"realloc\", end);
        } else {
            rval = fn(ptr, size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
memalign (size_t alignment, size_t size)
{
        struct timespec start, end;
        static void * (*fn)(size_t, size_t);
        void * rval;

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, \"memalign\");
        if (fn == NULL) {
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\",
                    \"memalign\");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(alignment, size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime(\"memalign\", end);
        } else {
            rval = fn(alignment, size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}


void *
memset (void *s, int c, size_t n)
{
        struct timespec start, end;
        int i;

        __sync_fetch_and_add(&entered, 1);
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                for (i = 0; i < n; i++)
                        *((unsigned char *)s + i) = c;
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
                _logtime(\"memset\", end);
        } else {
               for (i = 0; i < n; i++)
                       *((char *)s + i) = c;
        }
        __sync_fetch_and_sub(&entered, 1);
        return s;
}

//
//
//int
//ioctl (int d, int request, ...)
//{
//    struct timespec start, end;
//    static int (*fn)(int, int, ...);
//    __sync_fetch_and_add(&entered, 1);
//    _backtrace();
//    if (fn == NULL)
//        fn = dlsym(RTLD_NEXT, \"ioctl\");
//    if (fn == NULL){
//        fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"ioctl\");
//        goto out;
//    }
//    va_list ap;
//    va_start(ap, request);
//    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//    int rval;
//    rval = fn(d, request, ap);
//    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//    _timespec_sub(&end, &start);
//    _logtime(\"ioctl\", end);
//    va_end(ap);
//out:
//    __sync_fetch_and_sub(&entered, 1);
//    return rval;
//}
"
}


function echo_wrapper()
{
    local ftype="$1"
    local fname="$2"
    local farg_prototypes="$3"

    IFS=' ' read -a temp <<< "$farg_prototypes,"
    local farg_names=`for word in ${temp[@]}; do
        if [ "${word:${#word} - 1}" = "," ]; then
            echo "$word"
        fi
    done | sed 's,\*,,g' | tr '\n' ' ' | sed  's,[,]\s$,,g' | sed 's,\[[0-9]*\],,g'`
    #echo "$ftype" "$fname" "($farg_prototypes)"  "($farg_names)"
    local farg_signatures=`echo "$farg_prototypes" \
                    | sed 's,[a-z_0-9]\+\,,\,,g' \
                    | sed 's,[a-z_0-9]\+$,,g' \
                    | sed 's,[a-z_0-9]*\[\],,g'`
    echo "$ftype"
    echo "$fname ($farg_prototypes)"
    echo "{"
    echo "       struct timespec start, end;"
    echo "       static $ftype (*fn)($farg_signatures);"
    echo "       __sync_fetch_and_add(&entered, 1);"
    echo "       if (fn == NULL)"
    echo "           *(void **)(&fn) = dlsym(RTLD_NEXT, \"$fname\");"
    echo "       if (fn == NULL){"
    echo "            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"$fname\");"
    echo "            goto out;"
    echo "       }"
    if [ "$farg_names" = "void" -a "$ftype" = "void " ]; then
        echo "       if (entered == 1) {"
        echo "               _backtrace();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "               fn();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "               _timespec_sub(&end, &start);"
        echo "               _logtime(\"$fname\", end);"
        echo "       } else {"
        echo "               fn();"
        echo "       }"
        echo "out:"
        echo "       __sync_fetch_and_sub(&entered, 1);"
    elif [ "$farg_names" = "void"  -a "$ftype" != "void " ]; then
        echo "       $ftype rval;"
        echo "       if (entered == 1) {"
        echo "               _backtrace();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "               rval = fn();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "               _timespec_sub(&end, &start);"
        echo "               _logtime(\"$fname\", end);"
        echo "       } else {"
        echo "               rval = fn();"
        echo "       }"
        echo "out:"
        echo "       __sync_fetch_and_sub(&entered, 1);"
        echo "      return rval;"
    elif [ "$farg_names" != "void"  -a  "$ftype" = "void " ]; then
        echo "       if (entered == 1) {"
        echo "               _backtrace();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "               fn($farg_names);"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "               _timespec_sub(&end, &start);"
        echo "               _logtime(\"$fname\", end);"
        echo "       } else {"
        echo "               fn($farg_names);"
        echo "       }"
        echo "out:"
        echo "       __sync_fetch_and_sub(&entered, 1);"
    else
        echo "       $ftype rval;"
        echo "       if (entered == 1) {"
        echo "               _backtrace();"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "               rval = fn($farg_names);"
        echo "               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "               _timespec_sub(&end, &start);"
        echo "               _logtime(\"$fname\", end);"
        echo "       } else {"
        echo "               rval = fn($farg_names);"
        echo "       }"
        echo "out:"
        echo "       __sync_fetch_and_sub(&entered, 1);"
        echo "       return rval;"
    fi
    echo "}"
    echo ""
}

IFILE="$1"
echo_header
echo_fd_type_function
echo_backtrace_function
echo_backtrace_given_name_function
echo_timespec_sub_function
echo_logtime_function
echo_special_wrappers
count=0
while read line; do
    if [ "${line:0:1}" = "#" ]; then
        continue
    fi
    fargs=`echo "$line" | sed 's,.*(,,g' | sed 's,[);],,g'`
    fname=`echo "$line" | sed 's,(.*,,g' | tr ' ' '\n' | tail -n 1 | sed 's,\*,,g'`
    ftype=`echo "$line" | sed 's,[a-z0-9_]\+(.*,,g'`
    echo_wrapper "$ftype" "$fname" "$fargs"
    count=$(($count+1))
done < "$IFILE"
echo "Intrerpossing $(($count+17)) wrappers..." 1>&2
