
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789abcdef";
    srand(time(NULL) + rand()); // Seed with time and previous random
    
    int pos = 0;
    for(int i = 0; i < 32; i++) {
        if(i == 8 || i == 12 || i == 16 || i == 20) {
            sessionId[pos++] = '-';
        }
        sessionId[pos++] = charset[rand() % 16];
    }
    sessionId[36] = '\\0';
}

int main() {
    char sessionId[37];
    
    // Test cases
    for(int i = 0; i < 5; i++) {
        generateSessionId(sessionId);
        printf("Session ID %d: %s\\n", i+1, sessionId);
    }
    
    return 0;
}
