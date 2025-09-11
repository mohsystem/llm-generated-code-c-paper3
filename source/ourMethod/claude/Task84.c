
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SESSION_ID_LENGTH 32

void generate_session_id(char* session_id) {
    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charset_length = strlen(charset);
    
    // Initialize random seed using both time and clock
    srand((unsigned int)time(NULL) ^ (unsigned int)clock());
    
    for(int i = 0; i < SESSION_ID_LENGTH; i++) {
        int index = rand() % charset_length;
        session_id[i] = charset[index];
    }
    session_id[SESSION_ID_LENGTH] = '\\0';
}

int main() {
    char session_id[SESSION_ID_LENGTH + 1];
    
    // Test cases
    for(int i = 0; i < 5; i++) {
        generate_session_id(session_id);
        printf("Generated Session ID %d: %s\\n", i+1, session_id);
    }
    
    return 0;
}
