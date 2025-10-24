#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 100000

static bool is_ascii_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char* spin_words(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = strlen(s);
    if (len < 1 || len > MAX_LEN) {
        return NULL;
    }

    // Validate characters: only spaces and ASCII letters
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (!(c == ' ' || is_ascii_letter(c))) {
            return NULL;
        }
    }

    char* out = (char*)malloc(len + 1);
    if (!out) {
        return NULL;
    }

    size_t in_i = 0;
    size_t out_i = 0;

    while (in_i < len) {
        char c = s[in_i];
        if (c == ' ') {
            out[out_i++] = ' ';
            in_i++;
            continue;
        }

        if (!is_ascii_letter(c)) {
            free(out);
            return NULL;
        }

        size_t start = in_i;
        while (in_i < len && is_ascii_letter(s[in_i])) {
            in_i++;
        }
        size_t wlen = in_i - start;

        if (wlen >= 5) {
            for (size_t j = 0; j < wlen; j++) {
                out[out_i + j] = s[start + (wlen - 1 - j)];
            }
        } else {
            memcpy(out + out_i, s + start, wlen);
        }
        out_i += wlen;
    }

    out[out_i] = '\0';
    return out;
}

int main(void) {
    const char* tests[5] = {
        "Hey fellow warriors",
        "This is a test",
        "This is another test",
        "spin",
        "Spinning works right now"
    };

    for (int i = 0; i < 5; i++) {
        char* res = spin_words(tests[i]);
        if (res == NULL) {
            printf("ERROR\n");
        } else {
            printf("%s\n", res);
            free(res);
        }
    }

    return 0;
}