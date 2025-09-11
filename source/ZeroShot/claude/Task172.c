
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SUBSTRINGS 2000

bool isRepeated(const char* str, int len) {
    if (len % 2 != 0) return false;
    int halfLen = len / 2;
    return strncmp(str, str + halfLen, halfLen) == 0;
}

bool isInArray(char** arr, int size, const char* str) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], str) == 0) return true;
    }
    return false;
}

int countDistinctRepeatedSubstrings(const char* text) {
    int n = strlen(text);
    char** result = (char**)malloc(MAX_SUBSTRINGS * sizeof(char*));
    int resultSize = 0;
    
    char* temp = (char*)malloc((n + 1) * sizeof(char));
    
    for (int len = 2; len <= n; len += 2) {
        for (int i = 0; i <= n - len; i++) {
            strncpy(temp, text + i, len);
            temp[len] = '\\0';
            
            if (isRepeated(temp, len) && !isInArray(result, resultSize, temp)) {
                result[resultSize] = (char*)malloc((len + 1) * sizeof(char));
                strcpy(result[resultSize], temp);
                resultSize++;
            }
        }
    }
    
    // Free allocated memory
    free(temp);
    for (int i = 0; i < resultSize; i++) {
        free(result[i]);
    }
    free(result);
    
    return resultSize;
}

int main() {
    // Test cases
    const char* tests[] = {
        "abcabcabc",
        "leetcodeleetcode",
        "aa",
        "aabaabaa",
        "abcd"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Output: %d\\n\\n", countDistinctRepeatedSubstrings(tests[i]));
    }
    
    return 0;
}
