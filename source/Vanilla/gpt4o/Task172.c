#include <stdio.h>
#include <string.h>

int countDistinctConcatSubstrings(const char* text) {
    int count = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j += 2) {
            int mid = (i + j + 1) / 2;
            if (strncmp(&text[i], &text[mid], mid - i) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    printf("%d\n", countDistinctConcatSubstrings("abcabcabc")); // 3
    printf("%d\n", countDistinctConcatSubstrings("leetcodeleetcode")); // 2
    printf("%d\n", countDistinctConcatSubstrings("aaaa")); // 3
    printf("%d\n", countDistinctConcatSubstrings("ababab")); // 3
    printf("%d\n", countDistinctConcatSubstrings("aabb")); // 0
    return 0;
}