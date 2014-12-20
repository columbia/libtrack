/*
 * Valedectorian arguments are a problem - do not trace for now
 */
int
ioctl (int d, int request, ...)
{
        int rval;
        va_list ap;
        struct timespec start, end;
        static int (*fn)(int, int, ...);

        __sync_fetch_and_add(&entered, 1);
        va_start(ap, request);
        if (fn == NULL)
             fn = dlsym(RTLD_NEXT, "ioctl");
        if (fn == NULL){
             fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ioctl");
             goto out;
        }
        if (entered == 1) {
             _backtrace();
             clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
             rval = fn(d, request, ap);
             clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
             _timespec_sub(&end, &start);
             _logtime("ioctl", end);
        } else {
             rval = fn(d, request, ap);
        }
out:
       va_end(ap);
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memset (void *s, int c, size_t n)
{
	struct timespec start, end;
        void *rval;
	static void * (*fn)(void *, int, size_t);

        __sync_fetch_and_add(&entered, 1);
	if (fn == NULL)
		 *(void **)(&fn) = dlsym(RTLD_NEXT, "memset");
	if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "memset");
            goto out;
        }
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(s, c, n);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
                _logtime("memset", end);
        } else {
                rval = fn(s, c, n);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

/*
 * fd ops
 */
ssize_t
read (int fd, void *buf, size_t count)
{
        struct timespec start, end;
        static ssize_t  (*fn)(int , void *, size_t );
        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
                *(void **)(&fn) = dlsym(RTLD_NEXT, "read");
        if (fn == NULL){
                fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "read");
                goto out;
        }
        ssize_t  rval;
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(fd, buf, count);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
		char name[] = "read_?";
		name[5] = fd_type(fd);
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
               *(void **)(&fn) = dlsym(RTLD_NEXT, "write");
        if (fn == NULL){
                fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "write");
                goto out;
        }
        ssize_t  rval;
        if (entered == 1) {
                _backtrace();
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                rval = fn(fd, buf, count);
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                _timespec_sub(&end, &start);
		char name[] = "write_?";
		name[6] = fd_type(fd);
               _logtime(name, end);
       } else {
               rval = fn(fd, buf, count);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

/*
 * sleeps
 */
int 
nanosleep (const struct timespec *req, struct timespec *rem)
{
       struct timespec start, end;
       static int  (*fn)(const struct timespec *, struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "nanosleep");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "nanosleep");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(req, rem);
}

int 
clock_nanosleep (clockid_t clock_id, int flags, const struct timespec *request, struct timespec *remain)
{
       struct timespec start, end;
       static int  (*fn)(clockid_t , int , const struct timespec *, struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clock_nanosleep");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clock_nanosleep");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
	return fn(clock_id, flags, request, remain);
}

/*
 * [X]alloc
 */
void *
realloc (void *ptr, size_t size)
{
        void * rval;
        struct timespec start, end;
        static void * (*fn)(void *, size_t);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "realloc");
        if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "realloc");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(ptr, size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("realloc", end);
        } else {
            rval = fn(ptr, size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
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

void *
memalign (size_t alignment, size_t size)
{
        struct timespec start, end;
        static void * (*fn)(size_t, size_t);
        void * rval;

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memalign");
        if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "memalign");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(alignment, size);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("memalign", end);
        } else {
            rval = fn(alignment, size);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
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

/*
 * Do not time the following - to avoid deadlocks
 */

/*
 * jumps
 */
int
setjmp (jmp_buf env)
{
       struct timespec start, end;
       static int  (*fn)(jmp_buf );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setjmp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setjmp");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(env);
}

void 
siglongjmp (sigjmp_buf env, int val)
{
       static void  (*fn)(jmp_buf , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "siglongjmp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "siglongjmp");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
	fn(env, val);
}

void
longjmp (jmp_buf env, int val)
{
       static void  (*fn)(jmp_buf , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "longjmp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "longjmp");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       fn(env, val);
}

/*
 * exec family
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
       if (entered == 1)
               _backtrace();
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
       if (entered == 1)
               _backtrace();
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
       if (entered == 1)
               _backtrace();
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
gettimeofday (struct timeval *tv, struct timezone *tz)
{
       struct timespec start, end;
       static int  (*fn)(struct timeval *, struct timezone *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gettimeofday");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gettimeofday");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(tv, tz);
}

int 
waitid (idtype_t idtype, id_t id, siginfo_t *infop, int options)
{
       struct timespec start, end;
       static int  (*fn)(idtype_t , id_t , siginfo_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "waitid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "waitid");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(idtype, id, infop, options);
}

pid_t 
wait (int *status)
{
       struct timespec start, end;
       static pid_t  (*fn)(int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "wait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "wait");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(status);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("wait", end);
       } else {
               rval = fn(status);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

pid_t 
waitpid (pid_t pid, int *status, int options)
{
       struct timespec start, end;
       static pid_t  (*fn)(pid_t , int *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "waitpid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "waitpid");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       return fn(pid, status, options);
}

unsigned int 
sleep (unsigned int seconds)
{
       struct timespec start, end;
       static unsigned int  (*fn)(unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sleep");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sleep");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(seconds);
}

void 
abort (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "abort");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "abort");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
	fn();
}

int 
sigpause (int sigmask)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigpause");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigpause");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(sigmask);
}

int 
sigsuspend (const sigset_t *mask)
{
       struct timespec start, end;
       static int  (*fn)(const sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigsuspend");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigsuspend");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(mask);
}

int 
sigtimedwait (const sigset_t *set, siginfo_t *info, const struct timespec *timeout)
{
       struct timespec start, end;
       static int  (*fn)(const sigset_t *, siginfo_t *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigtimedwait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigtimedwait");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(set, info, timeout);
}

int 
sigwait (const sigset_t *set, int *sig)
{
       struct timespec start, end;
       static int  (*fn)(const sigset_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigwait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigwait");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(set, sig);
}

int 
sigwaitinfo (const sigset_t *set, siginfo_t *info)
{
       struct timespec start, end;
       static int  (*fn)(const sigset_t *, siginfo_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigwaitinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigwaitinfo");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(set, info);
}

int 
sched_yield (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_yield");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_yield");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
      return fn();
}


int 
pause (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pause");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pause");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
      return fn();
}

int 
sem_wait (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_wait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_wait");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(sem);
}
