#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000000UL

char* dna_complement(const char* s) {
    if (s == NULL) {
        return NULL;
    }
    size_t len = strlen(s);
    if (len == 0 || len > MAX_LEN) {
        return NULL;
    }
    char* out = (char*)malloc(len + 1);
    if (out == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)s[i];
        char u = (char)toupper(ch);
        switch (u) {
            case 'A': out[i] = 'T'; break;
            case 'T': out[i] = 'A'; break;
            case 'C': out[i] = 'G'; break;
            case 'G': out[i] = 'C'; break;
            default:
                free(out);
                return NULL;
        }
    }
    out[len] = '\0';
    return out;
}

int main(void) {
    const char* tests[5] = {
        "ATTGC",
        "GTAT",
        "AAAA",
        "CGCGTTAA",
        "acgtACGT"
    };
    for (int i = 0; i < 5; ++i) {
        const char* in = tests[i];
        char* res = dna_complement(in);
        if (res != NULL) {
            printf("Input: %s => Output: %s\n", in, res);
            free(res);
        } else {
            printf("Input: %s => Error: invalid input or processing failure\n", in);
        }
    }
    return 0;
}