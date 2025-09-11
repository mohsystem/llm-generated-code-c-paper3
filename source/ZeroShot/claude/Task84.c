
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SESSION_ID_LENGTH 32

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789abcdef";
    int i;
    
    // Seed the random number generator
    srand(time(NULL) * rand());
    
    // Generate random hex characters
    for(i = 0; i < SESSION_ID_LENGTH; i++) {
        if(i == 8 || i == 12 || i == 16 || i == 20) {
            sessionId[i] = '-';
        } else {
            int key = rand() % (int)(sizeof(charset) - 1);
            sessionId[i] = charset[key];
        }
    }
    sessionId[SESSION_ID_LENGTH] = '\\0';
}

int main() {
    char sessionId[SESSION_ID_LENGTH + 1];
    
    // Test cases
    for(int i = 0; i < 5; i++) {
        generateSessionId(sessionId);
        printf("Session ID %d: %s\\n", i+1, sessionId);
        // Add small delay to ensure different seeds
        struct timespec ts = {0, 1000000L}; // 1ms delay
        nanosleep(&ts, NULL);
    }
    
    return 0;
}
