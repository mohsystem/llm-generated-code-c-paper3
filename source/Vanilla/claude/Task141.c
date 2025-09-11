
#include <stdio.h>
#include <string.h>

void reverseString(char* str, char* result) {
    if (str == NULL || strlen(str) <= 1) {
        strcpy(result, str);
        return;
    }
    
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\\0';
}

int main() {
    char* testCases[] = {
        "Hello World",
        "Programming",
        "12345",
        "a",
        ""
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    char result[100];
    
    for (int i = 0; i < numTests; i++) {
        printf("Original: %s\\n", testCases[i]);
        reverseString(testCases[i], result);
        printf("Reversed: %s\\n\\n", result);
    }
    
    return 0;
}
