/*
 * Processes & Signals
 */
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
/*
 * End Processes & Signals
 */
