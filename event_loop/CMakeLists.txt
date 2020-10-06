aux_source_directory(. DIR_EVENT_LOOP_SRCS)

add_library(event_loop_lib ${DIR_EVENT_LOOP_SRCS} common.c)