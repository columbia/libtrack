

/*
 * FS
 */
int 
chdir (const char *path)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "chdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "chdir");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("chdir", end);
       } else {
               rval = fn(path);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mkdir (const char *pathname, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkdir");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkdir", end);
       } else {
               rval = fn(pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
catgets (nl_catd catalog, int set_number, int message_number, const char *message)
{
       struct timespec start, end;
       static char * (*fn)(nl_catd , int , int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "catgets");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "catgets");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(catalog, set_number, message_number, message);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("catgets", end);
       } else {
               rval = fn(catalog, set_number, message_number, message);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}
char *
dirname (char *path)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "dirname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "dirname");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("dirname", end);
       } else {
               rval = fn(path);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
fgets (char *s, int size, FILE *stream)
{
       struct timespec start, end;
       static char * (*fn)(char *, int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgets");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgets");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, size, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgets", end);
       } else {
               rval = fn(s, size, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
fgets_unlocked (char *s, int n, FILE *stream)
{
       struct timespec start, end;
       static char * (*fn)(char *, int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgets_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgets_unlocked");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgets_unlocked", end);
       } else {
               rval = fn(s, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
get_current_dir_name (void)
{
       struct timespec start, end;
       static char * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "get_current_dir_name");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "get_current_dir_name");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("get_current_dir_name", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

char *
getcwd (char *buf, size_t size)
{
       struct timespec start, end;
       static char * (*fn)(char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getcwd");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getcwd");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getcwd", end);
       } else {
               rval = fn(buf, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
gets (char *s)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gets");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gets");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gets", end);
       } else {
               rval = fn(s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
getwd (char *buf)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getwd");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getwd");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getwd", end);
       } else {
               rval = fn(buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
mkdtemp (char *template)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkdtemp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkdtemp");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(template);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkdtemp", end);
       } else {
               rval = fn(template);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

DIR *
fdopendir (int fd)
{
       struct timespec start, end;
       static DIR * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fdopendir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fdopendir");
            goto out;
       }
       DIR * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fdopendir", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

DIR *
opendir (const char *name)
{
       struct timespec start, end;
       static DIR * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "opendir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "opendir");
            goto out;
       }
       DIR * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("opendir", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
fdopen (int fd, const char *mode)
{
       struct timespec start, end;
       static FILE * (*fn)(int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fdopen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fdopen");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fdopen", end);
       } else {
               rval = fn(fd, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
fmemopen (void *buf, size_t size, const char *mode)
{
       struct timespec start, end;
       static FILE * (*fn)(void *, size_t , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fmemopen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fmemopen");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf, size, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fmemopen", end);
       } else {
               rval = fn(buf, size, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
fopen (const char *path, const char *mode)
{
       struct timespec start, end;
       static FILE * (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fopen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fopen");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fopen", end);
       } else {
               rval = fn(path, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
freopen (const char *path, const char *mode, FILE *stream)
{
       struct timespec start, end;
       static FILE * (*fn)(const char *, const char *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "freopen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "freopen");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, mode, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("freopen", end);
       } else {
               rval = fn(path, mode, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
popen (const char *command, const char *type)
{
       struct timespec start, end;
       static FILE * (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "popen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "popen");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(command, type);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("popen", end);
       } else {
               rval = fn(command, type);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
tmpfile (void)
{
       struct timespec start, end;
       static FILE * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tmpfile");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tmpfile");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tmpfile", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
access (const char *pathname, int mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "access");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "access");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("access", end);
       } else {
               rval = fn(pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_cancel (int fd, struct aiocb *aiocbp)
{
       struct timespec start, end;
       static int  (*fn)(int , struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_cancel");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_cancel");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_cancel", end);
       } else {
               rval = fn(fd, aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_error (const struct aiocb *aiocbp)
{
       struct timespec start, end;
       static int  (*fn)(const struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_error");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_error");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_error", end);
       } else {
               rval = fn(aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_fsync (int op, struct aiocb *aiocbp)
{
       struct timespec start, end;
       static int  (*fn)(int , struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_fsync");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_fsync");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(op, aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_fsync", end);
       } else {
               rval = fn(op, aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_read (struct aiocb *aiocbp)
{
       struct timespec start, end;
       static int  (*fn)(struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_read");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_read");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_read", end);
       } else {
               rval = fn(aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_suspend (const struct aiocb * const aiocb_list[], int nitems, const struct timespec *timeout)
{
       struct timespec start, end;
       static int  (*fn)(const struct aiocb * const , int , const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_suspend");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_suspend");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(aiocb_list, nitems, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_suspend", end);
       } else {
               rval = fn(aiocb_list, nitems, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
aio_write (struct aiocb *aiocbp)
{
       struct timespec start, end;
       static int  (*fn)(struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_write");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_write");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_write", end);
       } else {
               rval = fn(aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
atoi (const char *nptr)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "atoi");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "atoi");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nptr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("atoi", end);
       } else {
               rval = fn(nptr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
catclose (nl_catd catalog)
{
       struct timespec start, end;
       static int  (*fn)(nl_catd );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "catclose");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "catclose");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(catalog);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("catclose", end);
       } else {
               rval = fn(catalog);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
chmod (const char *path, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "chmod");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "chmod");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("chmod", end);
       } else {
               rval = fn(path, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
chown (const char *path, uid_t owner, gid_t group)
{
       struct timespec start, end;
       static int  (*fn)(const char *, uid_t , gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "chown");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "chown");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, owner, group);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("chown", end);
       } else {
               rval = fn(path, owner, group);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
closedir (DIR *dirp)
{
       struct timespec start, end;
       static int  (*fn)(DIR *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "closedir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "closedir");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("closedir", end);
       } else {
               rval = fn(dirp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
close (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "close");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "close");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("close", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
creat (const char *pathname, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "creat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "creat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("creat", end);
       } else {
               rval = fn(pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
dirfd (DIR *dirp)
{
       struct timespec start, end;
       static int  (*fn)(DIR *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "dirfd");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "dirfd");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("dirfd", end);
       } else {
               rval = fn(dirp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
dup (int oldfd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "dup");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "dup");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(oldfd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("dup", end);
       } else {
               rval = fn(oldfd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
faccessat (int dirfd, const char *pathname, int mode, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "faccessat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "faccessat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, mode, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("faccessat", end);
       } else {
               rval = fn(dirfd, pathname, mode, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fchdir (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fchdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fchdir");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fchdir", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fchmodat (int dirfd, const char *pathname, mode_t mode, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, mode_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fchmodat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fchmodat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, mode, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fchmodat", end);
       } else {
               rval = fn(dirfd, pathname, mode, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fchmod (int fd, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(int , mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fchmod");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fchmod");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fchmod", end);
       } else {
               rval = fn(fd, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fchownat (int dirfd, const char *pathname, uid_t owner, gid_t group, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, uid_t , gid_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fchownat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fchownat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, owner, group, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fchownat", end);
       } else {
               rval = fn(dirfd, pathname, owner, group, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fchown (int fd, uid_t owner, gid_t group)
{
       struct timespec start, end;
       static int  (*fn)(int , uid_t , gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fchown");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fchown");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, owner, group);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fchown", end);
       } else {
               rval = fn(fd, owner, group);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fclose (FILE *fp)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fclose");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fclose");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fclose", end);
       } else {
               rval = fn(fp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fdatasync (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fdatasync");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fdatasync");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fdatasync", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
feof (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feof");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feof");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feof", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
feof_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feof_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feof_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feof_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fflush (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fflush");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fflush");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fflush", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fflush_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fflush_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fflush_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fflush_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ffs (int i)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ffs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ffs");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(i);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ffs", end);
       } else {
               rval = fn(i);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ffsll (long long int i)
{
       struct timespec start, end;
       static int  (*fn)(long long int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ffsll");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ffsll");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(i);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ffsll", end);
       } else {
               rval = fn(i);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ffsl (long int i)
{
       struct timespec start, end;
       static int  (*fn)(long int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ffsl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ffsl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(i);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ffsl", end);
       } else {
               rval = fn(i);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fgetc (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetc");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetc", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fgetc_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetc_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetc_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fgetpos (FILE *stream, fpos_t *pos)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, fpos_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetpos");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetpos");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, pos);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetpos", end);
       } else {
               rval = fn(stream, pos);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fileno (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fileno");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fileno");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fileno", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fileno_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fileno_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fileno_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fileno_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputc (int c, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputc");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputc", end);
       } else {
               rval = fn(c, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputc_unlocked (int c, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputc_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputc_unlocked", end);
       } else {
               rval = fn(c, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputs (const char *s, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(const char *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputs");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputs", end);
       } else {
               rval = fn(s, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputs_unlocked (const char *s, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(const char *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputs_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputs_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputs_unlocked", end);
       } else {
               rval = fn(s, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputws (const wchar_t *ws, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(const wchar_t *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputws");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputws");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ws, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputws", end);
       } else {
               rval = fn(ws, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fputws_unlocked (const wchar_t *ws, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(const wchar_t *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputws_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputws_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ws, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputws_unlocked", end);
       } else {
               rval = fn(ws, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fseek (FILE *stream, long offset, int whence)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, long , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fseek");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fseek");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, offset, whence);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fseek", end);
       } else {
               rval = fn(stream, offset, whence);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fseeko (FILE *stream, off_t offset, int whence)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, off_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fseeko");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fseeko");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, offset, whence);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fseeko", end);
       } else {
               rval = fn(stream, offset, whence);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fstatat (int dirfd, const char *pathname, struct stat *buf, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, struct stat *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fstatat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fstatat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, buf, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fstatat", end);
       } else {
               rval = fn(dirfd, pathname, buf, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fstatvfs (int fd, struct statvfs *buf)
{
       struct timespec start, end;
       static int  (*fn)(int , struct statvfs *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fstatvfs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fstatvfs");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fstatvfs", end);
       } else {
               rval = fn(fd, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fsync (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fsync");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fsync");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fsync", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ftruncate (int fd, off_t length)
{
       struct timespec start, end;
       static int  (*fn)(int , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ftruncate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ftruncate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, length);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ftruncate", end);
       } else {
               rval = fn(fd, length);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ftrylockfile (FILE *filehandle)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ftrylockfile");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ftrylockfile");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(filehandle);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ftrylockfile", end);
       } else {
               rval = fn(filehandle);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
futimens (int fd, const struct timespec times[2])
{
       struct timespec start, end;
       static int  (*fn)(int , const struct timespec times[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "futimens");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "futimens");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, times);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("futimens", end);
       } else {
               rval = fn(fd, times);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fwide (FILE *stream, int mode)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fwide");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fwide");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fwide", end);
       } else {
               rval = fn(stream, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getc (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getc");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getc", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getchar_unlocked (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getchar_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getchar_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getchar_unlocked", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
getchar (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getchar");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getchar");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getchar", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
getc_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getc_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getc_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
klogctl (int type, char *bufp, int len)
{
       struct timespec start, end;
       static int  (*fn)(int , char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "klogctl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "klogctl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(type, bufp, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("klogctl", end);
       } else {
               rval = fn(type, bufp, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
lchown (const char *path, uid_t owner, gid_t group)
{
       struct timespec start, end;
       static int  (*fn)(const char *, uid_t , gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "lchown");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "lchown");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, owner, group);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("lchown", end);
       } else {
               rval = fn(path, owner, group);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
linkat (int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, int , const char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "linkat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "linkat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(olddirfd, oldpath, newdirfd, newpath, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("linkat", end);
       } else {
               rval = fn(olddirfd, oldpath, newdirfd, newpath, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
link (const char *oldpath, const char *newpath)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "link");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "link");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(oldpath, newpath);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("link", end);
       } else {
               rval = fn(oldpath, newpath);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
lio_listio (int mode, struct aiocb *const aiocb_list[], int nitems, struct sigevent *sevp)
{
       struct timespec start, end;
       static int  (*fn)(int , struct aiocb *const , int , struct sigevent *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "lio_listio");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "lio_listio");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mode, aiocb_list, nitems, sevp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("lio_listio", end);
       } else {
               rval = fn(mode, aiocb_list, nitems, sevp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
lockf (int fd, int cmd, off_t len)
{
       struct timespec start, end;
       static int  (*fn)(int , int , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "lockf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "lockf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, cmd, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("lockf", end);
       } else {
               rval = fn(fd, cmd, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
lstat (const char *path, struct stat *buf)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct stat *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "lstat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "lstat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("lstat", end);
       } else {
               rval = fn(path, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mkdirat (int dirfd, const char *pathname, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkdirat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkdirat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkdirat", end);
       } else {
               rval = fn(dirfd, pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mkfifoat (int dirfd, const char *pathname, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkfifoat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkfifoat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkfifoat", end);
       } else {
               rval = fn(dirfd, pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mkfifo (const char *pathname, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkfifo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkfifo");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkfifo", end);
       } else {
               rval = fn(pathname, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mknodat (int dirfd, const char *pathname, mode_t mode, dev_t dev)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, mode_t , dev_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mknodat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mknodat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, mode, dev);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mknodat", end);
       } else {
               rval = fn(dirfd, pathname, mode, dev);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mknod (const char *pathname, mode_t mode, dev_t dev)
{
       struct timespec start, end;
       static int  (*fn)(const char *, mode_t , dev_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mknod");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mknod");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname, mode, dev);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mknod", end);
       } else {
               rval = fn(pathname, mode, dev);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mkostemps (char *template, int suffixlen, int flags)
{
       struct timespec start, end;
       static int  (*fn)(char *, int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mkostemps");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mkostemps");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(template, suffixlen, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mkostemps", end);
       } else {
               rval = fn(template, suffixlen, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pclose (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pclose");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pclose");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pclose", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
       struct timespec start, end;
       static int  (*fn)(struct pollfd *, nfds_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "poll");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "poll");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fds, nfds, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("poll", end);
       } else {
               rval = fn(fds, nfds, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
posix_fadvise (int fd, off_t offset, off_t len, int advice)
{
       struct timespec start, end;
       static int  (*fn)(int , off_t , off_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "posix_fadvise");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "posix_fadvise");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, offset, len, advice);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("posix_fadvise", end);
       } else {
               rval = fn(fd, offset, len, advice);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
posix_fallocate (int fd, off_t offset, off_t len)
{
       struct timespec start, end;
       static int  (*fn)(int , off_t , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "posix_fallocate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "posix_fallocate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, offset, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("posix_fallocate", end);
       } else {
               rval = fn(fd, offset, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
putchar (int c)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putchar");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putchar");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putchar", end);
       } else {
               rval = fn(c);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
putchar_unlocked (int c)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putchar_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putchar_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putchar_unlocked", end);
       } else {
               rval = fn(c);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
putc (int c, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putc");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putc", end);
       } else {
               rval = fn(c, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
putc_unlocked (int c, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putc_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putc_unlocked", end);
       } else {
               rval = fn(c, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
puts (const char *s)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "puts");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "puts");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("puts", end);
       } else {
               rval = fn(s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
readdir_r (DIR *dirp, struct dirent *entry, struct dirent **result)
{
       struct timespec start, end;
       static int  (*fn)(DIR *, struct dirent *, struct dirent **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "readdir_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "readdir_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirp, entry, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("readdir_r", end);
       } else {
               rval = fn(dirp, entry, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
remove (const char *pathname)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "remove");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "remove");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("remove", end);
       } else {
               rval = fn(pathname);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
renameat (int olddirfd, const char *oldpath, int newdirfd, const char *newpath)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "renameat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "renameat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(olddirfd, oldpath, newdirfd, newpath);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("renameat", end);
       } else {
               rval = fn(olddirfd, oldpath, newdirfd, newpath);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
rename (const char *oldpath, const char *newpath)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "rename");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "rename");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(oldpath, newpath);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("rename", end);
       } else {
               rval = fn(oldpath, newpath);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
rmdir (const char *pathname)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "rmdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "rmdir");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("rmdir", end);
       } else {
               rval = fn(pathname);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setvbuf (FILE *stream, char *buf, int mode, size_t size)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, char *, int , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setvbuf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setvbuf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, buf, mode, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setvbuf", end);
       } else {
               rval = fn(stream, buf, mode, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
stat (const char *path, struct stat *buf)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct stat *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "stat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "stat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("stat", end);
       } else {
               rval = fn(path, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
statvfs (const char *path, struct statvfs *buf)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct statvfs *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "statvfs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "statvfs");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("statvfs", end);
       } else {
               rval = fn(path, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
symlinkat (const char *oldpath, int newdirfd, const char *newpath)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "symlinkat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "symlinkat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(oldpath, newdirfd, newpath);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("symlinkat", end);
       } else {
               rval = fn(oldpath, newdirfd, newpath);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
symlink (const char *oldpath, const char *newpath)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "symlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "symlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(oldpath, newpath);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("symlink", end);
       } else {
               rval = fn(oldpath, newpath);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
syslog (int type, char *bufp, int len)
{
       struct timespec start, end;
       static int  (*fn)(int , char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "syslog");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "syslog");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(type, bufp, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("syslog", end);
       } else {
               rval = fn(type, bufp, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
truncate (const char *path, off_t length)
{
       struct timespec start, end;
       static int  (*fn)(const char *, off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "truncate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "truncate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, length);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("truncate", end);
       } else {
               rval = fn(path, length);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ungetc (int c, FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ungetc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ungetc");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(c, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ungetc", end);
       } else {
               rval = fn(c, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
unlinkat (int dirfd, const char *pathname, int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "unlinkat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "unlinkat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("unlinkat", end);
       } else {
               rval = fn(dirfd, pathname, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
unlink (const char *pathname)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pathname);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("unlink", end);
       } else {
               rval = fn(pathname);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vdprintf (int fd, const char *format, va_list ap)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vdprintf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vdprintf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, format, ap);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vdprintf", end);
       } else {
               rval = fn(fd, format, ap);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vfprintf (FILE *stream, const char *format, va_list ap)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, const char *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vfprintf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vfprintf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, format, ap);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vfprintf", end);
       } else {
               rval = fn(stream, format, ap);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vfscanf (FILE *stream, const char *format, va_list ap)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, const char *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vfscanf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vfscanf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, format, ap);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vfscanf", end);
       } else {
               rval = fn(stream, format, ap);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vfwprintf (FILE *stream, const wchar_t *format, va_list args)
{
       struct timespec start, end;
       static int  (*fn)(FILE *, const wchar_t *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vfwprintf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vfwprintf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream, format, args);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vfwprintf", end);
       } else {
               rval = fn(stream, format, args);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vprintf (const char *format, va_list ap)
{
       struct timespec start, end;
       static int  (*fn)(const char *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vprintf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vprintf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(format, ap);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vprintf", end);
       } else {
               rval = fn(format, ap);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vscanf (const char *format, va_list ap)
{
       struct timespec start, end;
       static int  (*fn)(const char *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vscanf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vscanf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(format, ap);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vscanf", end);
       } else {
               rval = fn(format, ap);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
vwprintf (const wchar_t *format, va_list args)
{
       struct timespec start, end;
       static int  (*fn)(const wchar_t *, va_list );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "vwprintf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "vwprintf");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(format, args);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("vwprintf", end);
       } else {
               rval = fn(format, args);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

long 
fpathconf (int fd, int name)
{
       struct timespec start, end;
       static long  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fpathconf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fpathconf");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fpathconf", end);
       } else {
               rval = fn(fd, name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

long 
ftell (FILE *stream)
{
       struct timespec start, end;
       static long  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ftell");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ftell");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ftell", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

long 
telldir (DIR *dirp)
{
       struct timespec start, end;
       static long  (*fn)(DIR *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "telldir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "telldir");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("telldir", end);
       } else {
               rval = fn(dirp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

nl_catd 
catopen (const char *name, int flag)
{
       struct timespec start, end;
       static nl_catd  (*fn)(const char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "catopen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "catopen");
            goto out;
       }
       nl_catd  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, flag);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("catopen", end);
       } else {
               rval = fn(name, flag);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

off_t 
ftello (FILE *stream)
{
       struct timespec start, end;
       static off_t  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ftello");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ftello");
            goto out;
       }
       off_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ftello", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

off_t 
lseek (int fd, off_t offset, int whence)
{
       struct timespec start, end;
       static off_t  (*fn)(int , off_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "lseek");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "lseek");
            goto out;
       }
       off_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, offset, whence);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("lseek", end);
       } else {
               rval = fn(fd, offset, whence);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

pid_t 
tcgetpgrp (int fd)
{
       struct timespec start, end;
       static pid_t  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcgetpgrp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcgetpgrp");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcgetpgrp", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}
size_t 
fread_unlocked (void *ptr, size_t size, size_t n, FILE *stream)
{
       struct timespec start, end;
       static size_t  (*fn)(void *, size_t , size_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fread_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fread_unlocked");
            goto out;
       }
       size_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, size, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fread_unlocked", end);
       } else {
               rval = fn(ptr, size, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

size_t 
fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
       struct timespec start, end;
       static size_t  (*fn)(void *, size_t , size_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fread");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fread");
            goto out;
       }
       size_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, size, nmemb, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fread", end);
       } else {
               rval = fn(ptr, size, nmemb, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

size_t 
fwrite_unlocked (const void *ptr, size_t size, size_t n, FILE *stream)
{
       struct timespec start, end;
       static size_t  (*fn)(const void *, size_t , size_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fwrite_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fwrite_unlocked");
            goto out;
       }
       size_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, size, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fwrite_unlocked", end);
       } else {
               rval = fn(ptr, size, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

size_t 
fwrite (const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
       struct timespec start, end;
       static size_t  (*fn)(const void *, size_t , size_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fwrite");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fwrite");
            goto out;
       }
       size_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, size, nmemb, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fwrite", end);
       } else {
               rval = fn(ptr, size, nmemb, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
aio_return (struct aiocb *aiocbp)
{
       struct timespec start, end;
       static ssize_t  (*fn)(struct aiocb *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aio_return");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aio_return");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(aiocbp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aio_return", end);
       } else {
               rval = fn(aiocbp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
getdelim (char **lineptr, size_t *n, int delim, FILE *stream)
{
       struct timespec start, end;
       static ssize_t  (*fn)(char **, size_t *, int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getdelim");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getdelim");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(lineptr, n, delim, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getdelim", end);
       } else {
               rval = fn(lineptr, n, delim, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
getline (char **lineptr, size_t *n, FILE *stream)
{
       struct timespec start, end;
       static ssize_t  (*fn)(char **, size_t *, FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getline");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getline");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(lineptr, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getline", end);
       } else {
               rval = fn(lineptr, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
pread (int fd, void *buf, size_t count, off_t offset)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pread");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pread");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, buf, count, offset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pread", end);
       } else {
               rval = fn(fd, buf, count, offset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
pwrite (int fd, const void *buf, size_t count, off_t offset)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const void *, size_t , off_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pwrite");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pwrite");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, buf, count, offset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pwrite", end);
       } else {
               rval = fn(fd, buf, count, offset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
readlink (const char *path, char *buf, size_t bufsiz)
{
       struct timespec start, end;
       static ssize_t  (*fn)(const char *, char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "readlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "readlink");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(path, buf, bufsiz);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("readlink", end);
       } else {
               rval = fn(path, buf, bufsiz);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
readv (int fd, const struct iovec *iov, int iovcnt)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const struct iovec *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "readv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "readv");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, iov, iovcnt);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("readv", end);
       } else {
               rval = fn(fd, iov, iovcnt);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
writev (int fd, const struct iovec *iov, int iovcnt)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const struct iovec *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "writev");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "writev");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, iov, iovcnt);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("writev", end);
       } else {
               rval = fn(fd, iov, iovcnt);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct dirent *
readdir (DIR *dirp)
{
       struct timespec start, end;
       static struct dirent * (*fn)(DIR *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "readdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "readdir");
            goto out;
       }
       struct dirent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("readdir", end);
       } else {
               rval = fn(dirp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct utmp *
pututline (struct utmp *ut)
{
       struct timespec start, end;
       static struct utmp * (*fn)(struct utmp *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pututline");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pututline");
            goto out;
       }
       struct utmp * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ut);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pututline", end);
       } else {
               rval = fn(ut);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void *
aligned_alloc (size_t alignment, size_t size)
{
       struct timespec start, end;
       static void * (*fn)(size_t , size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "aligned_alloc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "aligned_alloc");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(alignment, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("aligned_alloc", end);
       } else {
               rval = fn(alignment, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
clearerr (FILE *stream)
{
       struct timespec start, end;
       static void  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clearerr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clearerr");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clearerr", end);
       } else {
               fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
clearerr_unlocked (FILE *stream)
{
       struct timespec start, end;
       static void  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clearerr_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clearerr_unlocked");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clearerr_unlocked", end);
       } else {
               fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
closelog (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "closelog");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "closelog");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("closelog", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
flockfile (FILE *filehandle)
{
       struct timespec start, end;
       static void  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "flockfile");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "flockfile");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(filehandle);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("flockfile", end);
       } else {
               fn(filehandle);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
funlockfile (FILE *filehandle)
{
       struct timespec start, end;
       static void  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "funlockfile");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "funlockfile");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(filehandle);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("funlockfile", end);
       } else {
               fn(filehandle);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
openlog (const char *ident, int option, int facility)
{
       struct timespec start, end;
       static void  (*fn)(const char *, int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "openlog");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "openlog");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(ident, option, facility);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("openlog", end);
       } else {
               fn(ident, option, facility);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
perror (const char *s)
{
       struct timespec start, end;
       static void  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "perror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "perror");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("perror", end);
       } else {
               fn(s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
rewinddir (DIR *dirp)
{
       struct timespec start, end;
       static void  (*fn)(DIR *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "rewinddir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "rewinddir");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(dirp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("rewinddir", end);
       } else {
               fn(dirp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
rewind (FILE *stream)
{
       struct timespec start, end;
       static void  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "rewind");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "rewind");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("rewind", end);
       } else {
               fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
seekdir (DIR *dirp, long offset)
{
       struct timespec start, end;
       static void  (*fn)(DIR *, long );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "seekdir");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "seekdir");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(dirp, offset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("seekdir", end);
       } else {
               fn(dirp, offset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setbuffer (FILE *stream, char *buf, size_t size)
{
       struct timespec start, end;
       static void  (*fn)(FILE *, char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setbuffer");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setbuffer");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stream, buf, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setbuffer", end);
       } else {
               fn(stream, buf, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setbuf (FILE *stream, char *buf)
{
       struct timespec start, end;
       static void  (*fn)(FILE *, char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setbuf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setbuf");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stream, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setbuf", end);
       } else {
               fn(stream, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}


void 
sync (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sync");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sync");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sync", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

wchar_t *
fgetws_unlocked (wchar_t *ws, int n, FILE *stream)
{
       struct timespec start, end;
       static wchar_t * (*fn)(wchar_t *, int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetws_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetws_unlocked");
            goto out;
       }
       wchar_t * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ws, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetws_unlocked", end);
       } else {
               rval = fn(ws, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wchar_t *
fgetws (wchar_t *ws, int n, FILE *stream)
{
       struct timespec start, end;
       static wchar_t * (*fn)(wchar_t *, int , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetws");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetws");
            goto out;
       }
       wchar_t * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ws, n, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetws", end);
       } else {
               rval = fn(ws, n, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
fgetwc (FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetwc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetwc");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetwc", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
fgetwc_unlocked (FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fgetwc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fgetwc_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fgetwc_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
fputwc_unlocked (wchar_t wc, FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputwc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputwc_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputwc_unlocked", end);
       } else {
               rval = fn(wc, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
fputwc (wchar_t wc, FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fputwc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fputwc");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fputwc", end);
       } else {
               rval = fn(wc, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
getwc (FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getwc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getwc");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getwc", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
getwchar_unlocked (void)
{
       struct timespec start, end;
       static wint_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getwchar_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getwchar_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getwchar_unlocked", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

wint_t 
getwchar (void)
{
       struct timespec start, end;
       static wint_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getwchar");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getwchar");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getwchar", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

wint_t 
getwc_unlocked (FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getwc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getwc_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getwc_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
putwchar_unlocked (wchar_t wc)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putwchar_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putwchar_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putwchar_unlocked", end);
       } else {
               rval = fn(wc);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
putwchar (wchar_t wc)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putwchar");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putwchar");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putwchar", end);
       } else {
               rval = fn(wc);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
putwc_unlocked (wchar_t wc, FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putwc_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putwc_unlocked");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putwc_unlocked", end);
       } else {
               rval = fn(wc, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
putwc (wchar_t wc, FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(wchar_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putwc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putwc");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putwc", end);
       } else {
               rval = fn(wc, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

wint_t 
ungetwc (wint_t wc, FILE *stream)
{
       struct timespec start, end;
       static wint_t  (*fn)(wint_t , FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ungetwc");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ungetwc");
            goto out;
       }
       wint_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(wc, stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ungetwc", end);
       } else {
               rval = fn(wc, stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}
/*
 * End of FS
 */
