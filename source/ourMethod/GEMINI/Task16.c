#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Checks if a string ends with a given suffix.
 * 
 * @param str The main string. Must be a null-terminated C-string.
 * @param ending The potential ending string. Must be a null-terminated C-string.
 * @return true if str ends with ending, false otherwise.
 */
bool solution(const char *str, const char *ending) {
    // Treat null inputs as untrusted and fail safely.
    if (str == NULL || ending == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);

    // If the ending is longer than the string, it can't be a suffix.
    if (ending_len > str_len) {
        return false;
    }
    
    // An empty string is a suffix of any string.
    if (ending_len == 0) {
        return true;
    }

    // Compare the end of 'str' with 'ending'.
    // The starting point for comparison in 'str' is its total length
    // minus the length of the ending.
    const char *suffix_start = str + (str_len - ending_len);
    return strcmp(suffix_start, ending) == 0;
}

int main() {
    // Test Case 1: Standard true case
    printf("Test 1: solution('abc', 'bc') -> %s\n", solution("abc", "bc") ? "true" : "false"); // Expected: true

    // Test Case 2: Standard false case
    printf("Test 2: solution('abc', 'd') -> %s\n", solution("abc", "d") ? "true" : "false"); // Expected: false

    // Test Case 3: Ending is the same as the string
    printf("Test 3: solution('samantha', 'samantha') -> %s\n", solution("samantha", "samantha") ? "true" : "false"); // Expected: true
    
    // Test Case 4: Ending is an empty string
    printf("Test 4: solution('abc', '') -> %s\n", solution("abc", "") ? "true" : "false"); // Expected: true

    // Test Case 5: Main string is shorter than the ending
    printf("Test 5: solution('a', 'abc') -> %s\n", solution("a", "abc") ? "true" : "false"); // Expected: false
    
    return 0;
}