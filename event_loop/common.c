//
// Created by lin on 2020/10/6.
//
#include "common.h"

void make_nonblocking(int fd) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

char * memmem_lin(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen) {
    char * source = (char*)haystack;
    char * sub = (char*)needle;
    for (int i = 0; i < haystacklen; i++) {
        if (source[i] != sub[0]) {
            continue;
        }else {
            for (int j = 1; j < needlelen; j++) {
                if(source[i + j] != sub[j]) {
                    break;
                }else {
                    continue;
                }
            }
            return source + i;
        }
    }
    return NULL;
}
