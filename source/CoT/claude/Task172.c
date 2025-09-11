
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_RESULT 2000

bool isEqual(const char* str1, const char* str2, int len) {
    for(int i = 0; i < len; i++) {
        if(str1[i] != str2[i]) return false;
    }
    return true;
}

bool isInArray(char arr[MAX_RESULT][2001], int size, const char* str) {
    for(int i = 0; i < size; i++) {
        if(strcmp(arr[i], str) == 0) return true;
    }
    return false;
}

int distinctSubstrings(const char* text) {
    int n = strlen(text);
    char result[MAX_RESULT][2001];
    int resultSize = 0;
    char temp[2001];
    
    // Check all possible substrings
    for(int len = 2; len <= n; len += 2) {
        for(int i = 0; i + len <= n; i++) {
            // Copy substring to temp
            strncpy(temp, text + i, len);
            temp[len] = '\\0';
            
            if(len % 2 == 0) {
                int halfLen = len/2;
                if(isEqual(temp, temp + halfLen, halfLen)) {
                    if(!isInArray(result, resultSize, temp)) {
                        strcpy(result[resultSize], temp);
                        resultSize++;
                    }
                }
            }
        }
    }
    return resultSize;
}

int main() {
    // Test cases
    printf("%d\\n", distinctSubstrings("abcabcabc")); // Expected: 3
    printf("%d\\n", distinctSubstrings("leetcodeleetcode")); // Expected: 2
    printf("%d\\n", distinctSubstrings("aa")); // Expected: 1
    printf("%d\\n", distinctSubstrings("aaa")); // Expected: 1
    printf("%d\\n", distinctSubstrings("aabaabaa")); // Expected: 2
    return 0;
}
