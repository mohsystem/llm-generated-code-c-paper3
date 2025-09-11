#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSessionId(char* buffer, size_t length) {
    const char charset[] = "0123456789abcdef";
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        buffer[i] = charset[key];
    }
    buffer[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));
    char sessionId[33];
    for (int i = 0; i < 5; ++i) {
        generateSessionId(sessionId, 32);
        printf("Session ID %d: %s\n", i + 1, sessionId);
    }
    return 0;
}