/* benchmark.c
 *
 * Copyright (C) 2014 Vaggelis Atlidakis <vatlidak@cs.columbia.edu>
 *
 * Benchmark average time for memset, and malloc a 256 bytes block
 *
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>
#define BLK_SIZE 256
#define MILLION 1000000
#define REPS 1000*MILLION


static inline void timespec_sub(struct timespec *a, const struct timespec *b)
{
	a->tv_sec  -= b->tv_sec;
	a->tv_nsec -= b->tv_nsec;
	if (a->tv_nsec < 0) {
		a->tv_nsec += 1000000000;
		a->tv_sec  -= 1;
	}
} 

void main(int argc, char** argv)
{
	char *p;
	struct timespec start, stop;
	uint64_t accum;
	uint32_t  i;
	FILE *fp;

	fp=fopen("data/benchmark_stats.txt", "a+");

	accum = 0;
	for (i = 0; i < REPS; i++)
	{
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
		p=malloc(BLK_SIZE);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &stop);
		timespec_sub(&stop, &start);
		accum += (((uint64_t)stop.tv_sec)*1000000000 + ((uint64_t)stop.tv_nsec));
		free(p);
		if ( i != 0 )
		if ( i % (MILLION) == 0 )
			fprintf(fp, "malloc progress: %.2f %% - cur. avg.: %"PRId64"\n", 100* ((float)i / (float)(REPS) ),  accum/(uint64_t)i);
			fflush(fp);
	}
	
	fprintf(fp, "avg. malloc time:%"PRId64" ns after %d reps\n", accum/(uint64_t)i, REPS);
	fflush(fp);

	p=malloc(BLK_SIZE);
	accum = 0;
	for (i = 0; i < REPS; i++)
	{
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
		memset(p, 0, BLK_SIZE);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &stop);
		timespec_sub(&stop, &start);
		accum += (((uint64_t)stop.tv_sec)*1000000000 + ((uint64_t)stop.tv_nsec));
		if ( i != 0 )
		if ( i % (MILLION) == 0  )
			fprintf(fp, "memset progress: %.2f %% - cur. avg.: %"PRId64"\n", 100* ((float)i /(float)(REPS) ), accum/(uint64_t)i);
			fflush(fp);
	}
	fprintf(fp, "avg. memset:%"PRId64" ns after %d reps\n", accum/(uint64_t)i, REPS);
	fflush(fp);
	free(p);
	fclose(fp);
}
