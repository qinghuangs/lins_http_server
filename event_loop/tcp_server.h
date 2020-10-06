//
// Created by lin on 2020/10/6.
//

#ifndef LINS_HTTP_SERVER_TCP_SERVER_H
#define LINS_HTTP_SERVER_TCP_SERVER_H

#include "common.h"
#include "thread_pool.h"
#include "acceptor.h"
#include "tcp_connection.h"

struct TCPserver {
    int port;
    struct event_loop *eventLoop;
    struct acceptor *acceptor;
    connection_completed_call_back connectionCompletedCallBack;
    message_call_back messageCallBack;
    write_completed_call_back writeCompletedCallBack;
    connection_closed_call_back connectionClosedCallBack;
    int threadNum;
    struct thread_pool *threadPool;
    void * data; //for callback use: http_server
};

//准备监听套接字
struct TCPserver *
tcp_server_init(struct event_loop *eventLoop, struct acceptor *acceptor,
                connection_completed_call_back connectionCallBack,
                message_call_back messageCallBack,
                write_completed_call_back writeCompletedCallBack,
                connection_closed_call_back connectionClosedCallBack,
                int threadNum);

//开启监听
void tcp_server_start(struct TCPserver *tcpServer);

#endif //LINS_HTTP_SERVER_TCP_SERVER_H
