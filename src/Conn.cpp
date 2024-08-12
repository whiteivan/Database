#include <cstdint>
#include "include/consts.h"
#include <cstddef>  

struct Conn {
    int fd = -1;
    uint32_t state = 0;     // either STATE_REQ or STATE_RES
    // buffer for reading
    std::size_t rbuf_size = 0;
    uint8_t rbuf[4 + k_max_msg];
    // buffer for writing
    std::size_t wbuf_size = 0;
    std::size_t wbuf_sent = 0;
    uint8_t wbuf[4 + k_max_msg];
};