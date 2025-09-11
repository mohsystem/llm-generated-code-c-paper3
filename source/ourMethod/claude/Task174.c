
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestPalindrome(const char* s) {
    if (!s || strlen(s) <= 1) {
        char* result = (char*)malloc(strlen(s) + 1);
        if (result) {
            strcpy(result, s);
        }
        return result;
    }
    
    // Create temp string
    int sLen = strlen(s);
    int tempLen = 2 * sLen + 1;
    char* temp = (char*)malloc(tempLen + 1);
    if (!temp) return NULL;
    
    // Copy s to temp
    strcpy(temp, s);
    temp[sLen] = '#';
    
    // Add reverse of s
    for (int i = 0; i < sLen; i++) {
        temp[sLen + 1 + i] = s[sLen - 1 - i];
    }
    temp[tempLen] = '\\0';
    
    // Compute KMP pattern array
    int* lps = (int*)calloc(tempLen, sizeof(int));
    if (!lps) {
        free(temp);
        return NULL;
    }
    
    for (int i = 1, len = 0; i < tempLen;) {
        if (temp[i] == temp[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    int longest = lps[tempLen - 1];
    
    // Create result string
    char* result = (char*)malloc(2 * sLen - longest + 1);
    if (!result) {
        free(temp);
        free(lps);
        return NULL;
    }
    
    int idx = 0;
    // Add remaining characters in reverse
    for (int i = sLen - 1; i >= longest; i--) {
        result[idx++] = s[i];
    }
    // Add original string
    strcpy(result + idx, s);
    
    free(temp);
    free(lps);
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {"aacecaaa", "abcd", "", "a", "aa"};
    int numTests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("Input: %s\\n", tests[i]);
        char* result = shortestPalindrome(tests[i]);
        if (result) {
            printf("Output: %s\\n\\n", result);
            free(result);
        }
    }
    
    return 0;
}
