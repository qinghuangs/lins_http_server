cmake_minimum_required(VERSION 3.10)
project(lins_http_server)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
add_compile_options(-pthread)
aux_source_directory(. DIR_SRCS)

add_subdirectory(./event_loop)

add_executable(lins_http_server ${DIR_SRCS})

#添加链接库
target_link_libraries(lins_http_server event_loop_lib)

#添加phtread库
#find_package(Threads REQUIRED)
#target_link_libraries(lins_http_server Threads::Threads)

#或者
target_link_libraries(lins_http_server pthread)