/*
 * Terminals
 */
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
/*
 * End Terminals
 */
