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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(req, rem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("nanosleep", end);
       } else {
               rval = fn(req, rem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
asctime (const struct tm *tm)
{
       struct timespec start, end;
       static char * (*fn)(const struct tm *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "asctime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "asctime");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(tm);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("asctime", end);
       } else {
               rval = fn(tm);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
asctime_r (const struct tm *tm, char *buf)
{
       struct timespec start, end;
       static char * (*fn)(const struct tm *, char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "asctime_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "asctime_r");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(tm, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("asctime_r", end);
       } else {
               rval = fn(tm, buf);
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
crypt (const char *key, const char *salt)
{
       struct timespec start, end;
       static char * (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "crypt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "crypt");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, salt);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("crypt", end);
       } else {
               rval = fn(key, salt);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
crypt_r (const char *key, const char *salt, struct crypt_data *data)
{
       struct timespec start, end;
       static char * (*fn)(const char *, const char *, struct crypt_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "crypt_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "crypt_r");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, salt, data);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("crypt_r", end);
       } else {
               rval = fn(key, salt, data);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
ctime (const time_t *timep)
{
       struct timespec start, end;
       static char * (*fn)(const time_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ctime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ctime");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ctime", end);
       } else {
               rval = fn(timep);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
ctime_r (const time_t *timep, char *buf)
{
       struct timespec start, end;
       static char * (*fn)(const time_t *, char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ctime_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ctime_r");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ctime_r", end);
       } else {
               rval = fn(timep, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
cuserid (char *string)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cuserid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cuserid");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(string);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cuserid", end);
       } else {
               rval = fn(string);
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
getenv (const char *name)
{
       struct timespec start, end;
       static char * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getenv");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getenv", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
getlogin (void)
{
       struct timespec start, end;
       static char * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getlogin");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getlogin");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getlogin", end);
       } else {
               rval = fn();
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
inet_ntoa (struct in_addr in)
{
       struct timespec start, end;
       static char * (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_ntoa");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_ntoa");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_ntoa", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
initstate (unsigned int seed, char *state, size_t n)
{
       struct timespec start, end;
       static char * (*fn)(unsigned int , char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "initstate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "initstate");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(seed, state, n);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("initstate", end);
       } else {
               rval = fn(seed, state, n);
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

char *
nl_langinfo (nl_item item)
{
       struct timespec start, end;
       static char * (*fn)(nl_item );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "nl_langinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "nl_langinfo");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(item);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("nl_langinfo", end);
       } else {
               rval = fn(item);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
ptsname (int fd)
{
       struct timespec start, end;
       static char * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ptsname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ptsname");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ptsname", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
secure_getenv (const char *name)
{
       struct timespec start, end;
       static char * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "secure_getenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "secure_getenv");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("secure_getenv", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
setlocale (int category, const char *locale)
{
       struct timespec start, end;
       static char * (*fn)(int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setlocale");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setlocale");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(category, locale);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setlocale", end);
       } else {
               rval = fn(category, locale);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
setstate (char *state)
{
       struct timespec start, end;
       static char * (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setstate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setstate");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(state);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setstate", end);
       } else {
               rval = fn(state);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

char *
ttyname (int fd)
{
       struct timespec start, end;
       static char * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ttyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ttyname");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ttyname", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

clock_t 
clock (void)
{
       struct timespec start, end;
       static clock_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clock");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clock");
            goto out;
       }
       clock_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clock", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

clock_t 
times (struct tms *buf)
{
       struct timespec start, end;
       static clock_t  (*fn)(struct tms *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "times");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "times");
            goto out;
       }
       clock_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("times", end);
       } else {
               rval = fn(buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

const char *
gai_strerror (int errcode)
{
       struct timespec start, end;
       static const char * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gai_strerror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gai_strerror");
            goto out;
       }
       const char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(errcode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gai_strerror", end);
       } else {
               rval = fn(errcode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

const char *
hstrerror (int err)
{
       struct timespec start, end;
       static const char * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hstrerror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hstrerror");
            goto out;
       }
       const char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(err);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hstrerror", end);
       } else {
               rval = fn(err);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

const char *
inet_ntop (int af, const void *src, char *dst, socklen_t size)
{
       struct timespec start, end;
       static const char * (*fn)(int , const void *, char *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_ntop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_ntop");
            goto out;
       }
       const char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(af, src, dst, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_ntop", end);
       } else {
               rval = fn(af, src, dst, size);
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

double
difftime (time_t time1, time_t time0)
{
       struct timespec start, end;
       static double  (*fn)(time_t , time_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "difftime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "difftime");
            goto out;
       }
       double  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(time1, time0);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("difftime", end);
       } else {
               rval = fn(time1, time0);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ENTRY *
hsearch (ENTRY item, ACTION action)
{
       struct timespec start, end;
       static ENTRY * (*fn)(ENTRY , ACTION );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hsearch");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hsearch");
            goto out;
       }
       ENTRY * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(item, action);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hsearch", end);
       } else {
               rval = fn(item, action);
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
open_memstream (char **ptr, size_t *sizeloc)
{
       struct timespec start, end;
       static FILE * (*fn)(char **, size_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "open_memstream");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "open_memstream");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, sizeloc);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("open_memstream", end);
       } else {
               rval = fn(ptr, sizeloc);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

FILE *
open_wmemstream (wchar_t **ptr, size_t *sizeloc)
{
       struct timespec start, end;
       static FILE * (*fn)(wchar_t **, size_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "open_wmemstream");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "open_wmemstream");
            goto out;
       }
       FILE * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ptr, sizeloc);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("open_wmemstream", end);
       } else {
               rval = fn(ptr, sizeloc);
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

gid_t 
getegid (void)
{
       struct timespec start, end;
       static gid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getegid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getegid");
            goto out;
       }
       gid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getegid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

gid_t 
getgid (void)
{
       struct timespec start, end;
       static gid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgid");
            goto out;
       }
       gid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

in_addr_t 
inet_addr (const char *cp)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_addr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_addr");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_addr", end);
       } else {
               rval = fn(cp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_lnaof (struct in_addr in)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_lnaof");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_lnaof");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_lnaof", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_netof (struct in_addr in)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_netof");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_netof");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_netof", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_network (const char *cp)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_network");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_network");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_network", end);
       } else {
               rval = fn(cp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "accept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "accept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("accept", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
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
bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "bind");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "bind");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("bind", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
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
cfsetispeed (struct termios *termios_p, speed_t speed)
{
       struct timespec start, end;
       static int  (*fn)(struct termios *, speed_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfsetispeed");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfsetispeed");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(termios_p, speed);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfsetispeed", end);
       } else {
               rval = fn(termios_p, speed);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
cfsetospeed (struct termios *termios_p, speed_t speed)
{
       struct timespec start, end;
       static int  (*fn)(struct termios *, speed_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfsetospeed");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfsetospeed");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(termios_p, speed);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfsetospeed", end);
       } else {
               rval = fn(termios_p, speed);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
cfsetspeed (struct termios *termios_p, speed_t speed)
{
       struct timespec start, end;
       static int  (*fn)(struct termios *, speed_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfsetspeed");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfsetspeed");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(termios_p, speed);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfsetspeed", end);
       } else {
               rval = fn(termios_p, speed);
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
clock_getcpuclockid (pid_t pid, clockid_t *clock_id)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , clockid_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clock_getcpuclockid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clock_getcpuclockid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, clock_id);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clock_getcpuclockid", end);
       } else {
               rval = fn(pid, clock_id);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int
clock_getres (clockid_t clk_id, struct timespec *res)
{
       struct timespec start, end;
       static int  (*fn)(clockid_t , struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clock_getres");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clock_getres");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(clk_id, res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clock_getres", end);
       } else {
               rval = fn(clk_id, res);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(clock_id, flags, request, remain);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clock_nanosleep", end);
       } else {
               rval = fn(clock_id, flags, request, remain);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
clock_settime (clockid_t clk_id, const struct timespec *tp)
{
       struct timespec start, end;
       static int  (*fn)(clockid_t , const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "clock_settime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "clock_settime");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(clk_id, tp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("clock_settime", end);
       } else {
               rval = fn(clk_id, tp);
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
connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "connect");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "connect");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("connect", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
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
feclearexcept (int excepts)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feclearexcept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feclearexcept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(excepts);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feclearexcept", end);
       } else {
               rval = fn(excepts);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fegetenv (fenv_t *envp)
{
       struct timespec start, end;
       static int  (*fn)(fenv_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fegetenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fegetenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(envp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fegetenv", end);
       } else {
               rval = fn(envp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fegetexceptflag (fexcept_t *flagp, int excepts)
{
       struct timespec start, end;
       static int  (*fn)(fexcept_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fegetexceptflag");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fegetexceptflag");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(flagp, excepts);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fegetexceptflag", end);
       } else {
               rval = fn(flagp, excepts);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fegetround (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fegetround");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fegetround");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fegetround", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
feholdexcept (fenv_t *envp)
{
       struct timespec start, end;
       static int  (*fn)(fenv_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feholdexcept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feholdexcept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(envp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feholdexcept", end);
       } else {
               rval = fn(envp);
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
feraiseexcept (int excepts)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feraiseexcept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feraiseexcept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(excepts);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feraiseexcept", end);
       } else {
               rval = fn(excepts);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ferror (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ferror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ferror");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ferror", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ferror_unlocked (FILE *stream)
{
       struct timespec start, end;
       static int  (*fn)(FILE *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ferror_unlocked");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ferror_unlocked");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(stream);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ferror_unlocked", end);
       } else {
               rval = fn(stream);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fesetenv (const fenv_t *envp)
{
       struct timespec start, end;
       static int  (*fn)(const fenv_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fesetenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fesetenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(envp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fesetenv", end);
       } else {
               rval = fn(envp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fesetexceptflag (const fexcept_t *flagp, int excepts)
{
       struct timespec start, end;
       static int  (*fn)(const fexcept_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fesetexceptflag");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fesetexceptflag");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(flagp, excepts);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fesetexceptflag", end);
       } else {
               rval = fn(flagp, excepts);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fesetround (int rounding_mode)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fesetround");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fesetround");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(rounding_mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fesetround", end);
       } else {
               rval = fn(rounding_mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fetestexcept (int excepts)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fetestexcept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fetestexcept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(excepts);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fetestexcept", end);
       } else {
               rval = fn(excepts);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
feupdateenv (const fenv_t *envp)
{
       struct timespec start, end;
       static int  (*fn)(const fenv_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "feupdateenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "feupdateenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(envp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("feupdateenv", end);
       } else {
               rval = fn(envp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
fexecve (int fd, char *const argv[], char *const envp[])
{
       struct timespec start, end;
       static int  (*fn)(int , char *const , char *const );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fexecve");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fexecve");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, argv, envp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fexecve", end);
       } else {
               rval = fn(fd, argv, envp);
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
fmtmsg (long classification, const char *label, int severity, const char *text, const char *action, const char *tag)
{
       struct timespec start, end;
       static int  (*fn)(long , const char *, int , const char *, const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "fmtmsg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "fmtmsg");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(classification, label, severity, text, action, tag);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("fmtmsg", end);
       } else {
               rval = fn(classification, label, severity, text, action, tag);
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
getaddrinfo (const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *, const struct addrinfo *, struct addrinfo **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getaddrinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getaddrinfo");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(node, service, hints, res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getaddrinfo", end);
       } else {
               rval = fn(node, service, hints, res);
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
getdate_r (const char *string, struct tm *res)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct tm *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getdate_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getdate_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(string, res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getdate_r", end);
       } else {
               rval = fn(string, res);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getgrgid_r (gid_t gid, struct group *grp, char *buf, size_t buflen, struct group **result)
{
       struct timespec start, end;
       static int  (*fn)(gid_t , struct group *, char *, size_t , struct group **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgrgid_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgrgid_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(gid, grp, buf, buflen, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgrgid_r", end);
       } else {
               rval = fn(gid, grp, buf, buflen, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getgrnam_r (const char *name, struct group *grp, char *buf, size_t buflen, struct group **result)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct group *, char *, size_t , struct group **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgrnam_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgrnam_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, grp, buf, buflen, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgrnam_r", end);
       } else {
               rval = fn(name, grp, buf, buflen, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getgroups (int size, gid_t list[])
{
       struct timespec start, end;
       static int  (*fn)(int , gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgroups");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgroups");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(size, list);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgroups", end);
       } else {
               rval = fn(size, list);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyaddr_r (const void *addr, socklen_t len, int type, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const void *, socklen_t , int , struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyaddr_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyaddr_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len, type, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyaddr_r", end);
       } else {
               rval = fn(addr, len, type, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyname2_r (const char *name, int af, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int , struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname2_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname2_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, af, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname2_r", end);
       } else {
               rval = fn(name, af, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyname_r (const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname_r", end);
       } else {
               rval = fn(name, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostent_r (struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostent_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostent_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostent_r", end);
       } else {
               rval = fn(ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostname (char *name, size_t len)
{
       struct timespec start, end;
       static int  (*fn)(char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostname");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostname", end);
       } else {
               rval = fn(name, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getitimer (int which, struct itimerval *curr_value)
{
       struct timespec start, end;
       static int  (*fn)(int , struct itimerval *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getitimer");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getitimer");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(which, curr_value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getitimer", end);
       } else {
               rval = fn(which, curr_value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getlogin_r (char *buf, size_t bufsize)
{
       struct timespec start, end;
       static int  (*fn)(char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getlogin_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getlogin_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf, bufsize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getlogin_r", end);
       } else {
               rval = fn(buf, bufsize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getnameinfo (const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
       struct timespec start, end;
       static int  (*fn)(const struct sockaddr *, socklen_t , char *, size_t , char *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnameinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnameinfo");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sa, salen, host, hostlen, serv, servlen, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnameinfo", end);
       } else {
               rval = fn(sa, salen, host, hostlen, serv, servlen, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getopt (int argc, char * const argv[], const char *optstring)
{
       struct timespec start, end;
       static int  (*fn)(int , char * const , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(argc, argv, optstring);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getopt", end);
       } else {
               rval = fn(argc, argv, optstring);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getopt_long_only (int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex)
{
       struct timespec start, end;
       static int  (*fn)(int , char * const , const char *, const struct option *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getopt_long_only");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getopt_long_only");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(argc, argv, optstring, longopts, longindex);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getopt_long_only", end);
       } else {
               rval = fn(argc, argv, optstring, longopts, longindex);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getpeername (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpeername");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpeername");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpeername", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getpwnam_r (const char *name, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct passwd *, char *, size_t , struct passwd **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpwnam_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpwnam_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, pwd, buf, buflen, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpwnam_r", end);
       } else {
               rval = fn(name, pwd, buf, buflen, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getpwuid_r (uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result)
{
       struct timespec start, end;
       static int  (*fn)(uid_t , struct passwd *, char *, size_t , struct passwd **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpwuid_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpwuid_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(uid, pwd, buf, buflen, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpwuid_r", end);
       } else {
               rval = fn(uid, pwd, buf, buflen, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getrusage (int who, struct rusage *usage)
{
       struct timespec start, end;
       static int  (*fn)(int , struct rusage *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getrusage");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getrusage");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(who, usage);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getrusage", end);
       } else {
               rval = fn(who, usage);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getsockname (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsockname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsockname");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsockname", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , void *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsockopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsockopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, level, optname, optval, optlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsockopt", end);
       } else {
               rval = fn(sockfd, level, optname, optval, optlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getsubopt (char **optionp, char * const *tokens, char **valuep)
{
       struct timespec start, end;
       static int  (*fn)(char **, char * const *, char **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsubopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsubopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(optionp, tokens, valuep);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsubopt", end);
       } else {
               rval = fn(optionp, tokens, valuep);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(tv, tz);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gettimeofday", end);
       } else {
               rval = fn(tv, tz);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
grantpt (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "grantpt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "grantpt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("grantpt", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
hcreate_r (size_t nel, struct hsearch_data *htab)
{
       struct timespec start, end;
       static int  (*fn)(size_t , struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hcreate_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hcreate_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nel, htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hcreate_r", end);
       } else {
               rval = fn(nel, htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
hcreate (size_t nel)
{
       struct timespec start, end;
       static int  (*fn)(size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hcreate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hcreate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nel);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hcreate", end);
       } else {
               rval = fn(nel);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
hsearch_r (ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab)
{
       struct timespec start, end;
       static int  (*fn)(ENTRY , ACTION , ENTRY **, struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hsearch_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hsearch_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(item, action, retval, htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hsearch_r", end);
       } else {
               rval = fn(item, action, retval, htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
inet_aton (const char *cp, struct in_addr *inp)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct in_addr *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_aton");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_aton");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp, inp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_aton", end);
       } else {
               rval = fn(cp, inp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
inet_pton (int af, const char *src, void *dst)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_pton");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_pton");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(af, src, dst);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_pton", end);
       } else {
               rval = fn(af, src, dst);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
killpg (int pgrp, int sig)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "killpg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "killpg");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pgrp, sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("killpg", end);
       } else {
               rval = fn(pgrp, sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
kill (pid_t pid, int sig)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "kill");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "kill");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("kill", end);
       } else {
               rval = fn(pid, sig);
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
listen (int sockfd, int backlog)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "listen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "listen");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, backlog);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("listen", end);
       } else {
               rval = fn(sockfd, backlog);
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
mq_close (mqd_t mqdes)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_close");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_close");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_close", end);
       } else {
               rval = fn(mqdes);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_getattr (mqd_t mqdes, struct mq_attr *attr)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , struct mq_attr *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_getattr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_getattr");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, attr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_getattr", end);
       } else {
               rval = fn(mqdes, attr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_notify (mqd_t mqdes, const struct sigevent *sevp)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const struct sigevent *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_notify");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_notify");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, sevp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_notify", end);
       } else {
               rval = fn(mqdes, sevp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_send (mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const char *, size_t , unsigned );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_send");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_send");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_send", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_timedsend (mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio,  const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const char *, size_t , unsigned ,  const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_timedsend");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_timedsend");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_timedsend", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
       struct timespec start, end;
       static int  (*fn)(int , int , struct msqid_ds *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgctl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgctl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, cmd, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgctl", end);
       } else {
               rval = fn(msqid, cmd, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgget (key_t key, int msgflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgget", end);
       } else {
               rval = fn(key, msgflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgsnd (int msqid, const void *msgp, size_t msgsz, int msgflg)
{
       struct timespec start, end;
       static int  (*fn)(int , const void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgsnd");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgsnd");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, msgp, msgsz, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgsnd", end);
       } else {
               rval = fn(msqid, msgp, msgsz, msgflg);
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

int 
nice (int inc)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "nice");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "nice");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(inc);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("nice", end);
       } else {
               rval = fn(inc);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pause", end);
       } else {
               rval = fn();
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
pipe (int pipefd[2])
{
       struct timespec start, end;
       static int  (*fn)(int pipefd[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pipe");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pipe");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pipefd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pipe", end);
       } else {
               rval = fn(pipefd);
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
posix_openpt (int flags)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "posix_openpt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "posix_openpt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("posix_openpt", end);
       } else {
               rval = fn(flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_destroy (pthread_attr_t *attr)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_destroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_destroy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_destroy", end);
       } else {
               rval = fn(attr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getdetachstate (pthread_attr_t *attr, int *detachstate)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getdetachstate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getdetachstate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, detachstate);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getdetachstate", end);
       } else {
               rval = fn(attr, detachstate);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getguardsize (pthread_attr_t *attr, size_t *guardsize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, size_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getguardsize");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getguardsize");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, guardsize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getguardsize", end);
       } else {
               rval = fn(attr, guardsize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getinheritsched (pthread_attr_t *attr, int inheritsched)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getinheritsched");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getinheritsched");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, inheritsched);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getinheritsched", end);
       } else {
               rval = fn(attr, inheritsched);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getschedparam (pthread_attr_t *attr, struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getschedparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getschedparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getschedparam", end);
       } else {
               rval = fn(attr, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getschedpolicy (pthread_attr_t *attr, int *policy)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getschedpolicy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getschedpolicy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, policy);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getschedpolicy", end);
       } else {
               rval = fn(attr, policy);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getscope (pthread_attr_t *attr, int *scope)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getscope");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getscope");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, scope);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getscope", end);
       } else {
               rval = fn(attr, scope);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getstack (pthread_attr_t *attr, void **stackaddr, size_t *stacksize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, void **, size_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getstack");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getstack");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, stackaddr, stacksize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getstack", end);
       } else {
               rval = fn(attr, stackaddr, stacksize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_getstacksize (pthread_attr_t *attr, size_t *stacksize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, size_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_getstacksize");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_getstacksize");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, stacksize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_getstacksize", end);
       } else {
               rval = fn(attr, stacksize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_init (pthread_attr_t *attr)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_init");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_init");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_init", end);
       } else {
               rval = fn(attr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setdetachstate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setdetachstate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, detachstate);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setdetachstate", end);
       } else {
               rval = fn(attr, detachstate);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setguardsize (pthread_attr_t *attr, size_t guardsize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setguardsize");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setguardsize");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, guardsize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setguardsize", end);
       } else {
               rval = fn(attr, guardsize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setinheritsched (pthread_attr_t *attr, int *inheritsched)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setinheritsched");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setinheritsched");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, inheritsched);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setinheritsched", end);
       } else {
               rval = fn(attr, inheritsched);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setschedparam (pthread_attr_t *attr, const struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, const struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setschedparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setschedparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setschedparam", end);
       } else {
               rval = fn(attr, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setschedpolicy (pthread_attr_t *attr, int policy)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setschedpolicy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setschedpolicy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, policy);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setschedpolicy", end);
       } else {
               rval = fn(attr, policy);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setscope (pthread_attr_t *attr, int scope)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setscope");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setscope");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, scope);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setscope", end);
       } else {
               rval = fn(attr, scope);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setstack (pthread_attr_t *attr, void *stackaddr, size_t stacksize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, void *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setstack");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setstack");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, stackaddr, stacksize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setstack", end);
       } else {
               rval = fn(attr, stackaddr, stacksize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_attr_setstacksize (pthread_attr_t *attr, size_t stacksize)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_attr_setstacksize");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_attr_setstacksize");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(attr, stacksize);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_attr_setstacksize", end);
       } else {
               rval = fn(attr, stacksize);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_cancel (pthread_t thread)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_cancel");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cancel");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_cancel", end);
       } else {
               rval = fn(thread);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_detach (pthread_t thread)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_detach");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_detach");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_detach", end);
       } else {
               rval = fn(thread);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_equal (pthread_t t1, pthread_t t2)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , pthread_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_equal");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_equal");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(t1, t2);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_equal", end);
       } else {
               rval = fn(t1, t2);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_getconcurrency (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_getconcurrency");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_getconcurrency");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_getconcurrency", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
pthread_getcpuclockid (pthread_t thread, clockid_t *clock_id)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , clockid_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_getcpuclockid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_getcpuclockid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, clock_id);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_getcpuclockid", end);
       } else {
               rval = fn(thread, clock_id);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_getschedparam (pthread_t thread, int *policy,  const struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , int *,  const struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_getschedparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_getschedparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, policy, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_getschedparam", end);
       } else {
               rval = fn(thread, policy, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_join (pthread_t thread, void **retval)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , void **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_join");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_join");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, retval);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_join", end);
       } else {
               rval = fn(thread, retval);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_kill (pthread_t thread, int sig)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_kill");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_kill");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_kill", end);
       } else {
               rval = fn(thread, sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_setcancelstate (int state, int *oldstate)
{
       struct timespec start, end;
       static int  (*fn)(int , int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_setcancelstate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_setcancelstate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(state, oldstate);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_setcancelstate", end);
       } else {
               rval = fn(state, oldstate);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_setcanceltype (int type, int *oldtype)
{
       struct timespec start, end;
       static int  (*fn)(int , int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_setcanceltype");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_setcanceltype");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(type, oldtype);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_setcanceltype", end);
       } else {
               rval = fn(type, oldtype);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_setconcurrency (int new_level)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_setconcurrency");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_setconcurrency");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(new_level);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_setconcurrency", end);
       } else {
               rval = fn(new_level);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_setschedparam (pthread_t thread, int policy, struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , int , struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_setschedparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_setschedparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, policy, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_setschedparam", end);
       } else {
               rval = fn(thread, policy, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_setschedprio (pthread_t thread, int prio)
{
       struct timespec start, end;
       static int  (*fn)(pthread_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_setschedprio");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_setschedprio");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(thread, prio);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_setschedprio", end);
       } else {
               rval = fn(thread, prio);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pthread_sigmask (int how, const sigset_t *set, sigset_t *oldset)
{
       struct timespec start, end;
       static int  (*fn)(int , const sigset_t *, sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_sigmask");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_sigmask");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(how, set, oldset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_sigmask", end);
       } else {
               rval = fn(how, set, oldset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
ptsname_r (int fd, char *buf, size_t buflen)
{
       struct timespec start, end;
       static int  (*fn)(int , char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ptsname_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ptsname_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, buf, buflen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ptsname_r", end);
       } else {
               rval = fn(fd, buf, buflen);
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
putenv (char *string)
{
       struct timespec start, end;
       static int  (*fn)(char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "putenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "putenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(string);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("putenv", end);
       } else {
               rval = fn(string);
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
raise (int sig)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "raise");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "raise");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("raise", end);
       } else {
               rval = fn(sig);
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
sched_getparam (pid_t pid, struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_getparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_getparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_getparam", end);
       } else {
               rval = fn(pid, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_get_priority_max (int policy)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_get_priority_max");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_get_priority_max");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(policy);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_get_priority_max", end);
       } else {
               rval = fn(policy);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_get_priority_min (int policy)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_get_priority_min");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_get_priority_min");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(policy);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_get_priority_min", end);
       } else {
               rval = fn(policy);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_getscheduler (pid_t pid)
{
       struct timespec start, end;
       static int  (*fn)(pid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_getscheduler");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_getscheduler");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_getscheduler", end);
       } else {
               rval = fn(pid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_rr_get_interval (pid_t pid, struct timespec * tp)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , struct timespec * );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_rr_get_interval");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_rr_get_interval");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, tp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_rr_get_interval", end);
       } else {
               rval = fn(pid, tp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_setparam (pid_t pid, const struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , const struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_setparam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_setparam");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_setparam", end);
       } else {
               rval = fn(pid, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sched_setscheduler (pid_t pid, int policy, const struct sched_param *param)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , int , const struct sched_param *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sched_setscheduler");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sched_setscheduler");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, policy, param);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_setscheduler", end);
       } else {
               rval = fn(pid, policy, param);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sched_yield", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
       struct timespec start, end;
       static int  (*fn)(int , fd_set *, fd_set *, fd_set *, struct timeval *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "select");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "select");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nfds, readfds, writefds, exceptfds, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("select", end);
       } else {
               rval = fn(nfds, readfds, writefds, exceptfds, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_close (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_close");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_close");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_close", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_destroy (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_destroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_destroy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_destroy", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semget (key_t key, int nsems, int semflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, nsems, semflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semget", end);
       } else {
               rval = fn(key, nsems, semflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_getvalue (sem_t *sem, int *sval)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_getvalue");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_getvalue");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, sval);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_getvalue", end);
       } else {
               rval = fn(sem, sval);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_init (sem_t *sem, int pshared, unsigned int value)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, int , unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_init");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_init");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, pshared, value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_init", end);
       } else {
               rval = fn(sem, pshared, value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semop (int semid, struct sembuf *sops, unsigned nsops)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sembuf *, unsigned );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semop");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(semid, sops, nsops);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semop", end);
       } else {
               rval = fn(semid, sops, nsops);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_post (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_post");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_post");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_post", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semtimedop (int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sembuf *, unsigned , struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semtimedop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semtimedop");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(semid, sops, nsops, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semtimedop", end);
       } else {
               rval = fn(semid, sops, nsops, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_timedwait (sem_t *sem, const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_timedwait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_timedwait");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_timedwait", end);
       } else {
               rval = fn(sem, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_trywait (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_trywait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_trywait");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_trywait", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_wait", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setegid (gid_t egid)
{
       struct timespec start, end;
       static int  (*fn)(gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setegid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setegid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(egid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setegid", end);
       } else {
               rval = fn(egid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setenv (const char *name, const char *value, int overwrite)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, value, overwrite);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setenv", end);
       } else {
               rval = fn(name, value, overwrite);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
seteuid (uid_t euid)
{
       struct timespec start, end;
       static int  (*fn)(uid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "seteuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "seteuid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(euid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("seteuid", end);
       } else {
               rval = fn(euid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setgid (gid_t gid)
{
       struct timespec start, end;
       static int  (*fn)(gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setgid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setgid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(gid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setgid", end);
       } else {
               rval = fn(gid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setitimer (int which, const struct itimerval *new_value, struct itimerval *old_value)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct itimerval *, struct itimerval *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setitimer");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setitimer");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(which, new_value, old_value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setitimer", end);
       } else {
               rval = fn(which, new_value, old_value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setlogmask (int mask)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setlogmask");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setlogmask");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mask);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setlogmask", end);
       } else {
               rval = fn(mask);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setpgid (pid_t pid, pid_t pgid)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , pid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setpgid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setpgid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, pgid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setpgid", end);
       } else {
               rval = fn(pid, pgid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setpgrp (void)
{
       struct timespec start, end;
       static int  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setpgrp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setpgrp");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setpgrp", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
setregid (gid_t rgid, gid_t egid)
{
       struct timespec start, end;
       static int  (*fn)(gid_t , gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setregid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setregid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(rgid, egid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setregid", end);
       } else {
               rval = fn(rgid, egid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setreuid (uid_t ruid, uid_t euid)
{
       struct timespec start, end;
       static int  (*fn)(uid_t , uid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setreuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setreuid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ruid, euid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setreuid", end);
       } else {
               rval = fn(ruid, euid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setsockopt (int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , const void *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setsockopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setsockopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, level, optname, optval, optlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setsockopt", end);
       } else {
               rval = fn(sockfd, level, optname, optval, optlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setuid (uid_t uid)
{
       struct timespec start, end;
       static int  (*fn)(uid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setuid");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(uid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setuid", end);
       } else {
               rval = fn(uid);
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
shmctl (int shmid, int cmd, struct shmid_ds *buf)
{
       struct timespec start, end;
       static int  (*fn)(int , int , struct shmid_ds *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmctl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmctl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(shmid, cmd, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmctl", end);
       } else {
               rval = fn(shmid, cmd, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shmdt (const void *shmaddr)
{
       struct timespec start, end;
       static int  (*fn)(const void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmdt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmdt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(shmaddr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmdt", end);
       } else {
               rval = fn(shmaddr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shmget (key_t key, size_t size, int shmflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, size, shmflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmget", end);
       } else {
               rval = fn(key, size, shmflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shm_open (const char *name, int oflag, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int , mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shm_open");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shm_open");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, oflag, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shm_open", end);
       } else {
               rval = fn(name, oflag, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shm_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shm_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shm_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shm_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shutdown (int sockfd, int how)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shutdown");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shutdown");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, how);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shutdown", end);
       } else {
               rval = fn(sockfd, how);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigaction (int signum, const struct sigaction *act,  struct sigaction *oldact)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct sigaction *,  struct sigaction *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigaction");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigaction");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(signum, act, oldact);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigaction", end);
       } else {
               rval = fn(signum, act, oldact);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigaddset (sigset_t *set, int signum)
{
       struct timespec start, end;
       static int  (*fn)(sigset_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigaddset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigaddset");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, signum);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigaddset", end);
       } else {
               rval = fn(set, signum);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigaltstack (const stack_t *ss, stack_t *oss)
{
       struct timespec start, end;
       static int  (*fn)(const stack_t *, stack_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigaltstack");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigaltstack");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ss, oss);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigaltstack", end);
       } else {
               rval = fn(ss, oss);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigdelset (sigset_t *set, int signum)
{
       struct timespec start, end;
       static int  (*fn)(sigset_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigdelset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigdelset");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, signum);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigdelset", end);
       } else {
               rval = fn(set, signum);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigemptyset (sigset_t *set)
{
       struct timespec start, end;
       static int  (*fn)(sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigemptyset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigemptyset");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigemptyset", end);
       } else {
               rval = fn(set);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigfillset (sigset_t *set)
{
       struct timespec start, end;
       static int  (*fn)(sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigfillset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigfillset");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigfillset", end);
       } else {
               rval = fn(set);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sighold (int sig)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sighold");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sighold");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sighold", end);
       } else {
               rval = fn(sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigignore (int sig)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigignore");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigignore");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigignore", end);
       } else {
               rval = fn(sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
siginterrupt (int sig, int flag)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "siginterrupt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "siginterrupt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig, flag);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("siginterrupt", end);
       } else {
               rval = fn(sig, flag);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigismember (const sigset_t *set, int signum)
{
       struct timespec start, end;
       static int  (*fn)(const sigset_t *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigismember");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigismember");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, signum);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigismember", end);
       } else {
               rval = fn(set, signum);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sigmask);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigpause", end);
       } else {
               rval = fn(sigmask);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigpending (sigset_t *set)
{
       struct timespec start, end;
       static int  (*fn)(sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigpending");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigpending");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigpending", end);
       } else {
               rval = fn(set);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigprocmask (int how, const sigset_t *set, sigset_t *oldset)
{
       struct timespec start, end;
       static int  (*fn)(int , const sigset_t *, sigset_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigprocmask");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigprocmask");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(how, set, oldset);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigprocmask", end);
       } else {
               rval = fn(how, set, oldset);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigqueue (pid_t pid, int sig, const union sigval value)
{
       struct timespec start, end;
       static int  (*fn)(pid_t , int , const union sigval );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigqueue");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigqueue");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, sig, value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigqueue", end);
       } else {
               rval = fn(pid, sig, value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sigrelse (int sig)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigrelse");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigrelse");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigrelse", end);
       } else {
               rval = fn(sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mask);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigsuspend", end);
       } else {
               rval = fn(mask);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, info, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigtimedwait", end);
       } else {
               rval = fn(set, info, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, sig);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigwait", end);
       } else {
               rval = fn(set, sig);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(set, info);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigwaitinfo", end);
       } else {
               rval = fn(set, info);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sockatmark (int sockfd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sockatmark");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sockatmark");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sockatmark", end);
       } else {
               rval = fn(sockfd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
socket (int domain, int type, int protocol)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "socket");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "socket");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(domain, type, protocol);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("socket", end);
       } else {
               rval = fn(domain, type, protocol);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
socketpair (int domain, int type, int protocol, int sv[2])
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , int sv[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "socketpair");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "socketpair");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(domain, type, protocol, sv);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("socketpair", end);
       } else {
               rval = fn(domain, type, protocol, sv);
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
system (const char *command)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "system");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "system");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(command);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("system", end);
       } else {
               rval = fn(command);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcdrain (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcdrain");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcdrain");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcdrain", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcflow (int fd, int action)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcflow");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcflow");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, action);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcflow", end);
       } else {
               rval = fn(fd, action);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcflush (int fd, int queue_selector)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcflush");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcflush");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, queue_selector);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcflush", end);
       } else {
               rval = fn(fd, queue_selector);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcgetattr (int fd, struct termios *termios_p)
{
       struct timespec start, end;
       static int  (*fn)(int , struct termios *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcgetattr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcgetattr");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, termios_p);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcgetattr", end);
       } else {
               rval = fn(fd, termios_p);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcsendbreak (int fd, int duration)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcsendbreak");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcsendbreak");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, duration);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcsendbreak", end);
       } else {
               rval = fn(fd, duration);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcsetattr (int fd, int optional_actions,  const struct termios *termios_p)
{
       struct timespec start, end;
       static int  (*fn)(int , int ,  const struct termios *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcsetattr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcsetattr");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, optional_actions, termios_p);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcsetattr", end);
       } else {
               rval = fn(fd, optional_actions, termios_p);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
tcsetpgrp (int fd, pid_t pgrp)
{
       struct timespec start, end;
       static int  (*fn)(int , pid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcsetpgrp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcsetpgrp");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, pgrp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcsetpgrp", end);
       } else {
               rval = fn(fd, pgrp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
timer_create (clockid_t clockid, struct sigevent *sevp, timer_t *timerid)
{
       struct timespec start, end;
       static int  (*fn)(clockid_t , struct sigevent *, timer_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "timer_create");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "timer_create");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(clockid, sevp, timerid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("timer_create", end);
       } else {
               rval = fn(clockid, sevp, timerid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
timer_delete (timer_t timerid)
{
       struct timespec start, end;
       static int  (*fn)(timer_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "timer_delete");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "timer_delete");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timerid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("timer_delete", end);
       } else {
               rval = fn(timerid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
timer_getoverrun (timer_t timerid)
{
       struct timespec start, end;
       static int  (*fn)(timer_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "timer_getoverrun");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "timer_getoverrun");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timerid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("timer_getoverrun", end);
       } else {
               rval = fn(timerid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
timer_gettime (timer_t timerid, struct itimerspec *curr_value)
{
       struct timespec start, end;
       static int  (*fn)(timer_t , struct itimerspec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "timer_gettime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "timer_gettime");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timerid, curr_value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("timer_gettime", end);
       } else {
               rval = fn(timerid, curr_value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
timer_settime (timer_t timerid, int flags, const struct itimerspec *new_value, struct itimerspec * old_value)
{
       struct timespec start, end;
       static int  (*fn)(timer_t , int , const struct itimerspec *, struct itimerspec * );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "timer_settime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "timer_settime");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timerid, flags, new_value, old_value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("timer_settime", end);
       } else {
               rval = fn(timerid, flags, new_value, old_value);
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
ttyname_r (int fd, char *buf, size_t buflen)
{
       struct timespec start, end;
       static int  (*fn)(int , char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ttyname_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ttyname_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd, buf, buflen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ttyname_r", end);
       } else {
               rval = fn(fd, buf, buflen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
uname (struct utsname *buf)
{
       struct timespec start, end;
       static int  (*fn)(struct utsname *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "uname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "uname");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("uname", end);
       } else {
               rval = fn(buf);
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
unlockpt (int fd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "unlockpt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "unlockpt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("unlockpt", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
unsetenv (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "unsetenv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "unsetenv");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("unsetenv", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
utime (const char *filename, const struct utimbuf *times)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const struct utimbuf *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "utime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "utime");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(filename, times);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("utime", end);
       } else {
               rval = fn(filename, times);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
utimensat (int dirfd, const char *pathname, const struct timespec times[2], int flags)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, const struct timespec times[2], int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "utimensat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "utimensat");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(dirfd, pathname, times, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("utimensat", end);
       } else {
               rval = fn(dirfd, pathname, times, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
utimes (const char *filename, const struct timeval times[2])
{
       struct timespec start, end;
       static int  (*fn)(const char *, const struct timeval times[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "utimes");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "utimes");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(filename, times);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("utimes", end);
       } else {
               rval = fn(filename, times);
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
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(idtype, id, infop, options);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("waitid", end);
       } else {
               rval = fn(idtype, id, infop, options);
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
gethostid (void)
{
       struct timespec start, end;
       static long  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostid");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

long long 
atoll (const char *nptr)
{
       struct timespec start, end;
       static long long  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "atoll");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "atoll");
            goto out;
       }
       long long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nptr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("atoll", end);
       } else {
               rval = fn(nptr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

long 
sysconf (int name)
{
       struct timespec start, end;
       static long  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sysconf");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sysconf");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sysconf", end);
       } else {
               rval = fn(name);
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

long 
ulimit (int cmd, long newlimit)
{
       struct timespec start, end;
       static long  (*fn)(int , long );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ulimit");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ulimit");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cmd, newlimit);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ulimit", end);
       } else {
               rval = fn(cmd, newlimit);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

mode_t 
umask (mode_t mask)
{
       struct timespec start, end;
       static mode_t  (*fn)(mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "umask");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "umask");
            goto out;
       }
       mode_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mask);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("umask", end);
       } else {
               rval = fn(mask);
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
getpgid (pid_t pid)
{
       struct timespec start, end;
       static pid_t  (*fn)(pid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpgid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpgid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpgid", end);
       } else {
               rval = fn(pid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

pid_t 
getpgrp (void)
{
       struct timespec start, end;
       static pid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpgrp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpgrp");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpgrp", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

pid_t 
getpid (void)
{
       struct timespec start, end;
       static pid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

pid_t 
getppid (void)
{
       struct timespec start, end;
       static pid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getppid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getppid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getppid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

pid_t 
getsid (pid_t pid)
{
       struct timespec start, end;
       static pid_t  (*fn)(pid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsid", end);
       } else {
               rval = fn(pid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

pid_t 
setsid (void)
{
       struct timespec start, end;
       static pid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setsid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setsid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setsid", end);
       } else {
               rval = fn();
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

pid_t 
tcgetsid (int fd)
{
       struct timespec start, end;
       static pid_t  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "tcgetsid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tcgetsid");
            goto out;
       }
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(fd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("tcgetsid", end);
       } else {
               rval = fn(fd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       pid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pid, status, options);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("waitpid", end);
       } else {
               rval = fn(pid, status, options);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

sighandler_t 
sigset (int sig, sighandler_t disp)
{
       struct timespec start, end;
       static sighandler_t  (*fn)(int , sighandler_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sigset");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sigset");
            goto out;
       }
       sighandler_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sig, disp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sigset", end);
       } else {
               rval = fn(sig, disp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

size_t 
confstr (int name, char *buf, size_t len)
{
       struct timespec start, end;
       static size_t  (*fn)(int , char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "confstr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "confstr");
            goto out;
       }
       size_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, buf, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("confstr", end);
       } else {
               rval = fn(name, buf, len);
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

speed_t 
cfgetispeed (const struct termios *termios_p)
{
       struct timespec start, end;
       static speed_t  (*fn)(const struct termios *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfgetispeed");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfgetispeed");
            goto out;
       }
       speed_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(termios_p);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfgetispeed", end);
       } else {
               rval = fn(termios_p);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

speed_t 
cfgetospeed (const struct termios *termios_p)
{
       struct timespec start, end;
       static speed_t  (*fn)(const struct termios *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfgetospeed");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfgetospeed");
            goto out;
       }
       speed_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(termios_p);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfgetospeed", end);
       } else {
               rval = fn(termios_p);
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
mq_receive (mqd_t mqdes, char *msg_ptr,  size_t msg_len, unsigned *msg_prio)
{
       struct timespec start, end;
       static ssize_t  (*fn)(mqd_t , char *,  size_t , unsigned *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_receive");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_receive");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_receive", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
mq_timedreceive (mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio, const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static ssize_t  (*fn)(mqd_t , char *, size_t , unsigned *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_timedreceive");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_timedreceive");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_timedreceive", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
msgrcv (int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , long , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgrcv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgrcv");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, msgp, msgsz, msgtyp, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgrcv", end);
       } else {
               rval = fn(msqid, msgp, msgsz, msgtyp, msgflg);
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
recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recvfrom");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recvfrom");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags, src_addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("recvfrom", end);
       } else {
               rval = fn(sockfd, buf, len, flags, src_addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
recv (int sockfd, void *buf, size_t len, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recv");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("recv", end);
       } else {
               rval = fn(sockfd, buf, len, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
recvmsg (int sockfd, struct msghdr *msg, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , struct msghdr *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recvmsg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recvmsg");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, msg, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("recvmsg", end);
       } else {
               rval = fn(sockfd, msg, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
send (int sockfd, const void *buf, size_t len, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "send");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "send");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("send", end);
       } else {
               rval = fn(sockfd, buf, len, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const struct msghdr *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sendmsg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sendmsg");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, msg, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sendmsg", end);
       } else {
               rval = fn(sockfd, msg, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
sendto (int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const void *, size_t , int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sendto");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sendto");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags, dest_addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sendto", end);
       } else {
               rval = fn(sockfd, buf, len, flags, dest_addr, addrlen);
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

struct group *
getgrent (void)
{
       struct timespec start, end;
       static struct group * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgrent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgrent");
            goto out;
       }
       struct group * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgrent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct group *
getgrgid (gid_t gid)
{
       struct timespec start, end;
       static struct group * (*fn)(gid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgrgid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgrgid");
            goto out;
       }
       struct group * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(gid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgrgid", end);
       } else {
               rval = fn(gid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct group *
getgrnam (const char *name)
{
       struct timespec start, end;
       static struct group * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getgrnam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getgrnam");
            goto out;
       }
       struct group * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getgrnam", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct hostent *
gethostbyaddr (const void *addr, socklen_t len, int type)
{
       struct timespec start, end;
       static struct hostent * (*fn)(const void *, socklen_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyaddr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyaddr");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len, type);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyaddr", end);
       } else {
               rval = fn(addr, len, type);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct hostent *
gethostbyname (const char *name)
{
       struct timespec start, end;
       static struct hostent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct hostent *
gethostent (void)
{
       struct timespec start, end;
       static struct hostent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostent");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct lconv *
localeconv (void)
{
       struct timespec start, end;
       static struct lconv * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "localeconv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "localeconv");
            goto out;
       }
       struct lconv * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("localeconv", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct netent *
getnetbyaddr (uint32_t net, int type)
{
       struct timespec start, end;
       static struct netent * (*fn)(uint32_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetbyaddr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetbyaddr");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(net, type);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetbyaddr", end);
       } else {
               rval = fn(net, type);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct netent *
getnetbyname (const char *name)
{
       struct timespec start, end;
       static struct netent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetbyname");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetbyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct netent *
getnetent (void)
{
       struct timespec start, end;
       static struct netent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetent");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct passwd *
getpwent (void)
{
       struct timespec start, end;
       static struct passwd * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpwent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpwent");
            goto out;
       }
       struct passwd * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpwent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct passwd *
getpwnam (const char *name)
{
       struct timespec start, end;
       static struct passwd * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpwnam");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpwnam");
            goto out;
       }
       struct passwd * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpwnam", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct passwd *
getpwuid (uid_t uid)
{
       struct timespec start, end;
       static struct passwd * (*fn)(uid_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpwuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpwuid");
            goto out;
       }
       struct passwd * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(uid);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpwuid", end);
       } else {
               rval = fn(uid);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotobyname (const char *name)
{
       struct timespec start, end;
       static struct protoent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotobyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotobyname");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotobyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotobynumber (int proto)
{
       struct timespec start, end;
       static struct protoent * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotobynumber");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotobynumber");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotobynumber", end);
       } else {
               rval = fn(proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotoent (void)
{
       struct timespec start, end;
       static struct protoent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotoent");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotoent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct servent *
getservbyname (const char *name, const char *proto)
{
       struct timespec start, end;
       static struct servent * (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservbyname");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservbyname", end);
       } else {
               rval = fn(name, proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct servent *
getservbyport (int port, const char *proto)
{
       struct timespec start, end;
       static struct servent * (*fn)(int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservbyport");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservbyport");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(port, proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservbyport", end);
       } else {
               rval = fn(port, proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct servent *
getservent (void)
{
       struct timespec start, end;
       static struct servent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservent");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct tm *
getdate (const char *string)
{
       struct timespec start, end;
       static struct tm * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getdate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getdate");
            goto out;
       }
       struct tm * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(string);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getdate", end);
       } else {
               rval = fn(string);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct tm *
gmtime (const time_t *timep)
{
       struct timespec start, end;
       static struct tm * (*fn)(const time_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gmtime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gmtime");
            goto out;
       }
       struct tm * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gmtime", end);
       } else {
               rval = fn(timep);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct tm *
gmtime_r (const time_t *timep, struct tm *result)
{
       struct timespec start, end;
       static struct tm * (*fn)(const time_t *, struct tm *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gmtime_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gmtime_r");
            goto out;
       }
       struct tm * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gmtime_r", end);
       } else {
               rval = fn(timep, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct tm *
localtime (const time_t *timep)
{
       struct timespec start, end;
       static struct tm * (*fn)(const time_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "localtime");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "localtime");
            goto out;
       }
       struct tm * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("localtime", end);
       } else {
               rval = fn(timep);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct tm *
localtime_r (const time_t *timep, struct tm *result)
{
       struct timespec start, end;
       static struct tm * (*fn)(const time_t *, struct tm *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "localtime_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "localtime_r");
            goto out;
       }
       struct tm * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(timep, result);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("localtime_r", end);
       } else {
               rval = fn(timep, result);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct utmp *
getutent (void)
{
       struct timespec start, end;
       static struct utmp * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getutent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getutent");
            goto out;
       }
       struct utmp * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getutent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct utmp *
getutid (struct utmp *ut)
{
       struct timespec start, end;
       static struct utmp * (*fn)(struct utmp *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getutid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getutid");
            goto out;
       }
       struct utmp * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ut);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getutid", end);
       } else {
               rval = fn(ut);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct utmp *
getutline (struct utmp *ut)
{
       struct timespec start, end;
       static struct utmp * (*fn)(struct utmp *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getutline");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getutline");
            goto out;
       }
       struct utmp * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ut);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getutline", end);
       } else {
               rval = fn(ut);
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

time_t 
time (time_t *t)
{
       struct timespec start, end;
       static time_t  (*fn)(time_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "time");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "time");
            goto out;
       }
       time_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(t);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("time", end);
       } else {
               rval = fn(t);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uid_t 
geteuid (void)
{
       struct timespec start, end;
       static uid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "geteuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "geteuid");
            goto out;
       }
       uid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("geteuid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

uid_t 
getuid (void)
{
       struct timespec start, end;
       static uid_t  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getuid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getuid");
            goto out;
       }
       uid_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getuid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

uint16_t 
htons (uint16_t hostshort)
{
       struct timespec start, end;
       static uint16_t  (*fn)(uint16_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "htons");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "htons");
            goto out;
       }
       uint16_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(hostshort);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("htons", end);
       } else {
               rval = fn(hostshort);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint16_t 
ntohs (uint16_t netshort)
{
       struct timespec start, end;
       static uint16_t  (*fn)(uint16_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ntohs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ntohs");
            goto out;
       }
       uint16_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(netshort);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ntohs", end);
       } else {
               rval = fn(netshort);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint32_t 
htonl (uint32_t hostlong)
{
       struct timespec start, end;
       static uint32_t  (*fn)(uint32_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "htonl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "htonl");
            goto out;
       }
       uint32_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(hostlong);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("htonl", end);
       } else {
               rval = fn(hostlong);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint32_t 
ntohl (uint32_t netlong)
{
       struct timespec start, end;
       static uint32_t  (*fn)(uint32_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ntohl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ntohl");
            goto out;
       }
       uint32_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(netlong);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ntohl", end);
       } else {
               rval = fn(netlong);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

unsigned int 
alarm (unsigned int seconds)
{
       struct timespec start, end;
       static unsigned int  (*fn)(unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "alarm");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "alarm");
            goto out;
       }
       unsigned int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(seconds);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("alarm", end);
       } else {
               rval = fn(seconds);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       unsigned int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(seconds);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sleep", end);
       } else {
               rval = fn(seconds);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
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
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("abort", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
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
cfmakeraw (struct termios *termios_p)
{
       struct timespec start, end;
       static void  (*fn)(struct termios *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "cfmakeraw");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "cfmakeraw");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(termios_p);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("cfmakeraw", end);
       } else {
               fn(termios_p);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
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
encrypt (char block[64], int edflag)
{
       struct timespec start, end;
       static void  (*fn)(char block[64], int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "encrypt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "encrypt");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(block, edflag);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("encrypt", end);
       } else {
               fn(block, edflag);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
encrypt_r (char *block, int edflag, struct crypt_data *data)
{
       struct timespec start, end;
       static void  (*fn)(char *, int , struct crypt_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "encrypt_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "encrypt_r");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(block, edflag, data);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("encrypt_r", end);
       } else {
               fn(block, edflag, data);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endgrent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endgrent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endgrent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endgrent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endhostent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endhostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endhostent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endhostent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endnetent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endnetent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endnetent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endprotoent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endprotoent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endprotoent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endpwent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endpwent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endpwent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endpwent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endservent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endservent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endservent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endutent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endutent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endutent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endutent", end);
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
freeaddrinfo (struct addrinfo *res)
{
       struct timespec start, end;
       static void  (*fn)(struct addrinfo *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "freeaddrinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "freeaddrinfo");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("freeaddrinfo", end);
       } else {
               fn(res);
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
hdestroy_r (struct hsearch_data *htab)
{
       struct timespec start, end;
       static void  (*fn)(struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hdestroy_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hdestroy_r");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hdestroy_r", end);
       } else {
               fn(htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
hdestroy (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hdestroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hdestroy");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hdestroy", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
herror (const char *s)
{
       struct timespec start, end;
       static void  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "herror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "herror");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("herror", end);
       } else {
               fn(s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
insque (void *elem, void *prev)
{
       struct timespec start, end;
       static void  (*fn)(void *, void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "insque");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "insque");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(elem, prev);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("insque", end);
       } else {
               fn(elem, prev);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
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
psiginfo (const siginfo_t *pinfo, const char *s)
{
       struct timespec start, end;
       static void  (*fn)(const siginfo_t *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "psiginfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "psiginfo");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(pinfo, s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("psiginfo", end);
       } else {
               fn(pinfo, s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
psignal (int sig, const char *s)
{
       struct timespec start, end;
       static void  (*fn)(int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "psignal");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "psignal");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(sig, s);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("psignal", end);
       } else {
               fn(sig, s);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
pthread_cleanup_pop (int execute)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_cleanup_pop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cleanup_pop");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(execute);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_cleanup_pop", end);
       } else {
               fn(execute);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
pthread_exit (void *retval)
{
       struct timespec start, end;
       static void  (*fn)(void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_exit");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_exit");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(retval);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_exit", end);
       } else {
               fn(retval);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
pthread_testcancel (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_testcancel");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_testcancel");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_testcancel", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
remque (void *elem)
{
       struct timespec start, end;
       static void  (*fn)(void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "remque");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "remque");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(elem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("remque", end);
       } else {
               fn(elem);
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
setgrent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setgrent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setgrent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setgrent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
sethostent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sethostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sethostent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sethostent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setkey (const char *key)
{
       struct timespec start, end;
       static void  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setkey");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setkey");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(key);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setkey", end);
       } else {
               fn(key);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setnetent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setnetent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setnetent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setprotoent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setprotoent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setprotoent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setpwent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setpwent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setpwent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setpwent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setservent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setservent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setservent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void *
shmat (int shmid, const void *shmaddr, int shmflg)
{
       struct timespec start, end;
       static void * (*fn)(int , const void *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmat");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmat");
            goto out;
       }
       void * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(shmid, shmaddr, shmflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmat", end);
       } else {
               rval = fn(shmid, shmaddr, shmflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
siglongjmp (sigjmp_buf env, int val)
{
       struct timespec start, end;
       static void  (*fn)(sigjmp_buf , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "siglongjmp");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "siglongjmp");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(env, val);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("siglongjmp", end);
       } else {
               fn(env, val);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
srandom (unsigned int seed)
{
       struct timespec start, end;
       static void  (*fn)(unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "srandom");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "srandom");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(seed);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("srandom", end);
       } else {
               fn(seed);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
srand (unsigned int seed)
{
       struct timespec start, end;
       static void  (*fn)(unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "srand");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "srand");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(seed);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("srand", end);
       } else {
               fn(seed);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
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

