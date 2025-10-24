#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief Converts a string to Jaden Case.
 * 
 * @param str The string to convert. Must be a null-terminated string.
 * @return A new dynamically allocated string in Jaden Case. 
 *         The caller is responsible for freeing this memory.
 *         Returns NULL if input is NULL or if memory allocation fails.
 */
char* toJadenCase(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    memcpy(result, str, len + 1); // Use memcpy for efficiency and safety

    bool capitalizeNext = true;
    for (size_t i = 0; i < len; ++i) {
        if (isspace((unsigned char)result[i])) {
            capitalizeNext = true;
        } else if (capitalizeNext && isalpha((unsigned char)result[i])) {
            result[i] = toupper((unsigned char)result[i]);
            capitalizeNext = false;
        }
    }

    return result;
}

int main() {
    const char* testCases[] = {
        "How can mirrors be real if our eyes aren't real",
        "most trees are blue",
        "",
        "the quick brown fox jumps over the lazy dog.",
        "a string   with   multiple   spaces"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    printf("C Test Cases:\n");
    for (int i = 0; i < numTestCases; ++i) {
        char* jadenCased = toJadenCase(testCases[i]);
        if (jadenCased != NULL) {
            printf("Original: \"%s\"\n", testCases[i]);
            printf("Jaden-Cased: \"%s\"\n\n", jadenCased);
            free(jadenCased); // Free the allocated memory
        }
    }

    // Test case for NULL input
    char* nullResult = toJadenCase(NULL);
    printf("Original: NULL\n");
    if (nullResult == NULL) {
        printf("Jaden-Cased: NULL\n\n");
    } else {
        printf("Jaden-Cased: \"%s\"\n\n", nullResult); // Should not happen
        free(nullResult);
    }
    
    return 0;
}