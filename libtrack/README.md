### Libtrack: library wrapper and system-level tracing utilities
---


The primary interface to the *libtrack* utility is the **wraplib.sh** script.
This script will create a project which can be compiled as an Android or Ubuntu
library depending on the options.

NOTE: the libtrack utility is not intended to be directly compiled!

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

### Description

At a high level, the wraplib.sh script executes the following.

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



### Usage


    Usage: ./wraplib.sh  --lib path/to/library 
                         --arch {android|arm|x86}
                         --type {elf|macho}
                         --out path/to/output/dir
                        [--wrap-specific symfile]
                        [--use-ndk]
                        [--wrap-all]
    
            --wrap-all                      Wrap (trace) all functions in the library
            --arch {android|arm|x86}        Architecture for syscall wrappers
            --lib path/to/library           Library (or directory of libraries) to search for syscalls
    
            --type {elf|macho}              Specify the type of input library (avoid auto-detection)
    
            --out output/dir                Directory to put output C wrappers (defaults to .)
    
    Environment variables:
            CROSS_COMPILE                   Used to properly dump ELF objects. Defaults to 'arm-eabi-'


The following command will create a directory named "wrapped/libc.so/" which will
contain an Android project that can be compiled via NDK or AOSP. This project
will contain all the libc entry points, and will log calls to libc functions
that invoke system calls.

    ./wraplib.sh --lib resources/libc.so  --arch arm  --type elf --out wrapped

To make this project build-able using the NDK:

    ./wraplib.sh --lib resources/libc.so  --arch arm  --type elf --out wrapped --use-ndk

### Using Wrapped Libraries

After creating a wrapped library, there are some more steps required in order to plug it 
into a device and produce logs, these include (1) compiling the wrapped library, (2) injecting
it in the target device, and (3) preloading the original shared library. The last step is particularly
important in the context of libc.so, which includes a set of necessary exported variables.

Since these three steps require some more effort we have provided a Makefile that automates the
whole process in a rooted Android device. Moreover, under script/android, we provide a collection 
of scripts for  starting/stopping tracing and unpacking android logs. 


### Example (Android)

A complete example of wrapping bionic libc of Android 4.3 using our Makefile will look like what follows.

    cd libtrack && make
    
    Hidding symbols and initializing static lookup  table.
    ./wraplib.sh --use-ndk --out wrapped --lib droid --type elf --arch arm --wrap-all
        Processing "droid/libc.so"
        disassembling...
        extracting functions...
        parsing function list...
            (found 1101 ELF entry points, 1099 non-syscall)
        searching dynamic symbol table for duplicate symbols...63
        stripping 'droid/libc.so' into 'wrapped/libc.so/jni/real_libc.so'...
        Hidding 1181 symbols in file wrapped/libc.so/jni/real_libc.so.
        Setting soname to '_ibc_so' in wrapped/libc.so/jni/real_libc.so
        creating library project in 'wrapped/libc.so/jni'...
        writing 0 syscall wrappers
        writing 1099 function wrappers...........................3.2...........
                                     2.2...........2..........................
                                     .........................................
                                     ......9..................................
                                     .......................4..2..3.2.........
                                     ......2...2.2....2.2.....................
                                     .........................................
                                     ...2...........2.........................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .............2...........................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .........................................
                                     ...2.....................................
                                     ....................2....................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .........................................
                                     .........................................
                                     ..3.3.3.3..2..2..2.2.2..2.2.2.2.2.2.2.2.2.
                                     2.2.3..2......2.2.2..2.2.2.2.2.2.2.2.2.2.
                                     2....2..................2...........2.2.2.
                                     2.2.........
    Installing Wrappers
    Reboot in recovery mode
    Wait 40 seconds before mounting system
    make[1]: Entering directory '/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'
    Invoking NDK build
    Android NDK: WARNING:/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni/Android.mk:c_wrapped: non-system libraries in linker flags: /home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni/real_libc.so -Wl,-soname=libc.so    
    Android NDK:     This is likely to result in incorrect builds. Try using LOCAL_STATIC_LIBRARIES    
    Android NDK:     or LOCAL_SHARED_LIBRARIES instead to list the library dependencies of the    
    Android NDK:     current module    
    make[2]: Entering directory `/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'
    [armeabi-v7a] Compile arm    : c_wrapped <= crtbegin_so.c
    [armeabi-v7a] Compile arm    : c_wrapped <= libc.S
    [armeabi-v7a] Compile arm    : c_wrapped <= backtrace.c
    [armeabi-v7a] Compile++ arm  : c_wrapped <= java_backtrace.cpp
    [armeabi-v7a] Compile arm    : c_wrapped <= libz.c
    [armeabi-v7a] Compile arm    : c_wrapped <= wrap_lib.c
    [armeabi-v7a] Compile arm    : c_wrapped <= wrap_tls.c
    [armeabi-v7a] Compile arm    : c_wrapped <= crtend_so.S
    [armeabi-v7a] Compile arm    : c_wrapped <= libc_wrappers.c
    [armeabi-v7a] Compile++ arm  : c_wrapped <= libc_init.cpp
    [armeabi-v7a] SharedLibrary  : libc_wrapped.so
    [armeabi-v7a] Install        : libc_wrapped.so => libs/armeabi-v7a/libc_wrapped.so
    make[2]: Leaving directory `/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'
    make[1]: Leaving directory '/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'
    make[1]: Entering directory '/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'
    Installing libc.so into /system/lib...
    Installing 'libc_wrapped.so' into '/system/lib'...
    1321 KB/s (534980 bytes in 0.395s)
    1315 KB/s (298180 bytes in 0.221s)
    done.

    I am about to overwrite /system/lib/libc.so!
    Are you sure it's OK? [y|N]: remount succeeded
    Here we go (I'll back it up to /system/lib/libc.so.bak first)!
    done.

    Be sure to preload the data-only library:
        export LD_PRELOAD=/system/lib/_ibc_so

    make[1]: Leaving directory '/home/vatlidak/repos/libtrack/libtrack/wrapped/libc.so/jni'


At this point your android device has a wrapped bionic libc and you only need to 
activate tracing for some logs to be produced. First, inspect our tools in your device as follows:
    
    adb push scripts/android/*
    adb push scripts/android/tkill/*
    
Then activate tracing and interact with your device
    
    adb shell start_tracing
    Unmounting trace_logs
    Mounting tmpfs on /data/trace_logs
    Dropping VM caches
    Maximizing CPU performance...
    Done.
    Starting the trace!

After having interactig with your device sufficiently you can stop the tracing and collect the logs

    adb shell stop_tracing                                                                                              
    Tracing stopped. waiting a second
    Flushing trace logs
    Zygote might reboot - don't be alarmed!
    Just make sure the device doesn't reboot.
    Size before flush: 
    Sending signals...
    Logs ready to be pulled!


At this point you can collect (pull) the logs from /data/trace_logs and parce them in any meaningful way.

Note: Having busybox installed in your device will be more than helpful!


### Example (Ubuntu)

In Ubuntu the situation is considerably easier because applications can be launched from the terminal with
LD_PRELOAD passed in the command line. To build a wrapped library in ubuntu execute the following:
    
    ./wraplib.sh --arch x86                                                                                                   
    /libtrack/scripts
    gcc -w -fPIC -shared -rdynamic -o interpose.so temp.c -ldl -lrt




