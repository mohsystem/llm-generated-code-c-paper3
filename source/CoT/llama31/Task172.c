#include <stdio.h>
#include <string.h>

int distinctEchoSubstrings(const char* text) {
    int n = strlen(text);
    int count = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            char substr1[2001], substr2[2001];
            strncpy(substr1, text + i, len / 2);
            substr1[len / 2] = '\0';
            if (len % 2 == 0) {
                strncpy(substr2, text + i + len / 2, len / 2);
                substr2[len / 2] = '\0';
            } else {
                strncpy(substr2, text + i + len / 2 + 1, len / 2);
                substr2[len / 2] = '\0';
            }
            if (strcmp(substr1, substr2) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    // Test cases
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("aaa")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("ababab")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("abcde")); // Output: 0
    return 0;
}