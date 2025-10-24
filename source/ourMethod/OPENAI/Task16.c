#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *s, const char *ending) {
    if (s == NULL || ending == NULL) {
        return false; // Fail closed on invalid input
    }
    size_t slen = strlen(s);
    size_t elen = strlen(ending);
    if (elen > slen) {
        return false;
    }
    // Safe comparison of the last elen bytes
    return memcmp(s + (slen - elen), ending, elen) == 0;
}

int main(void) {
    struct {
        const char *a;
        const char *b;
    } tests[5] = {
        {"abc", "bc"},
        {"abc", "d"},
        {"", ""},
        {"hello", ""},
        {"你好世界", "世界"}
    };

    for (int i = 0; i < 5; ++i) {
        bool res = solution(tests[i].a, tests[i].b);
        printf("solution(\"%s\", \"%s\") = %s\n", tests[i].a, tests[i].b, res ? "true" : "false");
    }
    return 0;
}