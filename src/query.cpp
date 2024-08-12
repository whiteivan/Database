#include <errno.h>              // for errno
#include <stdint.h>             // for int32_t, uint32_t
#include <stdio.h>              // for printf
#include <string.h>             // for memcpy, strlen
#include "include/consts.h"     // for k_max_msg
#include "include/msg.h"        // for msg
#include "include/read_full.h"  // for read_full
#include "include/write_all.h"  // for write_all


int32_t query(int fd, const char* text){
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