
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

char* copyString(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    size_t len = strlen(input);
    if (len >= MAX_LENGTH) {
        return NULL;
    }
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, input);
    return result;
}

char* concatenateStrings(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 + len2 >= MAX_LENGTH) {
        return NULL;
    }
    char* result = (char*)malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char* getSubstring(const char* input, size_t start, size_t end) {
    if (input == NULL || start > strlen(input) || end > strlen(input) || start > end) {
        return NULL;
    }
    size_t len = end - start;
    if (len >= MAX_LENGTH) {
        return NULL;
    }
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    strncpy(result, input + start, len);
    result[len] = '\\0';
    return result;
}

int compareStrings(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    return strcmp(str1, str2) == 0;
}

int main() {
    // Test case 1: Copy string
    char* copy = copyString("Hello");
    printf("Test 1: %s\\n", copy ? copy : "NULL");
    free(copy);
    
    // Test case 2: Concatenate strings
    char* concat = concatenateStrings("Hello ", "World");
    printf("Test 2: %s\\n", concat ? concat : "NULL");
    free(concat);
    
    // Test case 3: Get substring
    char* substr = getSubstring("Hello World", 0, 5);
    printf("Test 3: %s\\n", substr ? substr : "NULL");
    free(substr);
    
    // Test case 4: Compare strings
    printf("Test 4: %d\\n", compareStrings("Hello", "Hello"));
    
    // Test case 5: Null handling
    char* null_test = concatenateStrings(NULL, "World");
    printf("Test 5: %s\\n", null_test ? null_test : "NULL");
    free(null_test);
    
    return 0;
}
