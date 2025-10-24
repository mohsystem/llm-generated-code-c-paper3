#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum { MAX_INPUT_LEN = 1024 };

static size_t safe_strnlen_impl(const char *s, size_t maxlen) {
    if (s == NULL) return 0;
    size_t i = 0;
    for (; i < maxlen && s[i] != '\0'; ++i) { /* count safely */ }
    return i;
}

char* process_input(const char* input) {
    if (input == NULL) {
        char* out = (char*)malloc(1);
        if (out != NULL) out[0] = '\0';
        return out;
    }

    size_t in_len = safe_strnlen_impl(input, MAX_INPUT_LEN);
    char* out = (char*)malloc(in_len + 1);
    if (out == NULL) {
        return NULL;
    }

    size_t o = 0;
    int in_space = 1; /* skip leading spaces */
    for (size_t i = 0; i < in_len; ++i) {
        unsigned char ch = (unsigned char)input[i];
        if (isspace(ch)) {
            if (!in_space && o > 0) {
                out[o++] = ' ';
            }
            in_space = 1;
        } else {
            out[o++] = (char)toupper(ch);
            in_space = 0;
        }
        if (o >= in_len) {
            /* out will never exceed in_len, but this is a guard */
            break;
        }
    }
    if (o > 0 && out[o - 1] == ' ') {
        o--;
    }
    out[o] = '\0';
    return out;
}

static void run_tests(void) {
    const char* tests_static[4];
    tests_static[0] = "";
    tests_static[1] = "Hello, World!";
    tests_static[2] = "   multiple   spaces   here    ";
    tests_static[3] = "1234567890";

    /* Generate long test input safely */
    size_t n = 1100;
    char* long_input = (char*)malloc(n + 1);
    if (long_input != NULL) {
        for (size_t i = 0; i < n; ++i) long_input[i] = 'a';
        long_input[n] = '\0';
    }

    for (int i = 0; i < 4; ++i) {
        char* out = process_input(tests_static[i]);
        if (out != NULL) {
            printf("Test %d Input: [%s]\n", i + 1, tests_static[i]);
            printf("Test %d Output: [%s]\n", i + 1, out);
            free(out);
        } else {
            printf("Test %d Output: [allocation failed]\n", i + 1);
        }
    }

    if (long_input != NULL) {
        char* out = process_input(long_input);
        printf("Test 5 Input: [a... (%zu chars)]\n", (size_t)1100);
        if (out != NULL) {
            printf("Test 5 Output: [first 60 chars: %.60s]\n", out);
            free(out);
        } else {
            printf("Test 5 Output: [allocation failed]\n");
        }
        free(long_input);
    } else {
        printf("Test 5 Skipped: allocation failed\n");
    }
}

int main(int argc, char* argv[]) {
    run_tests();

    const char* user_src = NULL;
    char buffer[MAX_INPUT_LEN + 2]; /* +2 to safely hold newline and NUL */

    if (argc > 1) {
        user_src = argv[1];
    } else {
        /* Safe read using fgets with bounded buffer */
        if (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
            /* Remove trailing newline if present */
            size_t len = strcspn(buffer, "\r\n");
            buffer[len] = '\0';
            user_src = buffer;
        }
    }

    if (user_src != NULL) {
        char* result = process_input(user_src);
        if (result != NULL) {
            printf("User Input Output: [%s]\n", result);
            free(result);
        } else {
            fprintf(stderr, "Error: processing failed due to allocation error.\n");
            return 1;
        }
    }

    return 0;
}