/*
 * misc
 */
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
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(fd, argv, envp);
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
/*
 * End of misc
 */
