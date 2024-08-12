#include <errno.h>              // for errno
#include <stdint.h>             // for int32_t, uint32_t
#include <stdio.h>              // for printf
#include <string.h>             // for memcpy, strlen
#include "include/consts.h"     // for k_max_msg
#include "include/msg.h"        // for msg
#include "include/read_full.h"  // for read_full
#include "include/write_all.h"  // for write_all

int32_t one_request(int connfd){
    char rbuf[4 + k_max_msg + 1];
    errno = 0;
    int32_t err = read_full(connfd, rbuf, 4);
    if(err){
        if (errno == 0) {
            msg("EOF");
        } else{
            msg("read() error");
        }
        return err;
    }

    uint32_t len = 0;
    memcpy(&len, rbuf,4);
    if(len > k_max_msg){
        msg("too long");
        return -1;
    }

    err = read_full(connfd, &rbuf[4], len);
    if(err){
        msg("read() error");
        return err;
    }
    
    rbuf[4 + len] = '\0';
    printf("client says: %s\n", &rbuf[4]);//do_something
    
    const char reply[] = "world";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(connfd, wbuf, 4 + len);
}