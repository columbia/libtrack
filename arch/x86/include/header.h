#define _GNU_SOURCE
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
#include <mqueue.h>
#include <poll.h>
#include <regex.h>
#include <semaphore.h>
#include <setjmp.h>
#include <wordexp.h>
#include <assert.h>
#include <stdarg.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_FRAMES 10
#define NAME_LEN 4096
#define LINE_LEN 4096
#define BUF_LEN 8192
#define MODE O_RDWR | O_CREAT,  S_IRWXU


__thread char filename[NAME_LEN];
__thread int thread_fd = -1;
__thread unsigned int entered = 0;
__thread char tmpbuf[BUF_LEN];
__thread unsigned long tmppos = 0;
__thread unsigned long tmpallocs = 0;

static void * (*libc_calloc)(size_t, size_t);
static void * (*temp_calloc)(size_t nmemb, size_t size);
static void (*libc_free)(void *);
static void (*temp_free)(void *);
