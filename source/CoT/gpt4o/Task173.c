#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 30000

bool search(const char* s, int len, char* result) {
    char seen[MAX_LEN][MAX_LEN] = {0};
    int seenCount = 0;

    for (int i = 0; i <= strlen(s) - len; ++i) {
        strncpy(result, s + i, len);
        result[len] = '\0';

        for (int j = 0; j < seenCount; ++j) {
            if (strcmp(seen[j], result) == 0) {
                return true;
            }
        }
        strcpy(seen[seenCount++], result);
    }
    return false;
}

char* longestDupSubstring(const char* s) {
    static char result[MAX_LEN] = "";
    int left = 1, right = strlen(s);
    char temp[MAX_LEN];

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (search(s, mid, temp)) {
            strcpy(result, temp);
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // Output: "ana"
    printf("%s\n", longestDupSubstring("abcd"));   // Output: ""
    printf("%s\n", longestDupSubstring("aabbcc")); // Output: "aa"
    printf("%s\n", longestDupSubstring("aaaa"));   // Output: "aaa"
    printf("%s\n", longestDupSubstring("abcabc")); // Output: "abc"
    return 0;
}