#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Reverses a substring in place.
 * 
 * @param start Pointer to the start of the substring.
 * @param end Pointer to the end of the substring.
 */
void reverse_substring(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

/**
 * @brief Reverses words with five or more letters in a given string.
 *        The caller is responsible for freeing the returned string.
 *
 * @param sentence The input string of one or more words.
 * @return A new dynamically allocated string with the modifications, or NULL on error.
 */
char* spinWords(const char* sentence) {
    if (sentence == NULL) {
        return NULL;
    }

    size_t len = strlen(sentence);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    // Copy the original string to the result buffer to work on a mutable copy
    // and preserve original spacing.
    memcpy(result, sentence, len + 1);

    char* word_start = result;
    for (char* p = result; ; ++p) {
        if (isspace((unsigned char)*p) || *p == '\0') {
            // Found the end of a word or the end of the string
            if (p > word_start) {
                size_t word_len = p - word_start;
                if (word_len >= 5) {
                    reverse_substring(word_start, p - 1);
                }
            }
            if (*p == '\0') {
                break; // End of the entire string
            }
            // Start of the next word is after the current space
            word_start = p + 1;
        }
    }

    return result;
}

int main() {
    const char* testCases[] = {
        "Hey fellow warriors",
        "This is a test",
        "This is another test",
        "Welcome",
        "Just kidding there is still one more"
    };

    const char* expectedResults[] = {
        "Hey wollef sroirraw",
        "This is a test",
        "This is rehtona test",
        "emocleW",
        "Just gniddik ereht is llits one more"
    };

    int num_tests = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < num_tests; i++) {
        char* result = spinWords(testCases[i]);
        if (result == NULL) {
            printf("Test Case %d: FAILED (Memory allocation error)\n", i + 1);
            continue;
        }
        
        printf("Test Case %d:\n", i + 1);
        printf("Input:    \"%s\"\n", testCases[i]);
        printf("Output:   \"%s\"\n", result);
        printf("Expected: \"%s\"\n", expectedResults[i]);
        printf("Result: %s\n", strcmp(result, expectedResults[i]) == 0 ? "PASS" : "FAIL");
        printf("\n");

        free(result); // Free the allocated memory
    }

    return 0;
}