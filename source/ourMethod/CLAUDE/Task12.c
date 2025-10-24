#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

// Security: Maximum lengths to prevent buffer overflow and DoS
#define MAX_INPUT_LENGTH 1000000
#define MAX_WORD_LENGTH 1000
#define MAX_WORDS 10000

// Security: Validate character is lowercase letter
bool isValidLowercase(char c) {
    return c >= 'a' && c <= 'z';
}

// Security: Safe score calculation with overflow protection
bool calculateWordScore(const char *word, size_t wordLen, uint32_t *score) {
    // Security: Validate pointers are not NULL
    if (word == NULL || score == NULL) {
        return false;
    }

    // Security: Validate word length
    if (wordLen == 0) {
        *score = 0;
        return true;
    }

    // Security: Check maximum possible score won't overflow
    if (wordLen > UINT32_MAX / 26) {
        return false;
    }

    *score = 0;

    // Security: Bounds-checked loop with length validation
    for (size_t i = 0; i < wordLen; ++i) {
        // Security: Validate each character is lowercase letter
        if (!isValidLowercase(word[i])) {
            return false;
        }

        uint32_t charScore = (uint32_t)(word[i] - 'a' + 1);

        // Security: Check for overflow before addition
        if (*score > UINT32_MAX - charScore) {
            return false;
        }

        *score += charScore;
    }

    return true;
}

// Security: Safe string copy with bounds checking
bool safeCopy(char *dest, size_t destSize, const char *src, size_t srcLen) {
    // Security: Validate pointers and sizes
    if (dest == NULL || src == NULL || destSize == 0) {
        return false;
    }

    // Security: Ensure destination has room for null terminator
    if (srcLen >= destSize) {
        return false;
    }

    // Security: Use memcpy with validated length
    memcpy(dest, src, srcLen);
    dest[srcLen] = '\0'; // Ensure null termination

    return true;
}

char *highestScoringWord(const char *input) {
    // Security: Validate input pointer
    if (input == NULL) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t inputLen = strlen(input);

    // Security: Validate input length to prevent DoS
    if (inputLen > MAX_INPUT_LENGTH) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    // Security: Allocate result buffer
    char *highestWord = (char *)malloc(MAX_WORD_LENGTH + 1);
    if (highestWord == NULL) {
        return NULL; // Memory allocation failed
    }
    highestWord[0] = '\0'; // Initialize to empty string

    uint32_t highestScore = 0;
    bool foundValid = false;

    size_t wordStart = 0;
    size_t i = 0;

    // Security: Bounds-checked parsing loop
    while (i <= inputLen) {
        // Word boundary: space or end of string
        if (i == inputLen || input[i] == ' ') {
            size_t wordLen = i - wordStart;

            // Security: Validate word length
            if (wordLen > 0 && wordLen <= MAX_WORD_LENGTH) {
                uint32_t currentScore = 0;

                // Security: Safe score calculation with validation
                if (calculateWordScore(&input[wordStart], wordLen, &currentScore)) {
                    // First valid word or higher score found
                    if (!foundValid || currentScore > highestScore) {
                        // Security: Safe copy with bounds checking
                        if (safeCopy(highestWord, MAX_WORD_LENGTH + 1,
                                     &input[wordStart], wordLen)) {
                            highestScore = currentScore;
                            foundValid = true;
                        }
                    }
                }
            }

            // Move to next word
            wordStart = i + 1;
        }

        ++i;
    }

    return highestWord;
}

int main(void) {
    // Test case 1: Basic example
    char *result1 = highestScoringWord("man i need a taxi up to ubud");
    printf("Test 1: \"%s\"\n", result1 ? result1 : "NULL");
    free(result1); // Security: Free allocated memory

    // Test case 2: Single word
    char *result2 = highestScoringWord("hello");
    printf("Test 2: \"%s\"\n", result2 ? result2 : "NULL");
    free(result2);

    // Test case 3: Same score, return first
    char *result3 = highestScoringWord("aa b");
    printf("Test 3: \"%s\"\n", result3 ? result3 : "NULL");
    free(result3);

    // Test case 4: Different scores
    char *result4 = highestScoringWord("a bb ccc");
    printf("Test 4: \"%s\"\n", result4 ? result4 : "NULL");
    free(result4);

    // Test case 5: Empty string edge case
    char *result5 = highestScoringWord("");
    printf("Test 5: \"%s\"\n", result5 ? result5 : "NULL");
    free(result5);

    return 0;
}
