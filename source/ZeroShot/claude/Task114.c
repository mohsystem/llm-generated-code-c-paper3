
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

void copyString(const char* input, char* output) {
    if (input != NULL && output != NULL) {
        strcpy(output, input);
    }
}

void concatenateStrings(const char* str1, const char* str2, char* result) {
    if (str1 != NULL && str2 != NULL && result != NULL) {
        strcpy(result, str1);
        strcat(result, str2);
    }
}

void reverseString(const char* input, char* output) {
    if (input != NULL && output != NULL) {
        int len = strlen(input);
        for (int i = 0; i < len; i++) {
            output[i] = input[len - 1 - i];
        }
        output[len] = '\\0';
    }
}

void toUpperCase(const char* input, char* output) {
    if (input != NULL && output != NULL) {
        int i = 0;
        while (input[i]) {
            output[i] = toupper(input[i]);
            i++;
        }
        output[i] = '\\0';
    }
}

int countOccurrences(const char* str, char ch) {
    if (str == NULL) return 0;
    
    int count = 0;
    while (*str) {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    char output[MAX_LENGTH];
    
    // Test case 1
    copyString("Hello", output);
    printf("%s\\n", output);
    
    // Test case 2
    concatenateStrings("Hello ", "World", output);
    printf("%s\\n", output);
    
    // Test case 3
    reverseString("Hello", output);
    printf("%s\\n", output);
    
    // Test case 4
    toUpperCase("hello", output);
    printf("%s\\n", output);
    
    // Test case 5
    printf("%d\\n", countOccurrences("hello", 'l'));
    
    return 0;
}
