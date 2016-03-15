/*
 * Redefine and interpose on the following functions
 */
int
dup3 (int oldfd, int newfd, int flags)
{
	struct timespec start, end;
	static int  (*fn)(int , int , int );
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "dup3");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "dup3");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(oldfd, newfd, flags);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("dup3", end);
out:
	return rval;
}

int
getopt_long (int argc, char * const argv[],
	     const char *optstring,
	     const struct option *longopts,
	     int *longindex)
{
	struct timespec start, end;
	static int  (*fn)(int, char * const, const char *, const struct option *, int *);
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "getopt_long");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"getopt_long");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(argc, argv, optstring, longopts, longindex);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("getopt_long", end);
out:
	return rval;
}

pid_t
wait3 (int *status, int options, struct rusage *rusage)
{
	struct timespec start, end;
	static pid_t  (*fn)(int *, int , struct rusage *);
	pid_t  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "wait3");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "wait3");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(status, options, rusage);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("wait3", end);
out:
	return rval;
}

pid_t
wait4 (pid_t pid, int *status, int options, struct rusage *rusage)
{
	struct timespec start, end;
	static pid_t  (*fn)(pid_t , int *, int , struct rusage *);
	pid_t  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "wait4");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "wait4");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(pid, status, options, rusage);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("wait4", end);
out:
	return rval;
}

int
argvccept4 (int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flagss)
{
	struct timespec start, end;
	static int  (*fn)(int , struct sockaddr *, socklen_t *, int );
	int  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "argvccept4");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "argvccept4");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(sockfd, addr, addrlen, flagss);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("argvccept4", end);
out:
	return rval;
}

struct mallinfo
mallinfo (void)
{
	struct timespec start, end;
	static struct mallinfo  (*fn)();
	struct mallinfo  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "mallinfo");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"mallinfo");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("mallinfo", end);
out:
	return rval;
}

int
pipe2 (int pipefd[2], int flags)
{
	struct timespec start, end;
	static int  (*fn)(int pipefd[2], int );
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "pipe2");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "pipe2");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(pipefd, flags);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("pipe2", end);
out:
	return rval;
}

int
fcloseall (void)
{
	struct timespec start, end;
	static int  (*fn)();
	int  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "fcloseall");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"fcloseall");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("fcloseall", end);
out:
	return rval;
}

int
execvpe (const char *file, char *const argv[], char *const envp[])
{
	struct timespec start, end;
	static int  (*fn)(const char *, char *const , char *const );
	int  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "execvpe");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"execvpe");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(file, argv, envp);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("execvpe", end);
out:
	return rval;
}

int
ppoll (struct pollfd *fds,
       nfds_t nfds,
       const struct timespec *timeout_ts,
       const sigset_t *sigmask)
{
	struct timespec start, end;
	static int  (*fn)(struct pollfd *,
			  nfds_t,
			  const struct timespec *,
			  const sigset_t *);
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "ppoll");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "ppoll");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(fds, nfds, timeout_ts, sigmask);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("ppoll", end);
out:
	return rval;
}

int
clone (int (*func)(void *), void *child_stack, int flags, void *arg, ...)
{
	struct timespec start, end;
	static int  (*fn)(int (*func)(void *), void *, int , void *, ...);
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "clone");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n", "clone");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(func, child_stack, flags, arg);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("clone", end);
out:
	return rval;
}

int
mallopt (int param, int value)
{
	struct timespec start, end;
	static int  (*fn)(int , int );
	int  rval;
	
	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "mallopt");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"mallopt");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(param, value);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("mallopt", end);
out:
	return rval;
}

int
mkostemp (char *template, int suffixlen)
{
	struct timespec start, end;
	static int  (*fn)(char *, int );
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "mkostemp");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"mkostemp");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(template, suffixlen);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("mkostemp", end);
out:
	return rval;
}

void *
mempcpy (void *dest, const void *src, size_t n)
{
	struct timespec start, end;
	static void * (*fn)(void *, const void *, size_t );
	void * rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "mempcpy");
	if (fn == NULL) {
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"mempcpy");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(dest, src, n);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("mempcpy", end);
out:
	return rval;
}

int
cacheflush (char *cacheflushaddr, int nbytes, int cache)
{
	struct timespec start, end;
	static int  (*fn)(char *, int , int );
	int  rval;

	if (fn == NULL)
		*(void **)(&fn) = dlsym(RTLD_NEXT, "cacheflush");
	if (fn == NULL){
		fprintf(stderr,
			"dlsym: Error while loading symbol: <%s>\n",
			"cacheflush");
		goto out;
	}
	_backtrace();
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	rval = fn(cacheflushaddr, nbytes, cache);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
	_timespec_sub(&end, &start);
	_logtime("cacheflush", end);
out:
	return rval;
}
