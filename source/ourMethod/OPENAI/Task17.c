#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char* to_jaden_case(const char* s) {
    if (s == NULL) {
        return NULL;
    }
    size_t n = strlen(s);
    char* out = (char*)malloc(n + 1);
    if (out == NULL) {
        return NULL;
    }
    bool capitalize = true;
    for (size_t i = 0; i < n; ++i) {
        unsigned char uc = (unsigned char)s[i];
        if (isalpha(uc)) {
            if (capitalize) {
                out[i] = (char)toupper(uc);
                capitalize = false;
            } else {
                out[i] = (char)tolower(uc);
            }
        } else {
            out[i] = s[i];
            if (s[i] == ' ') {
                capitalize = true;
            }
        }
    }
    out[n] = '\0';
    return out;
}

int main(void) {
    const char* tests[5] = {
        "How can mirrors be real if our eyes aren't real",
        "",
        "  leading and trailing  ",
        "don't stop-believin' tEST-inG",
        "\"quoted\" words and  multiple   spaces 123abc test"
    };
    for (int i = 0; i < 5; ++i) {
        const char* input = tests[i];
        char* output = to_jaden_case(input);
        if (output == NULL) {
            printf("Test %d: (null) -> (null)\n", i + 1);
        } else {
            printf("Test %d: %s -> %s\n", i + 1, input, output);
            free(output);
        }
    }
    return 0;
}