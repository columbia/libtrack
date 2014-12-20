#!/bin/bash

HEADER="/home/vatlidak/repos/systrace/arch/x86/include/header.h"
BACKTRACE="/home/vatlidak/repos/systrace/arch/x86/src/backtrace.c"
LOGTIME="/home/vatlidak/repos/systrace/arch/x86/src/logtime.c"

GNU_EXTENSIONS="/home/vatlidak/repos/systrace/arch/x86/src/gnu_extensions.c"
SPECIAL="/home/vatlidak/repos/systrace/arch/x86/src/special.c"
ALGO="/home/vatlidak/repos/systrace/arch/x86/src/algorithms.c"
ARGS="/home/vatlidak/repos/systrace/arch/x86/src/arguments.c"
FS="/home/vatlidak/repos/systrace/arch/x86/src/fs.c"
IPC="/home/vatlidak/repos/systrace/arch/x86/src/ipc.c"
MEM="/home/vatlidak/repos/systrace/arch/x86/src/memory.c"
NET="/home/vatlidak/repos/systrace/arch/x86/src/network.c"
PROC="/home/vatlidak/repos/systrace/arch/x86/src/processes.c"
PTHREADS="/home/vatlidak/repos/systrace/arch/x86/src/pthreads.c"
TERM="/home/vatlidak/repos/systrace/arch/x86/src/terminals.c"
TIME="/home/vatlidak/repos/systrace/arch/x86/src/time.c"
USERS="/home/vatlidak/repos/systrace/arch/x86/src/users.c"
MISC="/home/vatlidak/repos/systrace/arch/x86/src/misc.c"
#
if [ ! -f $HEADER ]; then
    echo "Missing HEADER"
    exit -1
fi
if [ ! -f $BACKTRACE ]; then
    echo "Missing BACKTRACE"
    exit -1
fi

if [ ! -f $LOGTIME ]; then
    echo "Missing LOGTIME"
    exit -1
fi

if [ ! -f $SPECIAL ]; then
    echo "Missing SPECIAL"
    exit -1
fi

if [ ! -f $GNU_EXTENSIONS ]; then
    echo "Missing GNU_EXTENSIONS"
    exit -1
fi

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

cat ${HEADER} > temp.c
cat ${BACKTRACE} >> temp.c
cat ${LOGTIME} >> temp.c
cat ${SPECIAL} >> temp.c
cat ${FS} >> temp.c
cat ${IPC} >> temp.c
cat ${MEM} >> temp.c
cat ${NET} >> temp.c
cat ${PROC} >> temp.c
cat ${PTHREADS} >> temp.c
cat ${TERM} >> temp.c
cat ${TIME} >> temp.c
cat ${USERS} >> temp.c
##
#cat ${MISC} >> temp.c
#cat ${ALGO} >> temp.c
#cat ${ARGS} >> temp.c
#cat ${GNU_EXTENSIONS} >> temp.c
make
rm temp.c
