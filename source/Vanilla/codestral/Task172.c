#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int distinctEchoSubstrings(char* text) {
    int n = strlen(text);
    bool dp[n][n];
    int count = 0;

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (len % 2 == 0 && (len / 2 <= i || dp[i + 1][i + len / 2 - 1])) {
                dp[i][j] = strncmp(text + i, text + i + len / 2, len / 2) == 0;
                if (dp[i][j]) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // Output: 2
    return 0;
}