
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int tgkill(pid_t tgid, pid_t tid, int sig);

int main(int argc, char **argv)
{
	int sig, ii;
	if (argc < 3) {
		fprintf(stderr, "usage: %s sig ppid.tid [ppid.tid [ppid.tid ...]]\n", argv[0]);
		exit(1);
	}

	sig = atoi(argv[1]);
	if (sig <= 0 || sig > 31) {
		fprintf(stderr, "invalid signal: %s\n", argv[1]);
		exit(1);
	}

	for (ii = 2; ii < argc; ii++) {
		char *a, *b;
		pid_t tgid, tid;
		a = argv[ii];
		b = strchr(a, '.');
		if (!b) {
			fprintf(stderr, "invalid PPID.TID '%s'\n", argv[ii]);
			continue;
		}
		*b++ = 0;
		tgid = atoi(a);
		tid = atoi(b);
		fprintf(stdout, "Sending sig %d to %d.%d\n", sig, tgid, tid);
		if (tgkill(tgid, tid, sig) < 0)
			fprintf(stderr, "Couldn't signal %d.%d\n", tgid, tid);
	}

}
