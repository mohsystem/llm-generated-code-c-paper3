#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Takes two strings s1 and s2 including only letters from a to z.
 * Returns a new sorted string, the longest possible, containing distinct letters.
 * The caller is responsible for freeing the returned string.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A new dynamically allocated string with the result, or NULL on error.
 */
char* longest(const char* s1, const char* s2) {
    if (s1 == NULL || s2 == NULL) {
        // Return an empty string for NULL inputs to avoid crashing.
        char* empty_str = (char*)malloc(1);
        if (empty_str == NULL) return NULL;
        empty_str[0] = '\0';
        return empty_str;
    }

    bool seen[26] = {false};

    for (size_t i = 0; s1[i] != '\0'; ++i) {
        if (s1[i] >= 'a' && s1[i] <= 'z') {
            seen[s1[i] - 'a'] = true;
        }
    }

    for (size_t i = 0; s2[i] != '\0'; ++i) {
        if (s2[i] >= 'a' && s2[i] <= 'z') {
            seen[s2[i] - 'a'] = true;
        }
    }

    int count = 0;
    for (int i = 0; i < 26; ++i) {
        if (seen[i]) {
            count++;
        }
    }

    char* result = (char*)malloc(count + 1);
    if (result == NULL) {
        return NULL; // Allocation failed
    }

    int index = 0;
    for (int i = 0; i < 26; ++i) {
        if (seen[i]) {
            result[index++] = (char)('a' + i);
        }
    }
    result[index] = '\0';

    return result;
}

void run_test(const char* test_name, const char* s1, const char* s2, const char* expected) {
    printf("%s:\n", test_name);
    printf("s1: \"%s\"\n", s1);
    printf("s2: \"%s\"\n", s2);
    char* result = longest(s1, s2);
    if (result) {
        printf("Result: \"%s\"\n", result);
        printf("Expected: \"%s\"\n", expected);
        free(result); // Free the dynamically allocated memory
    } else {
        printf("Failed to allocate memory for result.\n");
    }
    printf("\n");
}

int main() {
    // Test Case 1
    run_test("Test Case 1", "xyaabbbccccdefww", "xxxxyyyyabklmopq", "abcdefklmopqwxy");
    
    // Test Case 2
    run_test("Test Case 2", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    
    // Test Case 3
    run_test("Test Case 3", "aretheyhere", "yestheyarehere", "aehrsty");

    // Test Case 4
    run_test("Test Case 4", "loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");

    // Test Case 5
    run_test("Test Case 5", "inmanylanguages", "theresapairoffunctions", "acefghilmnoprstu");

    return 0;
}