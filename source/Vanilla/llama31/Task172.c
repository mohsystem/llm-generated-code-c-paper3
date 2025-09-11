#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isEcho(const char* text, int start, int end) {
    int len = end - start + 1;
    if (len % 2 == 0) {
        return strncmp(text + start, text + start + len / 2, len / 2) == 0;
    } else {
        return strncmp(text + start, text + start + len / 2 + 1, len / 2) == 0;
    }
}

int distinctEchoSubstrings(const char* text) {
    int n = strlen(text);
    int count = 0;
    bool isDistinct[n];

    for (int i = 0; i < n; i++) {
        isDistinct[i] = false;
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (isEcho(text, i, j)) {
                isDistinct[j] = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (isDistinct[i]) {
            count++;
        }
    }

    return count;
}

int main() {
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // Output: 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("aaa")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("abcdabcd")); // Output: 2
    printf("%d\n", distinctEchoSubstrings("ababab")); // Output: 3
    return 0;
}