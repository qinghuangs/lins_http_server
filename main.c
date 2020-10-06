
#include <stdio.h>
#include "event_loop/event_loop.h"
#include "event_loop/http_server.h"

//数据读到buffer之后的callback
int onRequest(struct http_request *httpRequest, struct http_response *httpResponse) {
    char *url = httpRequest->url;
    //char *question = memmem(url, strlen(url), "?", 1);
    char *question = memmem_lin(url, strlen(url), "?", 1);
    char *path = NULL;
    if (question != NULL) {
        path = malloc(question - url);
        strncpy(path, url, question - url);
    } else {
        path = malloc(strlen(url));
        strncpy(path, url, strlen(url));
    }

    if (strcmp(path, "/") == 0) {
        httpResponse->statusCode = OK;
        httpResponse->statusMessage = "OK";
        httpResponse->contentType = "text/html";
        httpResponse->body = "<html><head><title>This is network programming</title></head><body><h1>Hello, network programming</h1></body></html>";
    } else if (strcmp(path, "/network") == 0) {
        httpResponse->statusCode = OK;
        httpResponse->statusMessage = "OK";
        httpResponse->contentType = "text/plain";
        httpResponse->body = "hello, network programming";
    } else {
        httpResponse->statusCode = NotFound;
        httpResponse->statusMessage = "Not Found";
        httpResponse->keep_connected = 1;
    }

    return 0;
}

int main() {
    //对event_loop进行初始化
    struct event_loop *eventLoop = event_loop_init();

    //初始化http_server
    struct http_server *httpServer = http_server_new(eventLoop, SERV_PORT, onRequest, 2);

    http_server_start(httpServer);

    // main thread for acceptor
    event_loop_run(eventLoop);
    return 0;
}
