
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateToken(int length) {
    if (length < 1) return "";
    
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    char* token = (char*)malloc(length + 1);
    if (!token) return NULL;
    
    // Use /dev/urandom for better randomness in production
    srand(time(NULL));
    
    for (int i = 0; i < length; i++) {
        token[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    token[length] = '\\0';
    
    return token;
}

int main() {
    // Test cases
    printf("Test 1: %s\\n", generateToken(16));  // 16 char token
    printf("Test 2: %s\\n", generateToken(24));  // 24 char token
    printf("Test 3: %s\\n", generateToken(32));  // 32 char token
    printf("Test 4: %s\\n", generateToken(0));   // empty token
    printf("Test 5: %s\\n", generateToken(8));   // 8 char token
    
    return 0;
}
