
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length < 0) {
        return NULL;
    }
    
    const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int lettersLen = strlen(letters);
    
    char* result = (char*)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Initialize random seed using current time
    srand((unsigned int)time(NULL));
    
    for(int i = 0; i < length; i++) {
        result[i] = letters[rand() % lettersLen];
    }
    result[length] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    char* str1 = generateRandomString(5);
    char* str2 = generateRandomString(10);
    char* str3 = generateRandomString(15);
    char* str4 = generateRandomString(20);
    char* str5 = generateRandomString(25);
    
    if (str1 && str2 && str3 && str4 && str5) {
        printf("%s\\n", str1);
        printf("%s\\n", str2);
        printf("%s\\n", str3);
        printf("%s\\n", str4);
        printf("%s\\n", str5);
        
        // Free allocated memory
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        free(str5);
    }
    
    return 0;
}
