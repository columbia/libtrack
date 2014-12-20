/*
 * Network
 */
char *
inet_ntoa (struct in_addr in)
{
       struct timespec start, end;
       static char * (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_ntoa");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_ntoa");
            goto out;
       }
       char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_ntoa", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
endhostent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endhostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endhostent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endhostent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endnetent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endnetent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endnetent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endprotoent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endprotoent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endprotoent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endpwent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endpwent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endpwent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endpwent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endservent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endservent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endservent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
endutent (void)
{
       struct timespec start, end;
       static void  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "endutent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "endutent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("endutent", end);
       } else {
               fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

int 
shutdown (int sockfd, int how)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "shutdown");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "shutdown");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, how);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("shutdown", end);
       } else {
               rval = fn(sockfd, how);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
sockatmark (int sockfd)
{
       struct timespec start, end;
       static int  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sockatmark");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sockatmark");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sockatmark", end);
       } else {
               rval = fn(sockfd);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
socket (int domain, int type, int protocol)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "socket");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "socket");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(domain, type, protocol);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("socket", end);
       } else {
               rval = fn(domain, type, protocol);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
socketpair (int domain, int type, int protocol, int sv[2])
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , int sv[2]);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "socketpair");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "socketpair");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(domain, type, protocol, sv);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("socketpair", end);
       } else {
               rval = fn(domain, type, protocol, sv);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
setsockopt (int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , const void *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setsockopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setsockopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, level, optname, optval, optlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setsockopt", end);
       } else {
               rval = fn(sockfd, level, optname, optval, optlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
       struct timespec start, end;
       static int  (*fn)(int , fd_set *, fd_set *, fd_set *, struct timeval *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "select");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "select");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(nfds, readfds, writefds, exceptfds, timeout);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("select", end);
       } else {
               rval = fn(nfds, readfds, writefds, exceptfds, timeout);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recvfrom");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recvfrom");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags, src_addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("recvfrom", end);
       } else {
               rval = fn(sockfd, buf, len, flags, src_addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
recv (int sockfd, void *buf, size_t len, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recv");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recv");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
		char name[] = "recv_?";
		name[5] = fd_type(sockfd);
               _logtime(name, end);
       } else {
               rval = fn(sockfd, buf, len, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
recvmsg (int sockfd, struct msghdr *msg, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , struct msghdr *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "recvmsg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "recvmsg");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, msg, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("recvmsg", end);
       } else {
               rval = fn(sockfd, msg, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
send (int sockfd, const void *buf, size_t len, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const void *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "send");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "send");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
		char name[] = "send_?";
		name[5] = fd_type(sockfd); 
               _logtime(name, end);
       } else {
               rval = fn(sockfd, buf, len, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const struct msghdr *, int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sendmsg");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sendmsg");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, msg, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sendmsg", end);
       } else {
               rval = fn(sockfd, msg, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

ssize_t 
sendto (int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
       struct timespec start, end;
       static ssize_t  (*fn)(int , const void *, size_t , int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sendto");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sendto");
            goto out;
       }
       ssize_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, buf, len, flags, dest_addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sendto", end);
       } else {
               rval = fn(sockfd, buf, len, flags, dest_addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
listen (int sockfd, int backlog)
{
       struct timespec start, end;
       static int  (*fn)(int , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "listen");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "listen");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, backlog);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("listen", end);
       } else {
               rval = fn(sockfd, backlog);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotobyname (const char *name)
{
       struct timespec start, end;
       static struct protoent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotobyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotobyname");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotobyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotobynumber (int proto)
{
       struct timespec start, end;
       static struct protoent * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotobynumber");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotobynumber");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotobynumber", end);
       } else {
               rval = fn(proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct protoent *
getprotoent (void)
{
       struct timespec start, end;
       static struct protoent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getprotoent");
            goto out;
       }
       struct protoent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getprotoent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct servent *
getservbyname (const char *name, const char *proto)
{
       struct timespec start, end;
       static struct servent * (*fn)(const char *, const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservbyname");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservbyname", end);
       } else {
               rval = fn(name, proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct servent *
getservbyport (int port, const char *proto)
{
       struct timespec start, end;
       static struct servent * (*fn)(int , const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservbyport");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservbyport");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(port, proto);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservbyport", end);
       } else {
               rval = fn(port, proto);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct servent *
getservent (void)
{
       struct timespec start, end;
       static struct servent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getservent");
            goto out;
       }
       struct servent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getservent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

int 
getpeername (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getpeername");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getpeername");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getpeername", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getsockname (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsockname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsockname");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsockname", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
       struct timespec start, end;
       static int  (*fn)(int , int , int , void *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getsockopt");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getsockopt");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, level, optname, optval, optlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getsockopt", end);
       } else {
               rval = fn(sockfd, level, optname, optval, optlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
inet_aton (const char *cp, struct in_addr *inp)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct in_addr *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_aton");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_aton");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp, inp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_aton", end);
       } else {
               rval = fn(cp, inp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
inet_pton (int af, const char *src, void *dst)
{
       struct timespec start, end;
       static int  (*fn)(int , const char *, void *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_pton");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_pton");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(af, src, dst);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_pton", end);
       } else {
               rval = fn(af, src, dst);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getnameinfo (const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
       struct timespec start, end;
       static int  (*fn)(const struct sockaddr *, socklen_t , char *, size_t , char *, size_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnameinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnameinfo");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sa, salen, host, hostlen, serv, servlen, flags);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnameinfo", end);
       } else {
               rval = fn(sa, salen, host, hostlen, serv, servlen, flags);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyaddr_r (const void *addr, socklen_t len, int type, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const void *, socklen_t , int , struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyaddr_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyaddr_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len, type, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyaddr_r", end);
       } else {
               rval = fn(addr, len, type, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyname2_r (const char *name, int af, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const char *, int , struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname2_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname2_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, af, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname2_r", end);
       } else {
               rval = fn(name, af, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostbyname_r (const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(const char *, struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname_r", end);
       } else {
               rval = fn(name, ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostent_r (struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
       struct timespec start, end;
       static int  (*fn)(struct hostent *, char *, size_t , struct hostent **, int *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostent_r");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostent_r");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(ret, buf, buflen, result, h_errnop);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostent_r", end);
       } else {
               rval = fn(ret, buf, buflen, result, h_errnop);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
gethostname (char *name, size_t len)
{
       struct timespec start, end;
       static int  (*fn)(char *, size_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostname");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name, len);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostname", end);
       } else {
               rval = fn(name, len);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
getaddrinfo (const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
       struct timespec start, end;
       static int  (*fn)(const char *, const char *, const struct addrinfo *, struct addrinfo **);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getaddrinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getaddrinfo");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(node, service, hints, res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getaddrinfo", end);
       } else {
               rval = fn(node, service, hints, res);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

const char *
gai_strerror (int errcode)
{
       struct timespec start, end;
       static const char * (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gai_strerror");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gai_strerror");
            goto out;
       }
       const char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(errcode);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gai_strerror", end);
       } else {
               rval = fn(errcode);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "connect");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "connect");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("connect", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
freeaddrinfo (struct addrinfo *res)
{
       struct timespec start, end;
       static void  (*fn)(struct addrinfo *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "freeaddrinfo");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "freeaddrinfo");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(res);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("freeaddrinfo", end);
       } else {
               fn(res);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

int 
bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , const struct sockaddr *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "bind");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "bind");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("bind", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

int 
accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
       struct timespec start, end;
       static int  (*fn)(int , struct sockaddr *, socklen_t *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "accept");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "accept");
            goto out;
       }
       int  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(sockfd, addr, addrlen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("accept", end);
       } else {
               rval = fn(sockfd, addr, addrlen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

const char *
inet_ntop (int af, const void *src, char *dst, socklen_t size)
{
       struct timespec start, end;
       static const char * (*fn)(int , const void *, char *, socklen_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_ntop");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_ntop");
            goto out;
       }
       const char * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(af, src, dst, size);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_ntop", end);
       } else {
               rval = fn(af, src, dst, size);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_addr (const char *cp)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_addr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_addr");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_addr", end);
       } else {
               rval = fn(cp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_lnaof (struct in_addr in)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_lnaof");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_lnaof");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_lnaof", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_netof (struct in_addr in)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(struct in_addr );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_netof");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_netof");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(in);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_netof", end);
       } else {
               rval = fn(in);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

in_addr_t 
inet_network (const char *cp)
{
       struct timespec start, end;
       static in_addr_t  (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "inet_network");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "inet_network");
            goto out;
       }
       in_addr_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(cp);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("inet_network", end);
       } else {
               rval = fn(cp);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

long 
gethostid (void)
{
       struct timespec start, end;
       static long  (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostid");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostid");
            goto out;
       }
       long  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostid", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct hostent *
gethostbyaddr (const void *addr, socklen_t len, int type)
{
       struct timespec start, end;
       static struct hostent * (*fn)(const void *, socklen_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyaddr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyaddr");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(addr, len, type);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyaddr", end);
       } else {
               rval = fn(addr, len, type);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct hostent *
gethostbyname (const char *name)
{
       struct timespec start, end;
       static struct hostent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostbyname");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostbyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct hostent *
gethostent (void)
{
       struct timespec start, end;
       static struct hostent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "gethostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "gethostent");
            goto out;
       }
       struct hostent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("gethostent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

struct netent *
getnetbyaddr (uint32_t net, int type)
{
       struct timespec start, end;
       static struct netent * (*fn)(uint32_t , int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetbyaddr");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetbyaddr");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(net, type);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetbyaddr", end);
       } else {
               rval = fn(net, type);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct netent *
getnetbyname (const char *name)
{
       struct timespec start, end;
       static struct netent * (*fn)(const char *);
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetbyname");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetbyname");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(name);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetbyname", end);
       } else {
               rval = fn(name);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

struct netent *
getnetent (void)
{
       struct timespec start, end;
       static struct netent * (*fn)();
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "getnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "getnetent");
            goto out;
       }
       struct netent * rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("getnetent", end);
       } else {
               rval = fn();
       }
out:
       __sync_fetch_and_sub(&entered, 1);
      return rval;
}

uint16_t 
htons (uint16_t hostshort)
{
       struct timespec start, end;
       static uint16_t  (*fn)(uint16_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "htons");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "htons");
            goto out;
       }
       uint16_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(hostshort);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("htons", end);
       } else {
               rval = fn(hostshort);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint16_t 
ntohs (uint16_t netshort)
{
       struct timespec start, end;
       static uint16_t  (*fn)(uint16_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ntohs");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ntohs");
            goto out;
       }
       uint16_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(netshort);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ntohs", end);
       } else {
               rval = fn(netshort);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint32_t 
htonl (uint32_t hostlong)
{
       struct timespec start, end;
       static uint32_t  (*fn)(uint32_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "htonl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "htonl");
            goto out;
       }
       uint32_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(hostlong);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("htonl", end);
       } else {
               rval = fn(hostlong);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

uint32_t 
ntohl (uint32_t netlong)
{
       struct timespec start, end;
       static uint32_t  (*fn)(uint32_t );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "ntohl");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "ntohl");
            goto out;
       }
       uint32_t  rval;
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               rval = fn(netlong);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("ntohl", end);
       } else {
               rval = fn(netlong);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
       return rval;
}

void 
sethostent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "sethostent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "sethostent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("sethostent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setnetent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setnetent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setnetent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setnetent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setprotoent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setprotoent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setprotoent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setprotoent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}

void 
setservent (int stayopen)
{
       struct timespec start, end;
       static void  (*fn)(int );
       __sync_fetch_and_add(&entered, 1);
       if (fn == NULL)
           *(void **)(&fn) = dlsym(RTLD_NEXT, "setservent");
       if (fn == NULL){
            fprintf(stderr, "dlsym: Error while loading symbol: <%s>\n", "setservent");
            goto out;
       }
       if (entered == 1) {
               _backtrace();
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
               fn(stayopen);
               clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
               _timespec_sub(&end, &start);
               _logtime("setservent", end);
       } else {
               fn(stayopen);
       }
out:
       __sync_fetch_and_sub(&entered, 1);
}
/*
 * End of Network
 */
