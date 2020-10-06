//
// Created by lin on 2020/10/6.
//

#ifndef LINS_HTTP_SERVER_ACCEPTOR_H
#define LINS_HTTP_SERVER_ACCEPTOR_H

#include "common.h"
#include <netinet/in.h>
#include <fcntl.h>

struct acceptor{
    int listen_port;
    int listen_fd;
} ;

struct acceptor *acceptor_init(int port);

#endif //LINS_HTTP_SERVER_ACCEPTOR_H
