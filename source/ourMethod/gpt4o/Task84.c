#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSessionID(char* sessionId, size_t length) {
    const char CHARACTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t charLength = sizeof(CHARACTERS) - 1;

    for (size_t i = 0; i < length; i++) {
        sessionId[i] = CHARACTERS[rand() % charLength];
    }
    sessionId[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));
    char sessionId[17]; // 16 characters + null terminator

    for (int i = 0; i < 5; i++) {
        generateSessionID(sessionId, 16);
        printf("Test Case %d: %s\n", i + 1, sessionId);
    }

    return 0;
}