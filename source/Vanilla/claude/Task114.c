
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void stringOperations(char* str1, char* str2, char* result) {
    char copy[100], concat[200], upper[100], reverse[100];
    int len = strlen(str1);
    
    // Copy
    strcpy(copy, str1);
    
    // Concatenate
    strcpy(concat, str1);
    strcat(concat, str2);
    
    // Convert to uppercase
    strcpy(upper, str1);
    for(int i = 0; upper[i]; i++) {
        upper[i] = toupper(upper[i]);
    }
    
    // Reverse
    for(int i = 0; i < len; i++) {
        reverse[i] = str1[len-1-i];
    }
    reverse[len] = '\\0';
    
    // Combine results
    sprintf(result, "Copy: %s\\nConcatenated: %s\\nUppercase: %s\\nReversed: %s",
            copy, concat, upper, reverse);
}

int main() {
    char result[500];
    
    // Test cases
    printf("Test 1:\\n");
    stringOperations("hello", "world", result);
    printf("%s\\n", result);
    
    printf("\\nTest 2:\\n");
    stringOperations("Java", "Program", result);
    printf("%s\\n", result);
    
    printf("\\nTest 3:\\n");
    stringOperations("abc", "xyz", result);
    printf("%s\\n", result);
    
    printf("\\nTest 4:\\n");
    stringOperations("Test", "Case", result);
    printf("%s\\n", result);
    
    printf("\\nTest 5:\\n");
    stringOperations("String", "Ops", result);
    printf("%s\\n", result);
    
    return 0;
}
