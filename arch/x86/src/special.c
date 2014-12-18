/*
 * Take some special care for exec family and exec: skip timing
 */
int 
execv (const char *path, char *const argv[])
{
       struct timespec start, end;
       static int  (*fn)(const char *, char *const );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "execv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "execv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(path, argv);
}

int 
execve (const char *filename, char *const argv[], char *const envp[])
{
       struct timespec start, end;
       static int  (*fn)(const char *, char *const , char *const );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "execve");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "execve");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(filename, argv, envp);
}

int 
execvp (const char *file, char *const argv[])
{
       struct timespec start, end;
       static int  (*fn)(const char *, char *const );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "execvp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "execvp");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return  fn(file, argv);
}


pid_t
fork (void)
{
        static pid_t  (*fn)(void);
        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
               *(void **)(&fn) = dlsym(RTLD_NEXT, "fork");
        if (fn == NULL){
                fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fork");
                goto out;
        }
        if (entered == 1)
                _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return  fn();
}

int
pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
        int rval;
        struct timespec start, end;
        static  int (*fn)(pthread_t *, const pthread_attr_t *,
                  void *(*start_routine) (void *), void *arg());

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_create");
        if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "pthread_create");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(thread, attr, start_routine, arg);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("pthread_create", end);
        } else {
            rval = fn(thread, attr, start_routine, arg);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void
pthread_cleanup_push (void (*routine)(void *), void *arg)
{
        struct timespec start, end;
        static  void (*fn)(void (*routine)(void *), void *arg);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "pthread_cleanup_push");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "pthread_clean_up_push");
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
        _logtime("pthread_cleanup_push", end);
}

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
            *(void **)(&temp_calloc) = dlsym(RTLD_NEXT, "calloc");
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
                _logtime("calloc", end);
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
            *(void **)(&temp_free) = dlsym(RTLD_NEXT, "free");
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
                _logtime("free", end);
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
           *(void **)(&fn) = dlsym(RTLD_NEXT, "malloc");
        if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "malloc");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("malloc", end);
        } else {
            rval = fn(size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

//void *
//realloc (void *ptr, size_t size)
//{
//        void * rval;
//        struct timespec start, end;
//        static void * (*fn)(void *, size_t);
//
//        __sync_fetch_and_add(&entered, 1);
//        if (fn == NULL)
//           *(void **)(&fn) = dlsym(RTLD_NEXT, "realloc");
//        if (fn == NULL) {
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
//                    "realloc");
//            goto out;
//        }
//        if (entered == 1) {
//            _backtrace();
//            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//            rval = fn(ptr, size);
//            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//            _timespec_sub(&end, &start);
//            _logtime("realloc", end);
//        } else {
//            rval = fn(ptr, size);
//        }
//out:
//        __sync_fetch_and_sub(&entered, 1);
//        return rval;
//}
//
//void *
//memalign (size_t alignment, size_t size)
//{
//        struct timespec start, end;
//        static void * (*fn)(size_t, size_t);
//        void * rval;
//
//        __sync_fetch_and_add(&entered, 1);
//        if (fn == NULL)
//           *(void **)(&fn) = dlsym(RTLD_NEXT, "memalign");
//        if (fn == NULL) {
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
//                    "memalign");
//            goto out;
//        }
//        if (entered == 1) {
//            _backtrace();
//            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//            rval = fn(alignment, size);
//            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//            _timespec_sub(&end, &start);
//            _logtime("memalign", end);
//        } else {
//            rval = fn(alignment, size);
//        }
//out:
//        __sync_fetch_and_sub(&entered, 1);
//        return rval;
//}
//
//
//void *
//libc_memset (void *dstpp, int sc, size_t len)
//{
//        int OPSIZ = sizeof(long);
//        typedef unsigned long op_t;
//
//
//        unsigned int c = sc;
//        long int dstp = (long int) dstpp;
//
//        if (len >= 8)
//        {
//                size_t xlen;
//                op_t cccc;
//
//                cccc = (unsigned char) c;
//                cccc |= cccc << 8;
//                cccc |= cccc << 16;
//                if (OPSIZ > 4)
//                /* Do the shift in two steps to avoid warning if long has 32 bits.  */
//                        cccc |= (cccc << 16) << 16;
//
//                /* There are at least some bytes to set.
//                    No need to test for LEN == 0 in this alignment loop.  */
//                while (dstp % OPSIZ != 0)
//                {
//                        ((unsigned char *) dstp)[0] = c;
//                        dstp += 1;
//                        len -= 1;
//                }
//
//                xlen = len / (OPSIZ * 8);
//                while (xlen > 0)
//                {
//                        ((op_t *) dstp)[0] = cccc;
//                        ((op_t *) dstp)[1] = cccc;
//                        ((op_t *) dstp)[2] = cccc;
//                        ((op_t *) dstp)[3] = cccc;
//                        ((op_t *) dstp)[4] = cccc;
//                        ((op_t *) dstp)[5] = cccc;
//                        ((op_t *) dstp)[6] = cccc;
//                        ((op_t *) dstp)[7] = cccc;
//                        dstp += 8 * OPSIZ;
//                        xlen -= 1;
//                }
//                len %= OPSIZ * 8;
//
//                xlen = len / OPSIZ;
//                while (xlen > 0)
//                {
//                        ((op_t *) dstp)[0] = cccc;
//                        dstp += OPSIZ;
//                        xlen -= 1;
//                }
//                len %= OPSIZ;
//        }
//
//        /* Write the last few bytes.  */
//        while (len > 0)
//        {
//                ((unsigned char *) dstp)[0] = c;
//                dstp += 1;
//                len -= 1;
//        }
//        return dstpp;
//}
//
//void *
//memset (void *s, int c, size_t n)
//{
//        struct timespec start, end;
//      void *rval;
//
//        __sync_fetch_and_add(&entered, 1);
//        if (entered == 1) {
//                _backtrace();
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//                rval = libc_memset(s, c, n);
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//                _timespec_sub(&end, &start);
//                _logtime("memset", end);
//        } else {
//                rval = libc_memset(s, c, n);
//        }
//        __sync_fetch_and_sub(&entered, 1);
//        return s;
//}
//
//int
//setjmp (jmp_buf env)
//{
//       struct timespec start, end;
//       static int  (*fn)(jmp_buf );
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(RTLD_NEXT, "setjmp");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setjmp");
//            goto out;
//       }
//       int  rval;
//       if (entered == 1)
//               _backtrace();
//       rval = fn(env);
//out:
//       __sync_fetch_and_sub(&entered, 1);
//       return rval;
//}
//
//
//
//void 
//siglongjmp (sigjmp_buf env, int val)
//{
//       struct timespec start, end;
//       static void  (*fn)(sigjmp_buf , int );
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(RTLD_NEXT, "siglongjmp");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "siglongjmp");
//            goto out;
//       }
//       if (entered == 1) {
//               _backtrace();
//               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//               fn(env, val);
//               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//               _timespec_sub(&end, &start);
//               _logtime("siglongjmp", end);
//       } else {
//               fn(env, val);
//       }
//out:
//       __sync_fetch_and_sub(&entered, 1);
//}
//
//
//
//void
//longjmp (jmp_buf env, int val)
//{
//       struct timespec start, end;
//       static void  (*fn)(jmp_buf , int );
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(RTLD_NEXT, "longjmp");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "longjmp");
//            goto out;
//       }
//       if (entered == 1)
//               _backtrace();
//       fn(env, val);
//out:
//       __sync_fetch_and_sub(&entered, 1);
//}
//
//ssize_t
//read (int fd, void *buf, size_t count)
//{
//        struct timespec start, end;
//        static ssize_t  (*fn)(int , void *, size_t );
//        __sync_fetch_and_add(&entered, 1);
//        if (fn == NULL)
//                *(void **)(&fn) = dlsym(RTLD_NEXT, "read");
//        if (fn == NULL){
//                fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "read");
//                goto out;
//        }
//        ssize_t  rval;
//        if (entered == 1) {
//                char name[] = "read_?";
//                name[5] = fd_type(fd);
//                _backtrace_given_name(name);
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//                rval = fn(fd, buf, count);
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//                _timespec_sub(&end, &start);
//                _logtime(name, end);
//        } else {
//                rval = fn(fd, buf, count);
//        }
//out:
//        __sync_fetch_and_sub(&entered, 1);
//        return rval;
//}
//
//
//
//ssize_t
//write (int fd, const void *buf, size_t count)
//{
//        struct timespec start, end;
//        static ssize_t  (*fn)(int , const void *, size_t );
//        __sync_fetch_and_add(&entered, 1);
//        if (fn == NULL)
//               *(void **)(&fn) = dlsym(RTLD_NEXT, "write");
//        if (fn == NULL){
//                fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "write");
//                goto out;
//        }
//        ssize_t  rval;
//        if (entered == 1) {
//                char name[] = "write_?";
//                name[6] = fd_type(fd);
//                _backtrace_given_name(name);
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//                rval = fn(fd, buf, count);
//                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//                _timespec_sub(&end, &start);
//               _logtime(name, end);
//       } else {
//               rval = fn(fd, buf, count);
//       }
//out:
//       __sync_fetch_and_sub(&entered, 1);
//       return rval;
//}
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
//        fn = dlsym(RTLD_NEXT, "ioctl");
//    if (fn == NULL){
//        fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ioctl");
//        goto out;
//    }
//    va_list ap;
//    va_start(ap, request);
//    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//    int rval;
//    rval = fn(d, request, ap);
//    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//    _timespec_sub(&end, &start);
//    _logtime("ioctl", end);
//    va_end(ap);
//out:
//    __sync_fetch_and_sub(&entered, 1);
//    return rval;
//}	
