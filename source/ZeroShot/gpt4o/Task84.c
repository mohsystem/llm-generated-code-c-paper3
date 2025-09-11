#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSessionID(char *sessionId, size_t length) {
    const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t charactersLen = sizeof(characters) - 1;
    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < length; ++i) {
        sessionId[i] = characters[rand() % charactersLen];
    }
    sessionId[length] = '\0';
}

int main() {
    size_t sessionIdLength = 20;
    char sessionId[sessionIdLength + 1];
    for (int i = 0; i < 5; ++i) {
        generateSessionID(sessionId, sessionIdLength);
        printf("Session ID %d: %s\n", i + 1, sessionId);
    }
    return 0;
}