//
// Created by lin on 2020/10/6.
//

#ifndef LINS_HTTP_SERVER_TCP_CONNECTION_H
#define LINS_HTTP_SERVER_TCP_CONNECTION_H

#include "channel.h"
#include "buffer.h"
//#include "../tcp_server/tcp_server.h"

typedef int (*connection_completed_call_back)(struct tcp_connection *tcpConnection);

typedef int (*message_call_back)(struct buffer *buffer, struct tcp_connection *tcpConnection);

typedef int (*write_completed_call_back)(struct tcp_connection *tcpConnection);

typedef int (*connection_closed_call_back)(struct tcp_connection *tcpConnection);

struct tcp_connection {
    struct event_loop *eventLoop;
    struct channel *channel;
    char *name;
    struct buffer *input_buffer;   //接收缓冲区
    struct buffer *output_buffer;  //发送缓冲区

    connection_completed_call_back connectionCompletedCallBack;
    message_call_back messageCallBack;
    write_completed_call_back writeCompletedCallBack;
    connection_closed_call_back connectionClosedCallBack;

    void * data; //for callback use: http_server
    void * request; // for callback use
    void * response; // for callback use
};
int tcp_connection_send_data(struct tcp_connection *tcpConnection, void *data, int size);

int tcp_connection_send_buffer(struct tcp_connection *tcpConnection, struct buffer * buffer);

void tcp_connection_shutdown(struct tcp_connection * tcpConnection);

struct tcp_connection *tcp_connection_new(int connected_fd, struct event_loop *eventLoop,
                   connection_completed_call_back connectionCompletedCallBack,
                   connection_closed_call_back connectionClosedCallBack,
                   message_call_back messageCallBack, write_completed_call_back writeCompletedCallBack);

#endif //LINS_HTTP_SERVER_TCP_CONNECTION_H
