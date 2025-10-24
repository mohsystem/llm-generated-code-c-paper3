#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>

/**
 * @brief Transforms a string based on character position.
 * Example: accum("abcd") -> "A-Bb-Ccc-Dddd"
 * 
 * @param s The input C-string, containing only letters from a..z and A..Z.
 * @return A new dynamically allocated string with the transformation.
 *         The caller is responsible for freeing this memory.
 *         Returns NULL on allocation failure or invalid input.
 */
char* accum(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    size_t n = strlen(s);
    if (n == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    // Calculate output length: n*(n+1)/2 characters + (n-1) hyphens
    // This can overflow for large n.
    size_t char_count = (n % 2 == 0) ? (n / 2) * (n + 1) : n * ((n + 1) / 2);
    size_t hyphen_count = n - 1;
    
    // Check for potential integer overflow before calculating total length
    if (n > 0 && (SIZE_MAX - hyphen_count) < char_count) {
        // Overflow would occur, handle error
        return NULL;
    }
    size_t out_len = char_count + hyphen_count;

    char* result = (char*)malloc(out_len + 1);
    if (result == NULL) {
        return NULL; // Allocation failed
    }

    char* p = result;
    for (size_t i = 0; i < n; i++) {
        if (i > 0) {
            *p++ = '-';
        }
        *p++ = toupper((unsigned char)s[i]);
        for (size_t j = 0; j < i; j++) {
            *p++ = tolower((unsigned char)s[i]);
        }
    }
    *p = '\0'; // Null-terminate

    return result;
}

void run_test(int* test_num, const char* test_input, const char* expected_output) {
    char* result = accum(test_input);
    
    printf("Test case %d: accum(\"%s\")\n", (*test_num)++, test_input);
    printf("Expected: %s\n", expected_output);
    if (result != NULL) {
        printf("Actual  : %s\n", result);
        if (strcmp(result, expected_output) == 0) {
            printf("Result: PASS\n");
        } else {
            printf("Result: FAIL\n");
        }
        free(result); // Free the memory allocated by accum
    } else {
        printf("Actual  : NULL (memory allocation failed or invalid input)\n");
        printf("Result: FAIL\n");
    }
    printf("\n");
}

int main() {
    int test_num = 1;
    run_test(&test_num, "abcd", "A-Bb-Ccc-Dddd");
    run_test(&test_num, "RqaEzty", "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy");
    run_test(&test_num, "cwAt", "C-Ww-Aaa-Tttt");
    run_test(&test_num, "ZpglnRxqenU", "Z-Pp-Ggg-Llll-Nnnnn-Rrrrrr-Xxxxxxx-Qqqqqqqq-Eeeeeeeee-Nnnnnnnnnn-Uuuuuuuuuuu");
    run_test(&test_num, "", "");
    return 0;
}