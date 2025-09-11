// task120.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Handler {
    void (*handleRequest)(struct Handler*, const char*);
    struct Handler* nextHandler;
} Handler;

void consoleHandlerHandleRequest(Handler* handler, const char* input) {
    printf("Displaying input on console: %s\n", input);
    if (handler->nextHandler) {
        handler->nextHandler->handleRequest(handler->nextHandler, input);
    }
}

void webHandlerHandleRequest(Handler* handler, const char* input) {
    printf("Displaying input on web page: %s\n", input);
    if (handler->nextHandler) {
        handler->nextHandler->handleRequest(handler->nextHandler, input);
    }
}

int main() {
    Handler consoleHandler;
    Handler webHandler;

    consoleHandler.handleRequest = consoleHandlerHandleRequest;
    webHandler.handleRequest = webHandlerHandleRequest;

    consoleHandler.nextHandler = &webHandler;

    // Test cases
    consoleHandler.handleRequest(&consoleHandler, "Hello, World!");
    consoleHandler.handleRequest(&consoleHandler, "This is a test.");
    consoleHandler.handleRequest(&consoleHandler, "User-supplied input.");
    consoleHandler.handleRequest(&consoleHandler, "Another test case.");
    consoleHandler.handleRequest(&consoleHandler, "Final test case.");

    return 0;
}