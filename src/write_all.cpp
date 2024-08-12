#include <assert.h>  // for assert
#include <stdint.h>  // for int32_t
#include <unistd.h>  // for size_t, write, ssize_t

int32_t write_all (int fd, char* buf, size_t n){
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