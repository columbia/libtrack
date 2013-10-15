
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>

static int local_pclose(FILE *iop);
static FILE * local_popen(const char *command, const char *type);


void err_msg(const char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	fprintf(stderr, "\nTesting stderr: ");
	vfprintf(stderr, msg, args);
	va_end(args);
	fprintf(stderr, "\n");
	fflush(NULL);
}

void std_msg(const char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	fprintf(stdout, "\nTesting stdout: ");
	vfprintf(stdout, msg, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(NULL);
}

int test_popen(void)
{
	FILE *iptOutput;
	const char *cmd = "/system/bin/iptables -t filter -X bw_INPUT";
	const char *flags = "r";

	fprintf(stdout, "Testing popen(\"%s\", \"%s\")...\n", cmd, flags);
	fflush(NULL);
	iptOutput = local_popen(cmd, flags);
	fflush(NULL);
	if (!iptOutput) {
		fprintf(stderr, "Failed to open pipe to iptables cmd: %d\n", errno);
		return -1;
	}
	fprintf(stdout, "Closing fd:%d\n", fileno(iptOutput));
	fflush(NULL);
	local_pclose(iptOutput);
	fflush(NULL);

	return 0;
}

int main(int argc, char **argv)
{
	unsigned int i, n = 0;
	int *myarg;

	if (argc > 1)
		n = atoi(argv[1]);
	if (n <= 0)
		n = 10;
	printf("testing %d arguments...\n", n);

	myarg = calloc(n, sizeof(int));
	for (i=0; i < n; i++)
		myarg[i] = i;

	if (n == 5) {
		fprintf(stdout,
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4]);
		std_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4]);
		err_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4]);
	} else if (n == 10) {
		fprintf(stdout,
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9]);
		std_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9]);
		err_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9]);
	} else if (n == 15) {
		fprintf(stdout,
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14]);
		std_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14]);
		err_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14]);
	} else if (n == 20) {
		fprintf(stdout,
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19]);
		std_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19]);
		err_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19]);
	} else if (n == 25) {
		fprintf(stdout,
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19],
			myarg[20], myarg[21], myarg[22], myarg[23], myarg[24]);
		std_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19],
			myarg[20], myarg[21], myarg[22], myarg[23], myarg[24]);
		err_msg("\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n"
			"arg%d, arg%d, arg%d, arg%d, arg%d\n",
			myarg[0], myarg[1], myarg[2], myarg[3], myarg[4],
			myarg[5], myarg[6], myarg[7], myarg[8], myarg[9],
			myarg[10], myarg[11], myarg[12], myarg[13], myarg[14],
			myarg[15], myarg[16], myarg[17], myarg[18], myarg[19],
			myarg[20], myarg[21], myarg[22], myarg[23], myarg[24]);
	} else {
		fprintf(stdout, "unsupported number of args:%d (use multiples of 5)\n", n);
	}
	free(myarg);

	static int SEC = 7;
	fprintf(stdout, "sleeping for %d seconds\n", SEC);
	sleep(SEC);

	test_popen();

	fork();
	fprintf(stdout, "proc:%d\n", getpid());
	exit(0);
	return EXIT_SUCCESS;
}



static struct pid {
	struct pid *next;
	FILE *fp;
	int fd;
	pid_t pid;
} *pidlist = NULL;
	
//static rwlock_t pidlist_lock = RWLOCK_INITIALIZER;

