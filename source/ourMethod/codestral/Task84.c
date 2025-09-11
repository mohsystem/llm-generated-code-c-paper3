#include <uuid/uuid.h>
#include <stdio.h>

char* generateSessionId() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char *s = malloc(37);
    uuid_unparse(uuid, s);
    return s;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* sessionId = generateSessionId();
        printf("%s\n", sessionId);
        free(sessionId);
    }
    return 0;
}