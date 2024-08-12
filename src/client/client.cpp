#include <arpa/inet.h>         // for ntohl, ntohs
#include <netinet/in.h>        // for sockaddr_in, INADDR_LOOPBACK, in_addr
#include <stdint.h>            // for int32_t
#include <sys/socket.h>        // for AF_INET, connect, socket, SOCK_STREAM
#include <unistd.h>            // for close
#include "../include/msg.h"    // for msg, die
#include "../include/query.h"  // for query


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
