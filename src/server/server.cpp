#include <arpa/inet.h>               // for ntohl, ntohs
#include <netinet/in.h>              // for sockaddr_in, in_addr
#include <stdint.h>                  // for int32_t
#include <sys/socket.h>              // for AF_INET, accept, bind, listen
#include <unistd.h>                  // for close
#include "../include/msg.h"          // for die
#include "../include/one_request.h"  // for one_request


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    // this is needed for most server applications
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    // bind
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(0);    // wildcard address 0.0.0.0
    int rv = bind(fd, (const sockaddr *)&addr, sizeof(addr));
    if (rv) {
        die("bind()");
    }

    // listen
    rv = listen(fd, SOMAXCONN);
    if (rv) {
        die("listen()");
    }

    while (true) {
        // accept
        struct sockaddr_in client_addr = {};
        socklen_t socklen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &socklen);
        if (connfd < 0) {
            continue;   // error
        }
        
        while (true) {
            int32_t err = one_request(connfd);//only one client connection at once
            if (err) {
                break;
            }
        }
        close(connfd);
    }

    return 0;
}
