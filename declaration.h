#include <cstdint>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <assert.h>

static int32_t read_full(int fd, char* buf, size_t n);
static int32_t one_request(int connfd);
static void die(const char *msg);
static int32_t write_all (int fd, char* buf, size_t n);
static void msg(const char *msg);
static void die(const char *msg);
static void do_something(int connfd);
const size_t k_max_msg = 4096;


static int32_t read_full(int fd, char* buf, size_t n){
    while(n > 0){
        ssize_t rv = read(fd, buf,n);
        if(rv <= 0){
            return -1;//error
        }
        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}

static int32_t write_all (int fd, char* buf, size_t n){
    while(n > 0){
        ssize_t rv = write(fd, buf, n);
        if (rv <= 0) {
            return -1;
        }
        assert((size_t) rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}

static void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static void die(const char *msg) {
    int err = errno;
    fprintf(stderr, "[%d] %s\n", err, msg);
    abort();
}

