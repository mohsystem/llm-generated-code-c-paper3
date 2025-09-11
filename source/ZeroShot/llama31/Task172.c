#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int distinctEchoSubstrings(const char* text) {
    int n = strlen(text);
    bool isEcho[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            isEcho[i][j] = false;
        }
    }

    int count = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (len % 2 == 0 && strncmp(text + i, text + i + len / 2, len / 2) == 0) {
                isEcho[i][j] = true;
            } else if (len % 2 != 0 && strncmp(text + i, text + i + len / 2 + 1, len / 2) == 0) {
                isEcho[i][j] = true;
            }
        }
    }

    for (int len = 2; len <= n; len += 2) {
        for (int i = 0; i <= n - len; i++) {
            if (isEcho[i][i + len - 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("aaaaaa")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("abababab")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("xyzxyzxyz")); // Output: 1
    return 0;
}