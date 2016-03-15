/*
 * Memory
 */
wchar_t *
wmemcpy (wchar_t *dest, const wchar_t *src, size_t n)
{
       struct timespec start, end;
       static wchar_t * (*fn)(wchar_t *, const wchar_t *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "wmemcpy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "wmemcpy");
            goto out;
       }
       wchar_t * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dest, src, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("wmemcpy", end);
       } else {
               rval = fn(dest, src, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wchar_t *
wmemmove (wchar_t *dest, const wchar_t *src, size_t n)
{
       struct timespec start, end;
       static wchar_t * (*fn)(wchar_t *, const wchar_t *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "wmemmove");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "wmemmove");
            goto out;
       }
       wchar_t * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dest, src, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("wmemmove", end);
       } else {
               rval = fn(dest, src, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wchar_t *
wmemset (wchar_t *wcs, wchar_t wc, size_t n)
{
       struct timespec start, end;
       static wchar_t * (*fn)(wchar_t *, wchar_t , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "wmemset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "wmemset");
            goto out;
       }
       wchar_t * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wcs, wc, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("wmemset", end);
       } else {
               rval = fn(wcs, wc, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
swab (const void *from, void *to, ssize_t n)
{
       struct timespec start, end;
       static void  (*fn)(const void *, void *, ssize_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "swab");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "swab");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(from, to, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("swab", end);
       } else {
               fn(from, to, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

int 
mlockall (int flags)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mlockall");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mlockall");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mlockall", end);
       } else {
               rval = fn(flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mlock (const void *addr, size_t len)
{
       struct timespec start, end;
       static int  (*fn)(const void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mlock");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mlock");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mlock", end);
       } else {
               rval = fn(addr, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msync (void *addr, size_t length, int flags)
{
       struct timespec start, end;
       static int  (*fn)(void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msync");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msync");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, length, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msync", end);
       } else {
               rval = fn(addr, length, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
munlockall (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "munlockall");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "munlockall");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("munlockall", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
munlock (const void *addr, size_t len)
{
       struct timespec start, end;
       static int  (*fn)(const void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "munlock");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "munlock");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("munlock", end);
       } else {
               rval = fn(addr, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
munmap (void *addr, size_t length)
{
       struct timespec start, end;
       static int  (*fn)(void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "munmap");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "munmap");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, length);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("munmap", end);
       } else {
               rval = fn(addr, length);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memccpy (void *dest, const void *src, int c, size_t n)
{
       struct timespec start, end;
       static void * (*fn)(void *, const void *, int , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memccpy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memccpy");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dest, src, c, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memccpy", end);
       } else {
               rval = fn(dest, src, c, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memchr (const void *s, int c, size_t n)
{
       struct timespec start, end;
       static void * (*fn)(const void *, int , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memchr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memchr");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, c, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memchr", end);
       } else {
               rval = fn(s, c, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memmove (void *dest, const void *src, size_t n)
{
       struct timespec start, end;
       static void * (*fn)(void *, const void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memmove");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memmove");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dest, src, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memmove", end);
       } else {
               rval = fn(dest, src, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memrchr (const void *s, int c, size_t n)
{
       struct timespec start, end;
       static void * (*fn)(const void *, int , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memrchr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memrchr");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, c, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memrchr", end);
       } else {
               rval = fn(s, c, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
mmap (void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
       struct timespec start, end;
       static void * (*fn)(void *, size_t , int , int , int , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mmap");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mmap");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, length, prot, flags, fd, offset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mmap", end);
       } else {
               rval = fn(addr, length, prot, flags, fd, offset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
memcmp (const void *s1, const void *s2, size_t n)
{
       struct timespec start, end;
       static int  (*fn)(const void *, const void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memcmp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memcmp");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s1, s2, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memcmp", end);
       } else {
               rval = fn(s1, s2, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
pvalloc (size_t size)
{
       struct timespec start, end;
       static void * (*fn)(size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pvalloc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pvalloc");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pvalloc", end);
       } else {
               rval = fn(size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
posix_memalign (void **memptr, size_t alignment, size_t size)
{
       struct timespec start, end;
       static int  (*fn)(void **, size_t , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "posix_memalign");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "posix_memalign");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(memptr, alignment, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("posix_memalign", end);
       } else {
               rval = fn(memptr, alignment, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
memcpy (void *dest, const void *src, size_t n)
{
       struct timespec start, end;
       static void * (*fn)(void *, const void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "memcpy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "memcpy");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dest, src, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("memcpy", end);
       } else {
               rval = fn(dest, src, n);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}
/*
 * End Memory
 */
