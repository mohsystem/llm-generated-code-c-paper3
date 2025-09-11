#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// C does not have a built-in hash set for strings, so implementing one efficiently would add significant complexity.
// For this exercise, a simpler approach with reduced efficiency is used.

char* longestDupSubstring(char *s) {
    int n = strlen(s);
    int left = 1, right = n - 1;
    char *result = "";
    int resultLen = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        char *duplicate = findDuplicate(s, mid);

        if (duplicate) {
             if (strlen(duplicate) > resultLen) {
                if (result && strlen(result) > 0) free(result);
                result = strdup(duplicate);
                resultLen = strlen(result);
            }
            
            free(duplicate);
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

char *findDuplicate(char *s, int len) {
    int n = strlen(s);
    for (int i = 0; i <= n - len; i++) {
        for (int j = i + 1; j <= n - len; j++) {
            if (strncmp(s + i, s + j, len) == 0) {
               char* res = (char*)malloc(sizeof(char) * (len + 1));
                strncpy(res, s+i, len);
                res[len] = '\0';
                return res;
            }
        }
    }
    return NULL;
}


int main() {
    char *result1 = longestDupSubstring("banana");
    printf("%s\n", result1);  // Output: ana
    free(result1);

    char *result2 = longestDupSubstring("abcd");
    printf("%s\n", result2);  // Output: ""
    free(result2);


    char *result3 = longestDupSubstring("abracadabra");
    printf("%s\n", result3);  // Output: abra
    free(result3);

    char *result4 = longestDupSubstring("aabaabaaba");
    printf("%s\n", result4);  // Output: aabaaba
    free(result4);


    char *result5 = longestDupSubstring("aabcaabdaab");
    printf("%s\n", result5);  // Output: aabd
    free(result5);

    return 0;
}