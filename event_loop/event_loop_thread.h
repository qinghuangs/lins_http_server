//
// Created by lin on 2020/10/6.
//

#ifndef LINS_HTTP_SERVER_EVENT_LOOP_THREAD_H
#define LINS_HTTP_SERVER_EVENT_LOOP_THREAD_H
#include "common.h"
#include "event_loop.h"

struct event_loop_thread {
    struct event_loop *eventLoop;
    pthread_t thread_tid;        /* thread ID */
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    char * thread_name;
    long thread_count;    /* # connections handled */
};

int event_loop_thread_init(struct event_loop_thread *eventLoopThread, int i);

//由主线程调用，初始化一个子线程，并且让子线程开始运行event_loop
struct event_loop *event_loop_thread_start(struct event_loop_thread *);
#endif //LINS_HTTP_SERVER_EVENT_LOOP_THREAD_H
