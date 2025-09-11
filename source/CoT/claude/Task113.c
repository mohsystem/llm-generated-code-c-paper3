
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateStrings(char** strings, int count) {
    if (strings == NULL || count <= 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\\0';
        }
        return empty;
    }
    
    size_t totalLength = 1; // For null terminator
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            totalLength += strlen(strings[i]);
        }
    }
    
    char* result = (char*)malloc(totalLength);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\\0';
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            strcat(result, strings[i]);
        }
    }
    
    return result;
}

int main() {
    // Test case 1: Basic concatenation
    char* test1[] = {"Hello", " ", "World"};
    char* result1 = concatenateStrings(test1, 3);
    printf("%s\\n", result1);
    free(result1);
    
    // Test case 2: Empty strings
    char* test2[] = {"", "Test", ""};
    char* result2 = concatenateStrings(test2, 3);
    printf("%s\\n", result2);
    free(result2);
    
    // Test case 3: Multiple strings
    char* test3[] = {"First", "Second", "Third"};
    char* result3 = concatenateStrings(test3, 3);
    printf("%s\\n", result3);
    free(result3);
    
    // Test case 4: Single string
    char* test4[] = {"OnlyString"};
    char* result4 = concatenateStrings(test4, 1);
    printf("%s\\n", result4);
    free(result4);
    
    // Test case 5: NULL input
    char* result5 = concatenateStrings(NULL, 0);
    printf("%s\\n", result5);
    free(result5);
    
    return 0;
}
