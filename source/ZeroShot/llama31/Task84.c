#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Simple UUID generation (not as secure as UUID library but sufficient for example)
void generateUUID(char* out) {
    uint32_t r1 = rand() % (1 << 16);
    uint16_t r2 = rand() % (1 << 16);
    uint16_t r3 = rand() % (1 << 16);
    uint32_t r4 = rand() % (1 << 32);

    sprintf(out, "%08x-%04x-%04x-%04x-%08x",
            r1, r2, r3, (r4 & 0xFFFF), (r4 >> 16));
}

char* generateSessionId() {
    static char uuid[33];
    generateUUID(uuid);
    uuid[8] = uuid[13] = uuid[18] = uuid[23] = '\0'; // Remove dashes
    return uuid;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 5; i++) {
        printf("%s\n", generateSessionId());
    }
    return 0;
}