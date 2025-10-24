#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Converts a positive integer into its expanded form string.
 * For example: 70304 becomes "70000 + 300 + 4".
 *
 * NOTE: The returned string is dynamically allocated and must be freed by the caller.
 *
 * @param num The positive integer to expand. Must be greater than 0.
 * @return A dynamically allocated string with the expanded form of the number,
 *         or NULL on allocation failure.
 */
char* expandedForm(int num) {
    if (num <= 0) {
        // As per prompt, numbers are > 0. Handle defensively.
        char* empty_str = malloc(1);
        if (empty_str) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    char s_num[25]; // Buffer for integer as string, max long long fits
    snprintf(s_num, sizeof(s_num), "%d", num);
    
    // Allocate a sufficiently large buffer for the result.
    // A 32-bit int has max 10 digits. Max length is for "1 + 10 + 100 + ..."
    // A safe upper bound is len*len + len*3. 512 is very safe.
    char* result = malloc(512);
    if (result == NULL) {
        return NULL; // Malloc failure
    }
    result[0] = '\0';

    bool first_part = true;
    size_t s_len = strlen(s_num);
    
    for (size_t i = 0; i < s_len; i++) {
        if (s_num[i] != '0') {
            if (!first_part) {
                // strcat is safe here due to oversized buffer and fixed-size separator
                strcat(result, " + ");
            }
            
            char part[25]; // Buffer for one part, e.g., "70000"
            part[0] = s_num[i];
            size_t k = 1;
            for (size_t j = 0; j < s_len - 1 - i; j++) {
                part[k++] = '0';
            }
            part[k] = '\0';
            strcat(result, part);
            
            first_part = false;
        }
    }
    
    return result;
}

int main() {
    int test_cases[] = {12, 42, 70304, 9000000, 1};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_cases; i++) {
        char* expanded = expandedForm(test_cases[i]);
        if (expanded) {
            printf("%d -> \"%s\"\n", test_cases[i], expanded);
            free(expanded); // Free the memory allocated by the function
        }
    }

    return 0;
}