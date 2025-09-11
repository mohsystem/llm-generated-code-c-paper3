
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

void reverseString(char* str) {
    int length = strlen(str);
    int i;
    for (i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void toUpperCase(char* str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void stringOperations(const char* str1, const char* str2, char* result) {
    if (str1 == NULL || str2 == NULL) {
        strcpy(result, "");
        return;
    }
    
    char copy[MAX_LENGTH];
    char concat[MAX_LENGTH * 2];
    char upper[MAX_LENGTH];
    char reversed[MAX_LENGTH];
    
    // Copy string
    strcpy(copy, str1);
    
    // Concatenate strings
    strcpy(concat, str1);
    strcat(concat, str2);
    
    // Convert to uppercase
    strcpy(upper, str1);
    toUpperCase(upper);
    
    // Reverse string
    strcpy(reversed, str1);
    reverseString(reversed);
    
    // Combine results
    sprintf(result, "Copy: %s\\nConcatenated: %s\\nUppercase: %s\\nReversed: %s",
            copy, concat, upper, reversed);
}

int main() {
    char result[MAX_LENGTH * 4];
    
    // Test cases
    printf("Test 1:\\n");
    stringOperations("hello", "world", result);
    printf("%s\\n", result);
    
    printf("\\nTest 2:\\n");
    stringOperations("C", "Program", result);
    printf("%s\\n", result);
    
    printf("\\nTest 3:\\n");
    stringOperations("ABC", "xyz", result);
    printf("%s\\n", result);
    
    printf("\\nTest 4:\\n");
    stringOperations("12345", "67890", result);
    printf("%s\\n", result);
    
    printf("\\nTest 5:\\n");
    stringOperations("Test", "Case", result);
    printf("%s\\n", result);
    
    return 0;
}
