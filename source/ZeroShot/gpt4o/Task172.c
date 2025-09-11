#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isEqual(const char *str1, const char *str2, int len) {
    return strncmp(str1, str2, len) == 0;
}

int countDistinctSubstrings(const char *text) {
    int length = strlen(text);
    int result = 0;
    bool seen[2000][2000] = { false };
    
    for (int i = 0; i < length; ++i) {
        for (int len = 2; i + len <= length; len += 2) {
            int halfLen = len / 2;
            if (isEqual(text + i, text + i + halfLen, halfLen) && !seen[i][len]) {
                seen[i][len] = true;
                ++result;
            }
        }
    }
    return result;
}

int main() {
    printf("%d\n", countDistinctSubstrings("abcabcabc"));  // 3
    printf("%d\n", countDistinctSubstrings("leetcodeleetcode"));  // 2
    printf("%d\n", countDistinctSubstrings("aaaa"));  // 3
    printf("%d\n", countDistinctSubstrings("ababab"));  // 3
    printf("%d\n", countDistinctSubstrings("abcd"));  // 0
    return 0;
}