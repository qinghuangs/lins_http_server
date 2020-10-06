//
// Created by linqinghuang on 2020/10/4.
//

#ifndef CHANNEL_H
#define CHANNEL_H

#include <pthread.h>
#include "common.h"
#include "channel_map.h"
#include "channel.h"
#include "event_dispatcher.h"

struct channel_element {
    int type;; // 1. add 2. delete
    struct channel *channel;
    struct channel_element * next;
};

struct event_loop {
    int quit;
    const struct event_dispatcher *eventDispatcher;

    void *event_dispatcher_data;
    struct channel_map *channelMap;

    int is_handle_pending;
    //head和tail，用于维护一个队列
    struct channel_element *pending_head;
    struct channel_element *pending_tail;

    pthread_t owner_thread_id;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int socketPair[2];
    char *thread_name;
};

void assertInSameThread(struct event_loop *eventLoop);

//1： same thread: 0： not the same thread
int isInSameThread(struct event_loop *eventLoop);

struct event_loop *event_loop_init();

struct event_loop *event_loop_init_with_name(char *thread_name);

int channel_event_activate(struct event_loop *eventLoop, int fd, int revents);

int handleWakeup(void *data);

int event_loop_add_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_remove_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_do_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1, int type);

int event_loop_handle_pending_add(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_remove(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_update(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_update_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_run(struct event_loop *eventLoop);

#endif