#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* longest(const char* s1, const char* s2) {
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }
    bool seen[26] = {false};

    for (size_t i = 0; s1[i] != '\0'; ++i) {
        char c = s1[i];
        if (c < 'a' || c > 'z') {
            return NULL;
        }
        seen[(int)(c - 'a')] = true;
    }
    for (size_t i = 0; s2[i] != '\0'; ++i) {
        char c = s2[i];
        if (c < 'a' || c > 'z') {
            return NULL;
        }
        seen[(int)(c - 'a')] = true;
    }

    int count = 0;
    for (int i = 0; i < 26; ++i) {
        if (seen[i]) {
            count++;
        }
    }

    char* out = (char*)malloc((size_t)count + 1);
    if (out == NULL) {
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < 26; ++i) {
        if (seen[i]) {
            out[idx++] = (char)('a' + i);
        }
    }
    out[idx] = '\0';
    return out;
}

int main(void) {
    const char* tests[][2] = {
        {"xyaabbbccccdefww", "xxxxyyyyabklmopq"},
        {"abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"},
        {"abc", "def"},
        {"", "abcxyz"},
        {"Abc", "def"} /* invalid test case */
    };

    for (int i = 0; i < 5; ++i) {
        const char* a = tests[i][0];
        const char* b = tests[i][1];
        char* res = longest(a, b);
        if (res != NULL) {
            printf("Test %d: longest(\"%s\", \"%s\") -> \"%s\"\n", i + 1, a, b, res);
            free(res);
        } else {
            printf("Test %d: longest(\"%s\", \"%s\") -> Error: invalid input or allocation failure\n", i + 1, a, b);
        }
    }
    return 0;
}