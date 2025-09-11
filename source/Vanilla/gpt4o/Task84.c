#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateSessionId() {
    static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static char sessionId[17];
    int length = 16;

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(characters) - 1);
        sessionId[i] = characters[index];
    }
    sessionId[length] = '\0';

    return sessionId;
}

int main() {
    printf("%s\n", generateSessionId());
    printf("%s\n", generateSessionId());
    printf("%s\n", generateSessionId());
    printf("%s\n", generateSessionId());
    printf("%s\n", generateSessionId());
    return 0;
}