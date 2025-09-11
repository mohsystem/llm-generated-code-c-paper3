#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateUUID(char* uuid) {
    static const char* const digits = "0123456789abcdef";
    srand(time(NULL));
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid[i] = '-';
        } else {
            uuid[i] = digits[rand() % 16];
        }
    }
    uuid[36] = '\0';
}

int main() {
    char sessionId[37];
    for (int i = 0; i < 5; i++) {
        generateUUID(sessionId);
        printf("%s\n", sessionId);
    }
    return 0;
}