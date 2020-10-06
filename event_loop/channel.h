//
// Created by linqinghuang on 2020/10/4.
//

#ifndef LINS_HTTP_SERVER_CHANNEL_H
#define LINS_HTTP_SERVER_CHANNEL_H

#include "../event_loop/event_loop.h"

#define EVENT_READ 0x02

#define EVENT_WRITE 0x04

typedef int (*event_read_callback)(void *data);
typedef int (*event_write_callback)(void *data);

struct channel {
    int fd;
    int events;

    event_read_callback eventReadCallback;
    event_write_callback  eventWriteCallback;
    void * data;
};

struct channel * channel_new(int fd, int events, event_read_callback eventReadCallback,
        event_write_callback eventWriteCallback, void *data);

int channel_write_event_is_enabled(struct channel *channel);

int channel_write_event_enable(struct channel *channel);

int channel_write_event_disable(struct channel *channel);
#endif //LINS_HTTP_SERVER_CHANNEL_H
