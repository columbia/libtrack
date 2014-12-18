/*
 * Arguments
 */
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
/*
 * End of Arguments
 */
