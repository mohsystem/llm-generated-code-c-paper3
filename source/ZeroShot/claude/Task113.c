
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateStrings(char** strings, int count) {
    if (strings == NULL || count <= 0) {
        return NULL;
    }
    
    // Calculate total length needed
    int totalLen = 1; // for null terminator
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            totalLen += strlen(strings[i]);
        }
    }
    
    // Allocate memory for result
    char* result = (char*)malloc(totalLen);
    if (result == NULL) {
        return NULL;
    }
    
    // Concatenate strings
    result[0] = '\\0';
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            strcat(result, strings[i]);
        }
    }
    
    return result;
}

int main() {
    // Test case 1
    char* test1[] = {"Hello", " ", "World"};
    char* result1 = concatenateStrings(test1, 3);
    printf("%s\\n", result1);
    free(result1);
    
    // Test case 2
    char* test2[] = {"Test", "1", "2", "3"};
    char* result2 = concatenateStrings(test2, 4);
    printf("%s\\n", result2);
    free(result2);
    
    // Test case 3
    char* test3[] = {"a", "b", "c", "d", "e"};
    char* result3 = concatenateStrings(test3, 5);
    printf("%s\\n", result3);
    free(result3);
    
    // Test case 4
    char* test4[] = {"C", " is ", "awesome"};
    char* result4 = concatenateStrings(test4, 3);
    printf("%s\\n", result4);
    free(result4);
    
    // Test case 5
    char* test5[] = {"test", "case"};
    char* result5 = concatenateStrings(test5, 2);
    printf("%s\\n", result5);
    free(result5);
    
    return 0;
}
