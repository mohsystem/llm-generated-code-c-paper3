#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 10000

static bool is_ascii_letter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char* accum(const char* s) {
    if (s == NULL) {
        return NULL;
    }
    size_t n = strlen(s);
    if (n > MAX_LEN) {
        return NULL;
    }
    for (size_t i = 0; i < n; ++i) {
        if (!is_ascii_letter(s[i])) {
            return NULL;
        }
    }
    size_t letters = n * (n + 1) / 2;
    size_t separators = (n > 1) ? (n - 1) : 0;
    size_t total = letters + separators;

    char* out = (char*)malloc(total + 1);
    if (out == NULL) {
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char ch = (unsigned char)s[i];
        char upper = (char)toupper(ch);
        char lower = (char)tolower(ch);
        out[pos++] = upper;
        for (size_t k = 0; k < i; ++k) {
            out[pos++] = lower;
        }
        if (i + 1 < n) {
            out[pos++] = '-';
        }
    }
    out[pos] = '\0';
    return out;
}

int main(void) {
    const char* tests[5] = {
        "abcd",
        "RqaEzty",
        "cwAt",
        "Z",
        "abc1" /* invalid */
    };
    for (int i = 0; i < 5; ++i) {
        char* res = accum(tests[i]);
        if (res != NULL) {
            printf("%s\n", res);
            free(res);
        } else {
            printf("ERROR\n");
        }
    }
    return 0;
}