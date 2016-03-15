systrace
========

Library wrapper and system-level tracing utilities

# Usage

The primary interface to the *systrace* utility is the **wraplib.sh** script.
This script will create a project which can be compiled as an Android or iOS
library depending on the options.

NOTE: the systrace utility is not intended to be directly compiled!

Instead,
the wraplib.sh script takes as input a library file (the "wrapped" library),
and outputs a project directory which will compile into a library with the
same name that contains all the entry points of the "wrapped" library. Some
subset of these entry points can be "logged" to disk whenever they are invoked
at runtime.

The subset of entry points can either be all system calls (which are
auto-detected), all entry points (specified in the wraplib.sh options),
or a manual subset using the *scripts/api_filter.pl* file.

The log entry for a call into one of these entry points is a full backtrace
(including the Java stack on Android). By default the logging system attempts to
use libz.so to compress the logs before writing to disk, and maintains an
aggressive caching and buffering system that attempts to mitigate the runtime
impact of logging.

### wraplib.sh usage

    Usage: ./wraplib.sh --lib path/to/library 
                              [--wrap-all]
                              [--arch {android|arm|x86}]
                              [--type {elf|macho}]
                              [--out path/to/output/dir]
                              [--use-ndk]
    
            --wrap-all                      Wrap (trace) all functions in the library
            --arch {android|arm|x86}        Architecture for syscall wrappers
            --lib path/to/library           Library (or directory of libraries) to search for syscalls
    
            --type {elf|macho}              Specify the type of input library (avoid auto-detection)
    
            --out output/dir                Directory to put output C wrappers (defaults to .)
    
    Environment variables:
            CROSS_COMPILE                   Used to properly dump ELF objects. Defaults to 'arm-eabi-'

### Examples

#### Wrap syscalls in Android libc.so
The following command will create a directory named "alibc/libc.so/" which will
contain an Android project that can be compiled via NDK or AOSP. This project
will contain all the libc entry points, and will log calls to libc functions
that invoke system calls.

    ./wraplib.sh --lib path/to/libc.so --arch android --out alibc

To make this project build-able using the NDK:

    ./wraplib.sh --lib path/to/libc.so --arch android --out alibc --use-ndk

#### Wrap all entry points in Android libsqlite.so
All entry points to libsqlite will be logged. Output project will be placed in
"sql/libsqlite.so/" and build-able using the NDK:

    ./wraplib.sh --lib path/to/libsqlite.so --wrap-all --arch android --out sql --use-ndk


### wraplib.sh Description

1. Disassemble text section of an ELF or Mach-O binary.

2. Parse dissasembled text section to extract and mark as syscalls entry-points that invoke
a system calls using "SVC" command. By default entry-points that are not black-listed will
be marked as syscalls, while black-listed entry-points, such as string related functions,
will be dropped.

3. Parse dissasembled text section to extract and mark as syscalls entry-point belonging to
intra-syscalls tree, i.e., entry-points with branches targeting previously identified entry-points
that are known to invoke system calls. Also, mark as syscalls all entry-points that match a
static index of POSIX symbols. Similarly to step 2., drop all black-listed symbols.

4. Extract collectivelly all entry-points defined in text section, except @plt symbols, and mark
them as functions if they have not been marked as syscalls in steps (2), (3). If !SHOULD\_WRAP
ignore those symbols.

5. Get all symbols names exported via the dynamic symbol table (excluding weak syms) and identify
duplicate function definitions, i.e., diffent symbols refering to the same address in the text.

6. Get all symbol names exported via the dynamic symbol table (including weak syms) that are
functions defined in the text section of the binary and change their visibility into "hidden"
(ELF) or strip them (Mach-O)

7. Create a file with assembly macros to WRAP entry-points marked a syscalls, and PASS entry-points
marked as functions.