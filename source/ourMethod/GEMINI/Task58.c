#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief Checks if a string has the same amount of 'x's and 'o's, case-insensitive.
 * 
 * @param str The input C-string to check. Must be null-terminated.
 * @return true if the number of 'x's and 'o's are equal, false otherwise.
 */
bool xo(const char *str) {
    if (str == NULL) {
        return true; // A null string has 0 'x's and 0 'o's
    }

    int x_count = 0;
    int o_count = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        // tolower expects an int and its behavior is undefined for values
        // outside the range of unsigned char and EOF. Casting is safe.
        int lower_c = tolower((unsigned char)str[i]);
        if (lower_c == 'x') {
            x_count++;
        } else if (lower_c == 'o') {
            o_count++;
        }
    }
    
    return x_count == o_count;
}

int main() {
    // Test Case 1: "ooxx" -> true
    printf("Test 1 \"ooxx\": %s\n", xo("ooxx") ? "true" : "false");
    // Test Case 2: "xooxx" -> false
    printf("Test 2 \"xooxx\": %s\n", xo("xooxx") ? "true" : "false");
    // Test Case 3: "ooxXm" -> true
    printf("Test 3 \"ooxXm\": %s\n", xo("ooxXm") ? "true" : "false");
    // Test Case 4: "zpzpzpp" -> true
    printf("Test 4 \"zpzpzpp\": %s\n", xo("zpzpzpp") ? "true" : "false");
    // Test Case 5: "zzoo" -> false
    printf("Test 5 \"zzoo\": %s\n", xo("zzoo") ? "true" : "false");

    return 0;
}