#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int countDistinctSubstrings(const char* text) {
    int n = strlen(text);
    bool isConcat[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            isConcat[i][j] = false;
        }
    }
    int count = 0;

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            char firstHalf[len / 2 + 1];
            char secondHalf[len / 2 + 1];
            strncpy(firstHalf, text + i, len / 2);
            firstHalf[len / 2] = '\0';
            strncpy(secondHalf, text + i + len / 2, len / 2);
            secondHalf[len / 2] = '\0';
            if (len % 2 == 0 && strcmp(firstHalf, secondHalf) == 0) {
                isConcat[i][j] = true;
            } else if (len % 2 != 0) {
                strncpy(firstHalf, text + i, len / 2 + 1);
                firstHalf[len / 2 + 1] = '\0';
                strncpy(secondHalf, text + i + len / 2 + 1, len / 2 + 1);
                secondHalf[len / 2 + 1] = '\0';
                if (strcmp(firstHalf, secondHalf) == 0) {
                    isConcat[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isConcat[i][j] && (j == i || !isConcat[i][j - 1])) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    printf("%d\n", countDistinctSubstrings("abcabcabc"));  // Output: 3
    printf("%d\n", countDistinctSubstrings("leetcodeleetcode"));  // Output: 2
    return 0;
}