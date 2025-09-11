#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to generate a random session ID
static char* generateSessionId() {
    static char sessionId[37];
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, sessionId);
    return sessionId;
}

int main() {
    // Initialize random number generator
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        char* sessionId = generateSessionId();
        printf("Session ID: %s\n", sessionId);
    }

    return 0;
}