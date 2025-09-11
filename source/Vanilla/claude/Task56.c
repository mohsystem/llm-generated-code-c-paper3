
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateToken(int length, char* result) {
    const char charset[] = "0123456789"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz"
                          "-_";
    int charset_length = strlen(charset);
    
    srand(time(NULL));
    
    for (int i = 0; i < length; i++) {
        int key = rand() % charset_length;
        result[i] = charset[key];
    }
    result[length] = '\\0';
}

int main() {
    char token[65];  // Max length 64 + null terminator
    
    // Test cases
    generateToken(16, token);
    printf("Test Case 1: Token length 16 = %s\\n", token);
    
    generateToken(24, token);
    printf("Test Case 2: Token length 24 = %s\\n", token);
    
    generateToken(32, token);
    printf("Test Case 3: Token length 32 = %s\\n", token);
    
    generateToken(48, token);
    printf("Test Case 4: Token length 48 = %s\\n", token);
    
    generateToken(64, token);
    printf("Test Case 5: Token length 64 = %s\\n", token);
    
    return 0;
}
