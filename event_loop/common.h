//
// Created by linqinghuang on 2020/10/4.
//

#ifndef LINS_HTTP_SERVER_COMMON_H
#define LINS_HTTP_SERVER_COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <assert.h>

#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>


char * memmem_lin(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);
void make_nonblocking(int fd);

#define SERV_PORT 43211
#define LISTENQ 1024
#endif //LINS_HTTP_SERVER_COMMON_H
