//
// Created by linqinghuang on 2020/10/4.
//

#ifndef LINS_HTTP_SERVER_CHANNNEL_MAP_H
#define LINS_HTTP_SERVER_CHANNNEL_MAP_H

#include "common.h"
struct channel_map {
    void **entries;

    int nentries;
};

void map_init(struct channel_map *ma);

int map_make_space(struct channel_map *map, int slot, int msize);

#endif //LINS_HTTP_SERVER_CHANNNEL_MAP_H
