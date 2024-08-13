#include <errno.h>        // for errno
#include <fcntl.h>        // for fcntl, F_GETFL, F_SETFL, O_NONBLOCK
#include "include/msg.h"  // for die

void fd_set_nb(int fd){//функция для установки дескриптора в неблокирующий режим
	errno = 0;
	int flags = fcntl(fd, F_GETFL, 0);
	if (errno) {
        die("fcntl error");
        return;
    }
	flags |= O_NONBLOCK;
	errno = 0;
	(void)fcntl(fd, F_SETFL, flags);
	if (errno) {
        die("fcntl error");
    }
}