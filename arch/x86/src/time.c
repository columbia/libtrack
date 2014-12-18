/*
 * time
 */
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
/* 
 * End of time
 */

