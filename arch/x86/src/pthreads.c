/*
 * Pthreads
 *
 * Note that unlike bionic libc, in glibc pthreads
 * live in another shared library and preloading
 * glibc in the GOT of a process has some implications.
 *
 * Specifically, dlsym used the default calloc which
 * ends up being recursively traced. To solve this,
 * we preload pthread symbols from glibc.so which
 * will end up using our modified calloc version that
 * is recursion free.
 *
 * Unfortunatelly, some pthread functions are not exposed
 * via libc and may cause problemms. If this is the case
 * in the future we will stop tracing them.
 */

/*
 * Invoked too often to trace
 *
 * We don't trace them in Android either.
 */
//int
//pthread_mutex_lock(pthread_mutex_t *mutex)
//{
//       static int  (*fn)(pthread_mutex_t *);
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_mutex_lock");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_mutex_lock");
//            goto out;
//       }
//       int  rval;
//       if (entered == 1)
//               _backtrace();
//out:
//       __sync_fetch_and_sub(&entered, 1);
//       return fn(mutex);
//}
//
//int
//pthread_mutex_unlock(pthread_mutex_t *mutex)
//{
//       static int  (*fn)(pthread_mutex_t *);
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_mutex_unlock");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_mutex_unlock");
//            goto out;
//       }
//       int  rval;
//       if (entered == 1)
//               _backtrace();
//out:
//       __sync_fetch_and_sub(&entered, 1);
//       return fn(mutex);
//}
//pthread_t
//pthread_self(void)
//{
//       struct timespec start, end;
//       static int  (*fn)(void);
//       __sync_fetch_and_add(&entered, 1);
//       if (fn == NULL)
//           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_self");
//       if (fn == NULL){
//            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_self");
//            goto out;
//       }
//       pthread_t  rval;
//       if (entered == 1) {
//               _backtrace();
//               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
//               rval = fn();
//               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
//               _timespec_sub(&end, &start);
//               _logtime("pthread_self", end);
//       } else {
//               rval = fn();
//       }
//out:
//       __sync_fetch_and_sub(&entered, 1);
//       return rval;
//}

int
pthread_cond_signal(pthread_cond_t *cond)
{
	struct timespec start, end;
       static int  (*fn)(pthread_cond_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_signal");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_signal");
            goto out;
       }
       int rval;
       if (entered == 1) {
		_backtrace();
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
		rval = fn(cond);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
		_timespec_sub(&end, &start);
               _logtime("pthread_cond_signal", end);
       } else {
               rval = fn(cond);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int
pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
	struct timespec start, end;
       static int  (*fn)(pthread_cond_t *, const pthread_condattr_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_init");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_init");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cond, attr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_cond_init", end);
       } else {
               rval = fn(cond, attr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int
pthread_cond_destroy(pthread_cond_t *cond)
{
	struct timespec start, end;
       static int  (*fn)(pthread_cond_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_destroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_destroy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cond);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pthread_cond_destroy", end);
       } else {
		rval = fn(cond);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int
pthread_cond_broadcast(pthread_cond_t *cond)
{
	struct timespec start, end;
       static int  (*fn)(pthread_cond_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_broadcast");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_broadcast");
            goto out;
       }
       int rval;
       if (entered == 1) {
            _backtrace();
	    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(cond);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("pthread_cond_broadcast", end);
	} else {
		rval = fn(cond);
        }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int
pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
       static int  (*fn)(pthread_cond_t *, pthread_mutex_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_wait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_wait");
            goto out;
       }
       int  rval;
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(cond, mutex);
}

int
pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime)
{
       static int  (*fn)(pthread_cond_t *, pthread_mutex_t *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_cond_timedwait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pthread_cond_timedwait");
            goto out;
       }
       if (entered == 1)
               _backtrace();
out:
       __sync_fetch_and_sub(&entered, 1);
       return fn(cond, mutex, abstime);
}

int
pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
        struct timespec start, end;
        static  int (*fn)(pthread_t *, const pthread_attr_t *,
                  void *(*s)(void *), void *);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void **)(&fn) = dlsym(RTLD_NEXT, "pthread_create");
        if (fn == NULL) {
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "pthread_create");
            goto out;
        }
	int rval;
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

int 
pthread_attr_destroy (pthread_attr_t *attr)
{
       struct timespec start, end;
       static int  (*fn)(pthread_attr_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_destroy");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_getdetachstate");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_getinheritsched");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_getschedparam");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_getschedpolicy");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_getscope");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_init");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_setdetachstate");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_setinheritsched");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_setschedparam");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_setschedpolicy");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_attr_setscope");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_equal");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_getschedparam");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_setcancelstate");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_setcanceltype");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_setschedparam");
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
           *(void **)(&fn) = dlsym(dlopen("/lib/x86_64-linux-gnu/libc.so.6",RTLD_LAZY), "pthread_exit");
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
/*
 * End of Pthreads
 */
