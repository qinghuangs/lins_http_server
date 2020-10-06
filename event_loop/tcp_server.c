//
// Created by lin on 2020/10/6.
//

#include "tcp_server.h"

int handle_connection_established(void *data) {
    struct TCPserver *tcpServer = (struct TCPserver *) data;
    struct acceptor *acceptor = tcpServer->acceptor;
    int listenfd = acceptor->listen_fd;

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int connected_fd = accept(listenfd, (struct sockaddr *) &client_addr, &client_len);
    make_nonblocking(connected_fd);

    //TODO:yolanda_msgx("new connection established, socket == %d", connected_fd);

    // choose event loop from the thread pool
    struct event_loop *eventLoop = thread_pool_get_loop(tcpServer->threadPool);

    // create a new tcp connection
    struct tcp_connection *tcpConnection = tcp_connection_new(connected_fd, eventLoop,
                                                              tcpServer->connectionCompletedCallBack,
                                                              tcpServer->connectionClosedCallBack,
                                                              tcpServer->messageCallBack,
                                                              tcpServer->writeCompletedCallBack);
    //for callback use
    if (tcpServer->data != NULL) {
        tcpConnection->data = tcpServer->data;
    }
    return 0;
}


struct TCPserver *
tcp_server_init(struct event_loop *eventLoop, struct acceptor *acceptor,
                connection_completed_call_back connectionCompletedCallBack,
                message_call_back messageCallBack,
                write_completed_call_back writeCompletedCallBack,
                connection_closed_call_back connectionClosedCallBack,
                int threadNum) {
    struct TCPserver *tcpServer = malloc(sizeof(struct TCPserver));
    tcpServer->eventLoop = eventLoop;
    tcpServer->acceptor = acceptor;
    tcpServer->connectionCompletedCallBack = connectionCompletedCallBack;
    tcpServer->messageCallBack = messageCallBack;
    tcpServer->writeCompletedCallBack = writeCompletedCallBack;
    tcpServer->connectionClosedCallBack = connectionClosedCallBack;
    tcpServer->threadNum = threadNum;
    tcpServer->threadPool = thread_pool_new(eventLoop, threadNum);
    tcpServer->data = NULL;

    return tcpServer;
}

//开启监听
void tcp_server_start(struct TCPserver *tcpServer) {
    struct acceptor *acceptor = tcpServer->acceptor;
    struct event_loop *eventLoop = tcpServer->eventLoop;

    //开启多个线程
    thread_pool_start(tcpServer->threadPool);

    //acceptor主线程， 同时把tcpServer作为参数传给channel对象
    struct channel *channel = channel_new(acceptor->listen_fd, EVENT_READ, handle_connection_established, NULL,
                                          tcpServer);
    event_loop_add_channel_event(eventLoop, channel->fd, channel);
    return;
}
