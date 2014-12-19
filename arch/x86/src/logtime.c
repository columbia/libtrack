char fd_type(int fd)
{
	struct stat buf;
	static int (*libc_getsockname)(int, struct sockaddr *, socklen_t *);

	if (fstat(fd, &buf) < 0)
		return '?';
	if (S_ISREG(buf.st_mode))
		return 'F';
	if (S_ISDIR(buf.st_mode))
		return 'f';
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		return 'D';
	if (S_ISFIFO(buf.st_mode))
		return 'P';
	if (S_ISLNK(buf.st_mode))
		return 'l';
	if (S_ISSOCK(buf.st_mode)) {
		struct sockaddr sam;
		int len = sizeof(sam);
		if (!libc_getsockname)
			libc_getsockname = dlsym(RTLD_NEXT, "getsockname");
		if (!libc_getsockname)
			return '?';
		if (libc_getsockname(fd, (struct sockaddr *)&sam, &len) < 0)
			return '?';
		if (sam.sa_family == AF_UNIX || sam.sa_family == AF_LOCAL)
			return 'U';
		return 'S';
	}
	return '?';
}

/*
 * Helper function calculating time elapsed from timestamp a
 * to timestamp b and store it to b.
 */
void
_timespec_sub (struct timespec *a, const struct timespec *b)
{
	a->tv_sec  -= b->tv_sec;
	a->tv_nsec -= b->tv_nsec;
	if (a->tv_nsec < 0) {
		a->tv_nsec += 1000000000;
		a->tv_sec  -= 1;
	}
}

/*
 * Helper function writing timing info
 */
void
_logtime (char *funcname, struct timespec end)
{
	char line[LINE_LEN];
	
	pid_t (*libc_getpid)(void);
	if (libc_getpid == NULL) {
		*(void **)(&libc_getpid) = dlsym(RTLD_NEXT, "getpid");
		if (libc_getpid == NULL){
			fprintf(stderr, "_logtime: Error loading getpid\n");
			return;
		}
	}
	static size_t (*libc_strlen)(const char *s);
	if (libc_strlen == NULL) {
		*(void **)(&libc_strlen) = dlsym(RTLD_NEXT, "strlen");
		if (libc_strlen == NULL){
			fprintf(stderr, "_logtime: Error loading strlen\n");
			return;
		}
	}
	static int (*libc_sprintf)(char *str, const char *format, ...);
	if (libc_sprintf == NULL) {
		*(void **)(&libc_sprintf) = dlsym(RTLD_NEXT, "sprintf");
		if (libc_sprintf == NULL){
			fprintf(stderr, "_logtime: Error loading sprintf\n");
			return;
		}
	}
	static int (*libc_open)(const char *pathname, int flags, mode_t mode);
	if (libc_open == NULL) {
		*(void **)(&libc_open) = dlsym(RTLD_NEXT, "open");
		if (libc_open == NULL){
			fprintf(stderr, "_logtime: Error loading open\n");
			return;
		}
	}
	static ssize_t (*libc_write)(int fd, const void *buf, size_t count);
	if (libc_write == NULL) {
		*(void **)(&libc_write) = dlsym(RTLD_NEXT, "write");
		if (libc_write == NULL) {
			fprintf(stderr, "_logtime: Error loading write\n");
			return;
		}
	}
	if (thread_fd < 0) {
		(libc_sprintf)(filename, "%s.%ld.%ld.log", "__progname",
			(long) (libc_getpid)(),syscall(SYS_gettid));
		thread_fd = (libc_open)(filename, MODE);
		if (thread_fd < 0) {
			fprintf(stderr,
				"_logtime: Error while opening: <%s>\n",
				filename);
			return;
		}
	}
	(libc_sprintf)(line, " T.T:LOG:T:%s:%lu.%lu\n", funcname,
		       (unsigned long) end.tv_sec,
		       (unsigned long) end.tv_nsec);
	(libc_write)(thread_fd, line, (libc_strlen)(line));
}

