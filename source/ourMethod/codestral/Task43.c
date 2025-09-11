// C language doesn't have built-in support for sessions like other languages.
// This is a simplified example of how sessions could be managed in C.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char sessionId[37];
} Session;

Session* createSession() {
    Session* session = malloc(sizeof(Session));
    for (int i = 0; i < 36; i++) {
        session->sessionId[i] = rand() % 26 + 'a';
    }
    session->sessionId[36] = '\0';
    return session;
}

void terminateSession(Session* session) {
    free(session);
}