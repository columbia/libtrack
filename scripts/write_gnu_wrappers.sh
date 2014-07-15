#!/bin/bash

##
##
##    for name in `cat posix`; do
##        man 3 $name | col -bx > ttt
##        while read line; do
##            echo "$line" | grep "[a-z]\+("
##            if [ "$line" = "DESCRIPTION" ]; then
##                break
##            fi;
##        done <  ttt
##        rm ttt
##    done | sort -u > prototypes3.txt
##
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

#define MAX_FRAMES 2
#define NAME_LEN 512
#define LINE_LEN 512

extern char *__progname;"
}

function echo_backtrace_function()
{
    echo "
/*
 * Any libc function used in this routine should 
 * be dynamically loaded to avoid recursice loops
 *
 */
static void _backtrace()
{
    	void  *frames[MAX_FRAMES];
    	char **bt;
    	size_t i, nframes;
    	FILE *fp;
    	char name[NAME_LEN];
    	char *lib;
    	char *libbase;
    	char *sym;
    	char *symoff;
    	char *delim = \"()+[] \";
    	char line[LINE_LEN];
    	nframes = backtrace(frames, MAX_FRAMES);
    	bt = backtrace_symbols(frames, nframes);

        char * (*pstrcpy)(char *dest, const char *src) =  dlsym(RTLD_NEXT, \"strcpy\");
        char * (*pstrtok)(char *str, const char *delim) = dlsym(RTLD_NEXT, \"strtok\");
        int (*pfprintf)(FILE *stream, const char *format, ...) = dlsym(RTLD_NEXT, \"fprintf\");
//        int (*psprintf)(char *str, const char *format, ...) = dlsym(RTLD_NEXT, \"sprintf\");
        void (*pfree)(void *ptr) = dlsym(RTLD_NEXT, \"free\");
//        FILE * (*pfopen)(const char *path, const char *mode) = dlsym(RTLD_NEXT, \"fopen\");
//        int (*pfclose)(FILE *fp) = dlsym(RTLD_NEXT, \"fclose\");

        for (i = 0; i < nframes; i++)
    	{
    		pstrcpy(line, bt[i]);
    		lib = pstrtok(line, delim);
    		sym = pstrtok(NULL, delim);
    		if ( sym[0] == '0'  && sym[1] == 'x' ){
    			symoff = sym;
    			sym = \"??\";
    		}
    		else
    			symoff = pstrtok(NULL, delim);
    		libbase = pstrtok(NULL, delim);
    		/* Format:
    		 *
    		 * TIMESTAMP::STACKFRAMENO:SYM:SYMNAME:SYM_OFFSET:DLINAME:DLIBASE
    		 *
    		 */
//    		pfprintf(stderr, \"TIMESTAMP::%d:SYM:%s:%s:%s:%s\n\", i, sym, symoff, lib, libbase);
    	}
    	pfree(bt);
    //	psprintf(name, \"%s.%ld.%ld.log\", __progname, getpid(),syscall(SYS_gettid));
    //	fp = pfopen(name, \"a+\");
    //	pfprintf(stderr, \"Interpossed:%s opening:%s\n\", __progname, pathname);
    //	pfclose(fp);
}"
echo ""
}

function echo_wrapper(){
    local ftype="$1"
    local fname="$2"
    local farg_prototypes="$3"

    # remove type of arguments and keep only their names
    IFS=' ' read -a temp <<< "$farg_prototypes,"
    local farg_names=`for word in ${temp[@]}; do
        if [ "${word:${#word} - 1}" = "," ]; then
            echo "$word"
        fi
    done | sed 's,\*,,g' | tr '\n' ' ' | sed  's,[,]\s$,,g' | sed 's,\[[0-9]*\],,g'`
#    echo "$ftype" "$fname" "($farg_prototypes)"  "($farg_names)"
    # declare function signature
    echo "$ftype $fname($farg_prototypes)"
    echo "{"
    # declare function pointer to dynamically load symbol
	echo -e "\t$ftype (*fn)($farg_prototypes);"
    echo -e "\t_backtrace();"
    # dynamicaly load function from libc
	echo -e "\tfn = dlsym(RTLD_NEXT, \""$fname"\");"
    # return callback
    if [ "$farg_names" = "void" ]; then
        echo -e "\treturn fn();"
    else
        echo -e "\treturn fn($farg_names);"
    fi
    echo "}"
    echo ""
}

function echo_special_wrappers(){
    echo "
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
    int (*fn)(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg());
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"pthread_create\");
    return fn(thread, attr, start_routine, arg);
}

int glob(const char *pattern, int flags, int (*errfunc) (const char *epath, int eerrno), glob_t *pglob)
{
    int (*fn)(const char *pattern, int flags, int (*errfunc) (const char *epath, int eerrno), glob_t *pglob);
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"glob\");
    return fn(pattern, flags, errfunc, pglob);
}

void *tdelete(const void *key, void **rootp, int (*compar)(const void *, const void *))
{
    void * (*fn)(const void *key, void **rootp, int (*compar)(const void *, const void *));
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"tdelete\");
    return fn(key, rootp, compar);
}

void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg)
{
    void (*fn)(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg);
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"qsort_r\");
    return fn(base, nmemb, size, compar, arg);
}

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void (*fn)(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"qsort\");
    return fn(base, nmemb, size, compar);
}

void pthread_cleanup_push(void (*routine)(void *), void *arg){
    void (*fn)(void (*routine)(void *), void *arg);
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"pthread_cleanup_push\");
    return fn(routine, arg);
}

void *lsearch(const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
    void * (*fn)(const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *));
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"lsearch\");
    return fn(key, base, nmemb, size, compar);
}

void *lfind(const void *key, const void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
    void * (*fn)(const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *));
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"lfind\");
    return fn(key, base, nmemb, size, compar);
}

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void * (*fn)(const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *));
    _backtrace();
    fn = dlsym(RTLD_NEXT, \"bsearch\");
    return fn(key, base, nmemb, size, compar);
}"
}


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 prototypes_file"
    exit -1
fi

IFILE="$1"
echo_header
echo_backtrace_function
while read line; do
    fargs=`echo "$line" | sed 's,.*(,,g' | sed 's,[);],,g'`
    fname=`echo "$line" | sed 's,(.*,,g' | tr ' ' '\n' | tail -n 1 | sed 's,\*,,g'`
    ftype=`echo "$line" | sed 's,[a-z0-9_]\+(.*,,g'`
    echo_wrapper "$ftype" "$fname" "$fargs"
done < "$IFILE"
echo_special_wrappers
