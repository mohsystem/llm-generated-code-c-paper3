#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* try_parse_int(const char* input) {
    if (input == NULL) {
        char* out = (char*)malloc(64);
        if (!out) return NULL;
        snprintf(out, 64, "ERROR: null input");
        return out;
    }

    const char* s = input;
    size_t n = strlen(s);
    size_t start = 0;
    while (start < n && isspace((unsigned char)s[start])) {
        start++;
    }
    if (start == n) {
        char* out = (char*)malloc(64);
        if (!out) return NULL;
        snprintf(out, 64, "ERROR: input length out of range (1..64)");
        return out;
    }
    size_t end = n - 1;
    while (end > start && isspace((unsigned char)s[end])) {
        end--;
    }
    size_t len = end >= start ? (end - start + 1) : 0;
    if (len < 1 || len > 64) {
        char* out = (char*)malloc(64);
        if (!out) return NULL;
        snprintf(out, 64, "ERROR: input length out of range (1..64)");
        return out;
    }

    size_t idx = start;
    int sign = 1;
    if (s[idx] == '+' || s[idx] == '-') {
        sign = (s[idx] == '-') ? -1 : 1;
        idx++;
    }
    if (idx > end) {
        char* out = (char*)malloc(64);
        if (!out) return NULL;
        snprintf(out, 64, "ERROR: no digits found");
        return out;
    }

    long long value = 0;
    const long long INT_MAX_LL = 2147483647LL;
    const long long LIMIT_NEG = 2147483648LL; /* magnitude allowed for negative */

    for (; idx <= end; idx++) {
        char c = s[idx];
        if (c < '0' || c > '9') {
            char* out = (char*)malloc(64);
            if (!out) return NULL;
            snprintf(out, 64, "ERROR: non-digit character encountered");
            return out;
        }
        int d = c - '0';
        if (sign == 1) {
            if (value > (INT_MAX_LL - d) / 10LL) {
                char* out = (char*)malloc(64);
                if (!out) return NULL;
                snprintf(out, 64, "ERROR: integer overflow");
                return out;
            }
        } else {
            if (value > (LIMIT_NEG - d) / 10LL) {
                char* out = (char*)malloc(64);
                if (!out) return NULL;
                snprintf(out, 64, "ERROR: integer underflow");
                return out;
            }
        }
        value = value * 10LL + (long long)d;
    }

    int result = (sign == 1) ? (int)value : (int)(-value);
    char* out = (char*)malloc(64);
    if (!out) return NULL;
    snprintf(out, 64, "OK: %d", result);
    return out;
}

int main(int argc, char* argv[]) {
    const char* tests[5] = {"123", "-42", "0042", "2147483648", "12a"};
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char* res = try_parse_int(argv[i]);
            if (res == NULL) {
                printf("Input: \"%s\" -> ERROR: memory allocation failure\n", argv[i]);
            } else {
                printf("Input: \"%s\" -> %s\n", argv[i], res);
                free(res);
            }
        }
    } else {
        for (int i = 0; i < 5; i++) {
            char* res = try_parse_int(tests[i]);
            if (res == NULL) {
                printf("Input: \"%s\" -> ERROR: memory allocation failure\n", tests[i]);
            } else {
                printf("Input: \"%s\" -> %s\n", tests[i], res);
                free(res);
            }
        }
    }
    return 0;
}