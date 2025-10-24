#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static char* expanded_form(unsigned long long n) {
    if (n == 0ULL) {
        return NULL; /* Input must be > 0 */
    }

    char numbuf[32];
    int len = snprintf(numbuf, sizeof(numbuf), "%llu", (unsigned long long)n);
    if (len <= 0 || len >= (int)sizeof(numbuf)) {
        return NULL; /* Fail closed on formatting error or overflow */
    }
    if (len > 20) {
        return NULL; /* Input too large per constraints */
    }

    size_t d = (size_t)len;
    size_t terms = 0;
    size_t sumZeros = 0;
    for (size_t i = 0; i < d; ++i) {
        if (numbuf[i] != '0') {
            terms++;
            sumZeros += (d - 1 - i);
        }
    }
    if (terms == 0) {
        return NULL; /* Should not happen for n > 0 */
    }

    size_t totalLen = terms + sumZeros + (terms > 1 ? 3 * (terms - 1) : 0) + 1; /* +1 for '\0' */
    char* out = (char*)malloc(totalLen);
    if (!out) {
        return NULL;
    }

    size_t pos = 0;
    size_t writtenTerms = 0;
    for (size_t i = 0; i < d; ++i) {
        if (numbuf[i] != '0') {
            if (writtenTerms > 0) {
                out[pos++] = ' ';
                out[pos++] = '+';
                out[pos++] = ' ';
            }
            out[pos++] = numbuf[i];
            size_t zeros = d - 1 - i;
            for (size_t z = 0; z < zeros; ++z) {
                out[pos++] = '0';
            }
            writtenTerms++;
        }
    }
    out[pos] = '\0';
    return out;
}

int main(void) {
    unsigned long long tests[5] = {12ULL, 42ULL, 70304ULL, 9000000ULL, 105ULL};
    for (size_t i = 0; i < 5; ++i) {
        char* res = expanded_form(tests[i]);
        if (res) {
            printf("%llu -> %s\n", tests[i], res);
            free(res);
        } else {
            printf("Error for input %llu\n", tests[i]);
        }
    }
    return 0;
}