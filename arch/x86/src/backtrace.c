/*
 * Helper functions for stack unwinding (backtracing) and
 * creating log-files. It writes unwond stack frames in a
 * per-thread private log-file, named "__progname.pid.tid".
 */
void _backtrace()
{
	int rval;
	char **bt;
	int nframes;
	char line[LINE_LEN];
	void *frames[MAX_FRAMES];

	static size_t (*libc_strlen)(const char *s);
	if (libc_strlen == NULL) {
		*(void **)(&libc_strlen) = dlsym(RTLD_NEXT, "strlen");
		if (libc_strlen == NULL)
			return;
	}
	static int (*libc_sprintf)(char *str, const char *format, ...);
	if (libc_sprintf == NULL) {
		*(void **)(&libc_sprintf) = dlsym(RTLD_NEXT, "sprintf");
		if (libc_sprintf == NULL)
			return;
	}
	static int (*libc_open)(const char *pathname, int flags, mode_t mode);
	if (libc_open == NULL) {
		*(void **)(&libc_open) = dlsym(RTLD_NEXT, "open");
		if (libc_open == NULL)
			return;
	}
	static int (*libc_fprintf)(FILE *stream, const char *format, ...);
	if (libc_fprintf == NULL) {
		*(void **)(&libc_fprintf) = dlsym(RTLD_NEXT, "fprintf");
		if (libc_fprintf == NULL)
			return;
	}
	static ssize_t (*libc_write)(int fd, const void *buf, size_t count);
	if (libc_write == NULL) {
		*(void **)(&libc_write) = dlsym(RTLD_NEXT, "write");
		if (libc_write == NULL)
			return;
	}

	/* Open file once per thread*/
	if (thread_fd < 0) {
		(libc_sprintf)(filename, "%s.%ld.%ld.log", "__progname",
			(long) getpid(), (long) syscall(SYS_gettid));
		thread_fd = (libc_open)(filename, MODE);
		if (thread_fd < 0) {
			(libc_fprintf)(stderr,
				"_backtrace: Error while opening: <%s>\n",
				filename);
			return;
		}
	}

	/* stack unwinding */
	nframes = backtrace(frames, MAX_FRAMES);
	(libc_sprintf)(line, " T:BT:START:%d:\n", (int) nframes - 1);
	rval = write(thread_fd, line, strlen(line));
	if (rval != (libc_strlen)(line)) {
		(libc_fprintf)(stderr, "write\n");
		return;
	}
	backtrace_symbols_fd(frames, nframes, thread_fd);
}

