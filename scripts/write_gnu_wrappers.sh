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

#define MAX_FRAMES 128
#define NAME_LEN 4096
#define LINE_LEN 4096

extern char *__progname;
volatile int*  __errno(void);

__thread unsigned int entered = 0;
"
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
        libc_sprintf(name, \"%s.%ld.%ld.log\", \"__progname\", libc_getpid(),syscall(SYS_gettid));
        fp = (libc_fopen)(name, \"a\");
        if (fp == NULL) {
            fprintf(stderr, \"_backtrace: Error while opening: <%s>\n\", name);
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
                libc_fprintf(fp, \" T::%d:SVAL:??:OFFSET:%s:(DLIBASE)\n\", i, \"libc.so\");
            } else {
                for (; j < LINE_LEN ; j++) {
                    if (line[j] == '+') {
                        line[j] = '\0';
                        break;
                    }
                    libc_fprintf(fp, \" T::%d:SVAL:%s:OFFSET:%s:(DLIBASE)\n\", i, sym, \"libc.so\");
                }
            }
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
        libc_sprintf(name, \"%s.%ld.%ld.log\", \"__progname\", libc_getpid(),syscall(SYS_gettid));
        fp = libc_fopen(name, \"a\");
        if (fp == NULL) {
            libc_fprintf(stderr, \"_logtime: Error while opening: <%s>\n\", name);
            return;
        }
        libc_fprintf(fp, \" T.T:LOG:T:%s::%lu.%lu\n\", funcname, (unsigned long)end.tv_sec, (unsigned long)end.tv_nsec);
        libc_fclose(fp);
}"
    echo ""
}


function echo_special_wrappers()
{
    echo "
int
pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
        struct timespec start, end;
        int (*fn)(pthread_t *, const pthread_attr_t *, void *(*start_routine) (void *), void *arg());
        _backtrace();
        *(void **)(&fn) = dlsym(RTLD_NEXT, \"pthread_create\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"pthread_create\");
            return;
        }
        int rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval = fn(thread, attr, start_routine, arg);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"pthread_create\", end);
        return rval;
}

int
glob (const char *pattern, int flags, int (*errfunc) (const char *epath, int eerrno), glob_t *pglob)
{
        struct timespec start, end;
        int (*fn)(const char *, int flags, int (*errfunc) (const char *, int), glob_t *);
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"glob\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"glob\");
            return;
        }
        int rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval =  fn(pattern, flags, errfunc, pglob);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"glob\", end);
        return rval;
}

void *
tdelete (const void *key, void **rootp, int (*compar)(const void *, const void *))
{
        struct timespec start, end;
        void * (*fn)(const void *, void **, int (*compar)(const void *, const void *));
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"tdelete\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"tdelete\");
            return;
        }
        void  *rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval =  fn(key, rootp, compar);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"tdelete\", end);
        return rval;
}

void
qsort_r (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg)
{
        struct timespec start, end;
        void (*fn)(void *base, size_t, size_t, int (*compar)(const void *, const void *, void *), void *arg);
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"qsort_r\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"qsort_r\");
            return;
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        fn(base, nmemb, size, compar, arg);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"qsort_r\", end);
}

void
qsort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
        struct timespec start, end;
        void (*fn)(void *, size_t, size_t, int (*compar)(const void *, const void *));
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"qsort\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"qsort\");
            return;
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        fn(base, nmemb, size, compar);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"qsort\", end);
}

void
pthread_cleanup_push (void (*routine)(void *), void *arg){
        struct timespec start, end;
        void (*fn)(void (*routine)(void *), void *arg);
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"pthread_cleanup_push\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"pthread_clean_up_push\");
            return;
        }
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        fn(routine, arg);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"pthread_cleanup_push\", end);
}

void *
lsearch (const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
        struct timespec start, end;
        void * (*fn)(const void *, void *, size_t *, size_t, int(*compar)(const void *, const void *));
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"lsearch\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"lsearch\");
            return;
        }
        void *rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval = fn(key, base, nmemb, size, compar);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"lsearch\", end);
        return rval;
}

void *
lfind (const void *key, const void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
        struct timespec start, end;
        void * (*fn)(const void *, void *, size_t *, size_t, int(*compar)(const void *, const void *));
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"lfind\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"lfind\");
            return;
        }
        void *rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval = fn(key, base, nmemb, size, compar);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"lfind\", end);
        return rval;
}

void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
        struct timespec start, end;
        void * (*fn)(const void *, void *, size_t *, size_t, int(*compar)(const void *, const void *));
        _backtrace();
        fn = dlsym(RTLD_NEXT, \"bsearch\");
        if (fn == NULL){
            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"bsearch\");
            return;
        }
        void *rval;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
        rval = fn(key, base, nmemb, size, compar);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        _timespec_sub(&end, &start);
        _logtime(\"bsearch\", end);
        return rval;
}

//void *
//malloc(size_t size)
//{
//       struct timespec start, end;
//       static void * (*fn)(size_t);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"malloc\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"malloc_logging\");
//           return;
//       }
//       void *rval;
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(size);
//       lol(\"MALAKAS\");
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
////       _timespec_sub(&end, &start);
////       _logtime(\"malloc\", end);
//       return rval;
//}
////
//void *
//memset (void *s, int c, size_t n)
//{
//       struct timespec start, end;
//       static void * (*fn)(void *, int, size_t);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"memset_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"memset\");
//           return;
//       }
//       void *rval;
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(s, c, n);
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
////       _timespec_sub(&end, &start);
////       _logtime(\"memset\", end);
//       return rval;
//}
//
//int
//mprotect (void *addr, size_t len, int prot)
//{
////       struct timespec start, end;
//       static int  (*fn)(void *, size_t, int);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"mprotect_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"mprotect\");
//           return;
//       }
//       int rval;
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(addr, len, prot);
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
////       _timespec_sub(&end, &start);
////       _logtime(\"mprotect\", end);
//       return rval;
//}
//
//void *
//memcpy (void *dest, const void *src, size_t n)
//{
//       struct timespec start, end;
//       static void * (*fn)(void *, const void *, size_t);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"memcpy_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"memcpy_logging\");
//           return;
//       }
//       void *rval;
//       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(dest, src, n);
//       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//       _timespec_sub(&end, &start);
//       _logtime(\"memcpy\", end);
//       return rval;
//}
//
//void
//free (void *ptr)
//{
//        struct timespec start, end;
//        static void  (*fn)(void *);
//        if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"free_logging\");
//        if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"free_logging\");
//           return;
//       }
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       fn(ptr);
//       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//       _timespec_sub(&end, &start);
//       _logtime(\"free\", end);
//}
//
//int
//chdir (const char *path)
//{
//        struct timespec start, end;
//        static int  (*fn)(const char *);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"chdir_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"chdir\");
//           return;
//       }
//       int rval;
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(path);
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
////       _timespec_sub(&end, &start);
////       _logtime(\"chdir\", end);
//       return rval;
//}
//
//int
//mkdir (const char *pathname, mode_t mode)
//{
//       struct timespec start, end;
//       static int  (*fn)(const char *, mode_t);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"mkdir_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"mkdir\");
//           return;
//       }
//       int rval;
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(pathname, mode);
////       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
////       _timespec_sub(&end, &start);
////       _logtime(\"mkdir\", end);
//       return rval;
//}
//
//int
//nanosleep (const struct timespec *req, struct timespec *rem)
//{
//       struct timespec start, end;
//       static int  (*fn)(const struct timespec *, struct timespec *);
//       if (fn == NULL)
//           fn = dlsym(RTLD_NEXT, \"nanosleep_logging\");
//       if (fn == NULL){
//           fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"nanosleep\");
//           return;
//       }
//       int rval;
//       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//       rval = fn(req, rem);
//       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//       _timespec_sub(&end, &start);
//       _logtime(\"nanosleep\", end);
//       return rval;
//}

int
ioctl (int d, int request, ...)
{
    struct timespec start, end;
    static int (*fn)(int, int, ...);
    _backtrace();
    if (fn == NULL)
        fn = dlsym(RTLD_NEXT, \"ioctl\");
    if (fn == NULL){
        fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"ioctl\");
        return;
    }
    va_list ap;
    va_start(ap, request);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    int rval;
    rval = fn(d, request, ap);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    _timespec_sub(&end, &start);
    _logtime(\"ioctl\", end);
    va_end(ap);
    return rval;
}
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
    echo "       __sync_fetch_and_add(&entered, 1);"
    echo "       struct timespec start, end;"
    echo "       static $ftype (*fn)($farg_signatures);"
    echo "       _backtrace();"
    echo "       if (fn == NULL)"
    echo "           *(void **)(&fn) = dlsym(RTLD_NEXT, \"$fname\");"
    echo "       if (fn == NULL){"
    echo "            fprintf(stderr, \"dlsym: Error while loading symbol: <%s>\n\", \"$fname\");"
    echo "            return;"
    echo "       }"
    if [ "$farg_names" = "void" -a "$ftype" = "void " ]; then
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "       fn();"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "       _timespec_sub(&end, &start);"
        echo "       _logtime(\"$fname\", end);"
        echo "       __sync_fetch_and_sub(&entered, 1);"
    elif [ "$farg_names" = "void"  -a "$ftype" != "void " ]; then
        echo "       $ftype rval;"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "       rval = fn();"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "       _timespec_sub(&end, &start);"
        echo "       _logtime(\"$fname\", end);"
        echo "       __sync_fetch_and_sub(&entered, 1);"
        echo  "      return rval;"
    elif [ "$farg_names" != "void"  -a  "$ftype" = "void " ]; then
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "       fn($farg_names);"
        echo "       _timespec_sub(&end, &start);"
        echo "       _logtime(\"$fname\", end);"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "       __sync_fetch_and_sub(&entered, 1);"
    else
        echo "       $ftype rval;"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);"
        echo "       rval = fn($farg_names);"
        echo "       clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);"
        echo "       _timespec_sub(&end, &start);"
        echo "       _logtime(\"$fname\", end);"
        echo "       __sync_fetch_and_sub(&entered, 1);"
        echo "       return rval;"
    fi
    echo "}"
    echo ""
}

IFILE="$1"
echo_header
echo_backtrace_function
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
