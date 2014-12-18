/*
 * Algorithms
 */
void *
tdelete (const void *key, void **rootp, int (*compar)(const void *, const void *))
{
        void  *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void **,
                     int (*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "tdelete");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "tdelete");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval =  fn(key, rootp, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("tdelete", end);
        } else {
            rval =  fn(key, rootp, compar);
        }

out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void
qsort_r (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg)
{
        struct timespec start, end;
        static void (*fn)(void *base, size_t, size_t,
                   int (*compar)(const void *, const void *, void *), void *arg);

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "qsort_r");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "qsort_r");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            fn(base, nmemb, size, compar, arg);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
        } else {
            fn(base, nmemb, size, compar, arg);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        _logtime("qsort_r", end);
}

void
qsort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
        struct timespec start, end;
        static void (*fn)(void *, size_t, size_t,
                   int (*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "qsort");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "qsort");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            fn(base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
        } else {
            fn(base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        _logtime("qsort", end);
}

void *
lsearch (const void *key, void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                    int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "lsearch");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "lsearch");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("lsearch", end);
        } else {
            rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
lfind (const void *key, const void *base, size_t *nmemb, size_t size, int(*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                     int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "lfind");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "lfind");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("lfind", end);
        } else {
             rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
        void *rval;
        struct timespec start, end;
        static void * (*fn)(const void *, void *, size_t *, size_t,
                     int(*compar)(const void *, const void *));

        __sync_fetch_and_add(&entered, 1);
        if (fn == NULL)
            *(void**)(&fn) = dlsym(RTLD_NEXT, "bsearch");
        if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n",
                    "bsearch");
            goto out;
        }
        if (entered == 1) {
            _backtrace();
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            rval = fn(key, base, nmemb, size, compar);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            _timespec_sub(&end, &start);
            _logtime("bsearch", end);
        } else {
            rval = fn(key, base, nmemb, size, compar);
        }
out:
        __sync_fetch_and_sub(&entered, 1);
        return rval;
}

int 
hcreate_r (size_t nel, struct hsearch_data *htab)
{
       struct timespec start, end;
       static int  (*fn)(size_t , struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hcreate_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hcreate_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nel, htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hcreate_r", end);
       } else {
               rval = fn(nel, htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
hcreate (size_t nel)
{
       struct timespec start, end;
       static int  (*fn)(size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hcreate");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hcreate");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nel);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hcreate", end);
       } else {
               rval = fn(nel);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
hsearch_r (ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab)
{
       struct timespec start, end;
       static int  (*fn)(ENTRY , ACTION , ENTRY **, struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hsearch_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hsearch_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(item, action, retval, htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hsearch_r", end);
       } else {
               rval = fn(item, action, retval, htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
hdestroy_r (struct hsearch_data *htab)
{
       struct timespec start, end;
       static void  (*fn)(struct hsearch_data *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hdestroy_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hdestroy_r");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(htab);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hdestroy_r", end);
       } else {
               fn(htab);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
hdestroy (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "hdestroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "hdestroy");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("hdestroy", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}
/*
 * End of Algorithms
 */
