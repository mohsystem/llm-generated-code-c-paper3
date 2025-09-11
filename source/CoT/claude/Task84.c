
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789"
                          "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int len = 32;  // Length of session ID
    
    // Seed the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    // Generate random string
    for (int i = 0; i < len; i++) {
        int index = rand() % (sizeof(charset) - 1);
        sessionId[i] = charset[index];
    }
    sessionId[len] = '\\0';
}

int main() {
    char sessionId[33];  // 32 chars + null terminator
    
    // Test cases
    for(int i = 0; i < 5; i++) {
        generateSessionId(sessionId);
        printf("Generated Session ID %d: %s\\n", i+1, sessionId);
    }
    
    return 0;
}
