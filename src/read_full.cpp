#include <assert.h>  // for assert
#include <stdint.h>  // for int32_t
#include <unistd.h>  // for size_t, read, ssize_t

int32_t read_full(int fd, char* buf, size_t n){
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