
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateRandomString(int length) {
    const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* result = (char*)malloc((length + 1) * sizeof(char));
    
    for(int i = 0; i < length; i++) {
        int index = rand() % (sizeof(chars) - 1);
        result[i] = chars[index];
    }
    result[length] = '\\0';
    
    return result;
}

int main() {
    srand(time(NULL));  // Initialize random seed
    
    // Test cases
    char* str1 = generateRandomString(5);
    printf("%s\\n", str1);  // e.g. "kJheR"
    free(str1);
    
    char* str2 = generateRandomString(10);
    printf("%s\\n", str2);  // e.g. "hGtRfVbNmK"
    free(str2);
    
    char* str3 = generateRandomString(3);
    printf("%s\\n", str3);  // e.g. "XyZ"
    free(str3);
    
    char* str4 = generateRandomString(7);
    printf("%s\\n", str4);  // e.g. "AbCdEfG"
    free(str4);
    
    char* str5 = generateRandomString(1);
    printf("%s\\n", str5);  // e.g. "Q"
    free(str5);
    
    return 0;
}
