#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **lines;
    size_t count;
    int error; /* 0 = OK, nonzero = error */
} NumberedResult;

static size_t count_digits(size_t n) {
    size_t d = 0;
    do {
        d++;
        n /= 10;
    } while (n != 0);
    return d;
}

static void free_numbered_result(NumberedResult *r) {
    if (!r) return;
    if (r->lines) {
        for (size_t i = 0; i < r->count; ++i) {
            free(r->lines[i]);
        }
        free(r->lines);
    }
    r->lines = NULL;
    r->count = 0;
    r->error = 0;
}

static NumberedResult number_lines(const char *const *lines, size_t count) {
    NumberedResult result;
    result.lines = NULL;
    result.count = 0;
    result.error = 0;

    if (count > 0 && lines == NULL) {
        result.error = 1;
        return result;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lines[i] == NULL) {
            result.error = 2;
            return result;
        }
    }

    if (count == 0) {
        result.lines = NULL;
        result.count = 0;
        result.error = 0;
        return result;
    }

    char **out = (char **)calloc(count, sizeof(char *));
    if (!out) {
        result.error = 3;
        return result;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *s = lines[i];
        size_t num = i + 1;
        size_t digits = count_digits(num);
        size_t slen = strlen(s);
        size_t outlen = digits + 2 + slen; /* "n: " + s */
        char *buf = (char *)calloc(outlen + 1, 1);
        if (!buf) {
            /* free already allocated */
            for (size_t j = 0; j < i; ++j) free(out[j]);
            free(out);
            result.error = 4;
            return result;
        }
        int written = snprintf(buf, outlen + 1, "%zu: %s", num, s);
        if (written < 0 || (size_t)written > outlen) {
            free(buf);
            for (size_t j = 0; j < i; ++j) free(out[j]);
            free(out);
            result.error = 5;
            return result;
        }
        out[i] = buf;
    }

    result.lines = out;
    result.count = count;
    result.error = 0;
    return result;
}

static void print_result(const NumberedResult *r) {
    if (r->error != 0) {
        printf("Error: %d\n", r->error);
        return;
    }
    printf("[");
    for (size_t i = 0; i < r->count; ++i) {
        printf("\"%s\"", r->lines[i]);
        if (i + 1 < r->count) printf(", ");
    }
    printf("]\n");
}

int main(void) {
    /* 5 test cases */

    /* Test 1: empty */
    const char *t1[] = {};
    NumberedResult r1 = number_lines(t1, 0);
    printf("Test 1: ");
    print_result(&r1);
    free_numbered_result(&r1);

    /* Test 2: simple a,b,c */
    const char *t2[] = {"a", "b", "c"};
    NumberedResult r2 = number_lines(t2, 3);
    printf("Test 2: ");
    print_result(&r2);
    free_numbered_result(&r2);

    /* Test 3: empty string and x */
    const char *t3[] = {"", "x"};
    NumberedResult r3 = number_lines(t3, 2);
    printf("Test 3: ");
    print_result(&r3);
    free_numbered_result(&r3);

    /* Test 4: spaces and colons */
    const char *t4[] = {"one line with spaces", "two:with:colons"};
    NumberedResult r4 = number_lines(t4, 2);
    printf("Test 4: ");
    print_result(&r4);
    free_numbered_result(&r4);

    /* Test 5: misc characters */
    const char *t5[] = {"emoji 😀", "multibyte 字", "punctuation!?", "tabs\tand\nnewlines"};
    NumberedResult r5 = number_lines(t5, 4);
    printf("Test 5: ");
    print_result(&r5);
    free_numbered_result(&r5);

    return 0;
}