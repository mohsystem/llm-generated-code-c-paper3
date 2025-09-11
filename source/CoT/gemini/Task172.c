#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for a substring
typedef struct {
    char *str;
    int len;
} Substring;

// Function to check if a substring is a concatenation of itself
int isConcatenated(const char *str, int len) {
    if (len % 2 != 0) {
        return 0;
    }
    int halfLen = len / 2;
    return memcmp(str, str + halfLen, halfLen) == 0;
}

// Function to compare substrings for uniqueness
int compareSubstrings(const void *a, const void *b) {
    Substring *subA = (Substring *)a;
    Substring *subB = (Substring *)b;
    if (subA->len != subB->len) {
        return subA->len - subB->len;
    }
    return strcmp(subA->str, subB->str);
}


int distinctConcatenatedStrings(const char *text) {
    int n = strlen(text);
    Substring *substrings = (Substring *)malloc(n * n * sizeof(Substring)); 
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int len = j - i;
            char *sub = (char *)malloc((len + 1) * sizeof(char));
            strncpy(sub, text + i, len);
            sub[len] = '\0';

            if (isConcatenated(sub, len)) {
                substrings[count].str = sub;
                substrings[count].len = len;
                count++;
            }
        }
    }


    qsort(substrings, count, sizeof(Substring), compareSubstrings);

    int distinctCount = 0;
    if (count > 0) {
        distinctCount = 1;
        for (int i = 1; i < count; i++) {
            if (strcmp(substrings[i].str, substrings[i - 1].str) != 0) {
                distinctCount++;
            }
        }
    }


    for (int i = 0; i < count; i++) {
        free(substrings[i].str);
    }
    free(substrings);

    return distinctCount;
}

int main() {
    printf("%d\n", distinctConcatenatedStrings("abcabcabc")); // 3
    printf("%d\n", distinctConcatenatedStrings("leetcodeleetcode")); // 2
    printf("%d\n", distinctConcatenatedStrings("aaaa")); // 2
    printf("%d\n", distinctConcatenatedStrings("abc")); // 0
    printf("%d\n", distinctConcatenatedStrings("abababab")); // 3
    return 0;
}