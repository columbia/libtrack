/*
 * ipc
 */
int 
shmctl (int shmid, int cmd, struct shmid_ds *buf)
{
       struct timespec start, end;
       static int  (*fn)(int , int , struct shmid_ds *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmctl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmctl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(shmid, cmd, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmctl", end);
       } else {
               rval = fn(shmid, cmd, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shmdt (const void *shmaddr)
{
       struct timespec start, end;
       static int  (*fn)(const void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmdt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmdt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(shmaddr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmdt", end);
       } else {
               rval = fn(shmaddr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shmget (key_t key, size_t size, int shmflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shmget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shmget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, size, shmflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shmget", end);
       } else {
               rval = fn(key, size, shmflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shm_open (const char *name, int oflag, mode_t mode)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int , mode_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shm_open");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shm_open");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, oflag, mode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shm_open", end);
       } else {
               rval = fn(name, oflag, mode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
shm_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shm_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shm_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shm_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
pipe (int pipefd[2])
{
       struct timespec start, end;
       static int  (*fn)(int pipefd[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "pipe");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "pipe");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(pipefd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("pipe", end);
       } else {
               rval = fn(pipefd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_close (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_close");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_close");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_close", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_destroy (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_destroy");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_destroy");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_destroy", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semget (key_t key, int nsems, int semflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, nsems, semflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semget", end);
       } else {
               rval = fn(key, nsems, semflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_getvalue (sem_t *sem, int *sval)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_getvalue");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_getvalue");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, sval);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_getvalue", end);
       } else {
               rval = fn(sem, sval);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_init (sem_t *sem, int pshared, unsigned int value)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, int , unsigned int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_init");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_init");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, pshared, value);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_init", end);
       } else {
               rval = fn(sem, pshared, value);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semop (int semid, struct sembuf *sops, unsigned nsops)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sembuf *, unsigned );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semop");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(semid, sops, nsops);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semop", end);
       } else {
               rval = fn(semid, sops, nsops);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_post (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_post");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_post");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_post", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
semtimedop (int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sembuf *, unsigned , struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "semtimedop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "semtimedop");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(semid, sops, nsops, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("semtimedop", end);
       } else {
               rval = fn(semid, sops, nsops, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_timedwait (sem_t *sem, const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_timedwait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_timedwait");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_timedwait", end);
       } else {
               rval = fn(sem, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_trywait (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_trywait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_trywait");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_trywait", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sem_wait (sem_t *sem)
{
       struct timespec start, end;
       static int  (*fn)(sem_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sem_wait");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sem_wait");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sem);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sem_wait", end);
       } else {
               rval = fn(sem);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_close (mqd_t mqdes)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_close");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_close");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_close", end);
       } else {
               rval = fn(mqdes);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_getattr (mqd_t mqdes, struct mq_attr *attr)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , struct mq_attr *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_getattr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_getattr");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, attr);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_getattr", end);
       } else {
               rval = fn(mqdes, attr);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_notify (mqd_t mqdes, const struct sigevent *sevp)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const struct sigevent *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_notify");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_notify");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, sevp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_notify", end);
       } else {
               rval = fn(mqdes, sevp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_send (mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const char *, size_t , unsigned );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_send");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_send");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_send", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_timedsend (mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio,  const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static int  (*fn)(mqd_t , const char *, size_t , unsigned ,  const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_timedsend");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_timedsend");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_timedsend", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
mq_unlink (const char *name)
{
       struct timespec start, end;
       static int  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_unlink");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_unlink");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_unlink", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
       struct timespec start, end;
       static int  (*fn)(int , int , struct msqid_ds *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgctl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgctl");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, cmd, buf);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgctl", end);
       } else {
               rval = fn(msqid, cmd, buf);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgget (key_t key, int msgflg)
{
       struct timespec start, end;
       static int  (*fn)(key_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgget");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgget");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(key, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgget", end);
       } else {
               rval = fn(key, msgflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
msgsnd (int msqid, const void *msgp, size_t msgsz, int msgflg)
{
       struct timespec start, end;
       static int  (*fn)(int , const void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgsnd");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgsnd");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, msgp, msgsz, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgsnd", end);
       } else {
               rval = fn(msqid, msgp, msgsz, msgflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
mq_receive (mqd_t mqdes, char *msg_ptr,  size_t msg_len, unsigned *msg_prio)
{
       struct timespec start, end;
       static ssize_t  (*fn)(mqd_t , char *,  size_t , unsigned *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_receive");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_receive");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_receive", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
mq_timedreceive (mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio, const struct timespec *abs_timeout)
{
       struct timespec start, end;
       static ssize_t  (*fn)(mqd_t , char *, size_t , unsigned *, const struct timespec *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "mq_timedreceive");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "mq_timedreceive");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("mq_timedreceive", end);
       } else {
               rval = fn(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
msgrcv (int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , long , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "msgrcv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "msgrcv");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(msqid, msgp, msgsz, msgtyp, msgflg);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("msgrcv", end);
       } else {
               rval = fn(msqid, msgp, msgsz, msgtyp, msgflg);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}
/*
 * End of ipc
 */
