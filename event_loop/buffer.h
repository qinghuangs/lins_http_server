//
// Created by lin on 2020/10/6.
//

#ifndef LINS_HTTP_SERVER_BUFFER_H
#define LINS_HTTP_SERVER_BUFFER_H

#include "common.h"
#include <sys/uio.h>

#define INIT_BUFFER_SIZE 65536

//数据缓冲区
struct buffer {
    char *data;          //实际缓冲
    int readIndex;       //缓冲读取位置
    int writeIndex;      //缓冲写入位置
    int total_size;      //总大小
};

struct buffer *buffer_new();

char *buffer_find_CRLF(struct buffer *buffer);

int buffer_readable_size(struct buffer *buffer);

int buffer_writeable_size(struct buffer *buffer);

int buffer_front_spare_size(struct buffer *buffer);

int buffer_append(struct buffer *buffer, void *data, int size);

int buffer_append_string(struct buffer *buffer, char *data);

void make_room(struct buffer *buffer, int size);

//读socket数据，往buffer里写
int buffer_socket_read(struct buffer *buffer, int fd);

#endif //LINS_HTTP_SERVER_BUFFER_H
