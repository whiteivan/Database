#include "../include/write_all.h"
#include "../include/read_full.h"
#include "../include/msg.h"
#include <arpa/inet.h>    // for ntohl, ntohs
#include <errno.h>        // for errno
#include <netinet/in.h>   // for sockaddr_in, INADDR_LOOPBACK, in_addr
#include <stdint.h>       // for int32_t, uint32_t
#include <stdio.h>        // for printf
#include <string.h>       // for memcpy, strlen
#include <sys/socket.h>   // for AF_INET, connect, socket, SOCK_STREAM
#include <unistd.h>       // for close
#include "../include/consts.h"

static int32_t query(int fd, const char* text){
    uint32_t len = (uint32_t)strlen(text);
    if(len > k_max_msg){
        return -1;
    }

    char wbuf[4 + k_max_msg];
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], text, len);
    if (int32_t err = write_all(fd, wbuf, 4 + len)){
        return err;
    }

    char rbuf[4 + k_max_msg + 1];
    errno = 0;
    int32_t err = read_full(fd, rbuf, 4);
    if(err){
        if(errno == 0){
            msg("EOF");
        } else{
            msg("read() error");
        }
        return err;
    }

    memcpy(&len, rbuf, 4);
    if(len > k_max_msg){
        msg("too long");
        return -1;
    }

    err = read_full(fd, &rbuf[4], len);
    if(err){
        msg("read() error");
        return err;
    }

    rbuf[4 + len] = '\0';
    printf("server says: %s\n", &rbuf[4]);
    return 0;
}



int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  // 127.0.0.1
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) {
        die("connect");
    }
    int32_t err = query(fd,"hello1");
    if(err){
        msg("query() error");
    }
    err = query(fd,"hello2");
    if(err){
        msg("query() error");
    }
    err = query(fd,"hello3");
    if(err){
        msg("query() error");
    }
    close(fd);
    return 0;
}