FILE * local_popen(const char *command, const char *type)
{
	struct pid *cur, *old;
	FILE *iop;
	const char * volatile xtype = type;
	int pdes[2], pid, serrno;
	volatile int twoway;
	int flags;

	flags = strchr(xtype, 'e') ? O_CLOEXEC : 0;
	if (strchr(xtype, '+')) {
		twoway = 1;
		xtype = "r+";
		if (socketpair(AF_LOCAL, SOCK_STREAM, 0, pdes) < 0)
			return NULL;
	} else  {
		twoway = 0;
		xtype = strrchr(xtype, 'r') ? "r" : "w";
		if (pipe2(pdes, flags) == -1)
			return NULL;
	}

	if ((cur = malloc(sizeof(struct pid))) == NULL) {
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		errno = ENOMEM;
		return (NULL);
	}

	//(void)rwlock_rdlock(&pidlist_lock);
	switch (pid = vfork()) {
	case -1:			/* Error. */
		serrno = errno;
		//(void)rwlock_unlock(&pidlist_lock);
		free(cur);
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		errno = serrno;
		fprintf(stdout, "ERROR:%d\n", serrno);
		fflush(stdout);
		return (NULL);
		/* NOTREACHED */
	case 0:				/* Child. */
		fprintf(stdout, "child:%d\n", getpid());
		fflush(stdout);
		/* POSIX.2 B.3.2.2 "popen() shall ensure that any streams
		   from previous popen() calls that remain open in the 
		   parent process are closed in the new child process. */
		for (old = pidlist; old; old = old->next)
			close(old->fd); /* don't allow a flush */

		if (*xtype == 'r') {
			(void)close(pdes[0]);
			if (pdes[1] != STDOUT_FILENO) {
				(void)dup2(pdes[1], STDOUT_FILENO);
				(void)close(pdes[1]);
			}
			if (twoway)
				(void)dup2(STDOUT_FILENO, STDIN_FILENO);
		} else {
			(void)close(pdes[1]);
			if (pdes[0] != STDIN_FILENO) {
				(void)dup2(pdes[0], STDIN_FILENO);
				(void)close(pdes[0]);
			}
		}

		fflush(NULL);
		fprintf(stderr, "\nchild about to exec...\n");
		fflush(NULL);
		sleep(2);
		execl("/system/bin/sh", "sh", "-c", command, NULL);
		fprintf(stderr, "\nexecl returned:%d to pid:%d (vfork ret=%d)\n", errno, getpid(), pid);
		fflush(NULL);
		_exit(127);
		/* NOTREACHED */
	}

	fprintf(stdout, "\n\nparent(%d)\n", getpid());
	fflush(stdout);
	sleep(2);
	fprintf(stdout, "parent(%d) continuing...\n", getpid());
	fflush(stdout);

	/* Parent; assume fdopen can't fail. */
	if (*xtype == 'r') {
		iop = fdopen(pdes[0], xtype);
		cur->fd = pdes[0];
		(void)close(pdes[1]);
	} else {
		iop = fdopen(pdes[1], xtype);
		cur->fd = pdes[1];
		(void)close(pdes[0]);
	}

	/* Link into list of file descriptors. */
	cur->fp = iop;
	cur->pid =  pid;
	cur->next = pidlist;
	pidlist = cur;
	//(void)rwlock_unlock(&pidlist_lock);

	return (iop);
}

/*
 * pclose --
 *	Pclose returns -1 if stream is not associated with a `popened' command,
 *	if already `pclosed', or waitpid returns an error.
 */
int local_pclose(FILE *iop)
{
	struct pid *cur, *last;
	int pstat;
	pid_t pid;

	//rwlock_wrlock(&pidlist_lock);

	/* Find the appropriate file pointer. */
	for (last = NULL, cur = pidlist; cur; last = cur, cur = cur->next)
		if (cur->fp == iop)
			break;
	if (cur == NULL) {
		//(void)rwlock_unlock(&pidlist_lock);
		return (-1);
	}

	(void)fclose(iop);

	/* Remove the entry from the linked list. */
	if (last == NULL)
		pidlist = cur->next;
	else
		last->next = cur->next;

	//(void)rwlock_unlock(&pidlist_lock);

	do {
		pid = waitpid(cur->pid, &pstat, 0);
	} while (pid == -1 && errno == EINTR);

	free(cur);

	return (pid == -1 ? -1 : pstat);
}
