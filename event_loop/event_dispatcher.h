//
// Created by linqinghuang on 2020/10/4.
//

#ifndef LINS_HTTP_SERVER_EVENT_DISPATCHER_H
#define LINS_HTTP_SERVER_EVENT_DISPATCHER_H

#include "channel.h"

struct event_dispatcher {
    const char *name;

    void* (*init)(struct event_loop * eventLoop);

    int (*add)(struct event_loop * eventLoop, struct channel * channel);

    int (*del)(struct event_loop* eventLoop, struct channel * channel);

    int (*update)(struct event_loop * eventLoop, struct channel * channel);

    int (*dispatch)(struct event_loop * eventLoop, struct timeval *);

    void (*clear)(struct event_loop * eventLoop);
};

#endif //LINS_HTTP_SERVER_EVENT_DISPATCHER_H
