
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Maximum expected input length based on constraints
#define MAX_TEXT_LENGTH 2000
// Maximum possible distinct substrings (conservative upper bound)
#define MAX_DISTINCT_SUBSTRINGS 4000

// Structure to store distinct substrings
typedef struct {
    char** substrings;
    int count;
    int capacity;
} SubstringSet;

// Initialize substring set with proper memory allocation and validation
// Returns NULL on allocation failure
SubstringSet* createSubstringSet(int initialCapacity) {
    // Validate capacity to prevent integer overflow
    if (initialCapacity <= 0 || initialCapacity > MAX_DISTINCT_SUBSTRINGS) {
        return NULL;
    }
    
    SubstringSet* set = (SubstringSet*)malloc(sizeof(SubstringSet));
    if (set == NULL) {
        return NULL;
    }
    
    // Initialize all fields before allocation to ensure safe cleanup on failure
    set->substrings = NULL;
    set->count = 0;
    set->capacity = initialCapacity;
    
    set->substrings = (char**)calloc(initialCapacity, sizeof(char*));
    if (set->substrings == NULL) {
        free(set);
        return NULL;
    }
    
    // Initialize all pointers to NULL for safe cleanup
    for (int i = 0; i < initialCapacity; i++) {
        set->substrings[i] = NULL;
    }
    
    return set;
}

// Check if substring already exists in set
// Prevents buffer overruns by validating string lengths
bool containsSubstring(const SubstringSet* set, const char* str, size_t len) {
    if (set == NULL || str == NULL || len == 0) {
        return false;
    }
    
    for (int i = 0; i < set->count; i++) {
        if (set->substrings[i] != NULL && strlen(set->substrings[i]) == len) {
            // Safe comparison: both strings are null-terminated and length validated
            if (strncmp(set->substrings[i], str, len) == 0) {
                return true;
            }
        }
    }
    return false;
}

// Add substring to set if not already present
// Returns true on success, false on failure or duplicate
bool addSubstring(SubstringSet* set, const char* str, size_t len) {
    if (set == NULL || str == NULL || len == 0 || len > MAX_TEXT_LENGTH) {
        return false;
    }
    
    // Check if already exists
    if (containsSubstring(set, str, len)) {
        return true;
    }
    
    // Check capacity to prevent overflow
    if (set->count >= set->capacity) {
        return false;
    }
    
    // Allocate memory for new substring (len + 1 for null terminator)
    // Check for integer overflow
    if (len >= SIZE_MAX - 1) {
        return false;
    }
    
    set->substrings[set->count] = (char*)malloc(len + 1);
    if (set->substrings[set->count] == NULL) {
        return false;
    }
    
    // Safe copy with explicit bounds checking
    memcpy(set->substrings[set->count], str, len);
    set->substrings[set->count][len] = '\\0';
    set->count++;
    
    return true;
}

// Free all memory associated with substring set
// Ensures no memory leaks and prevents double-free
void freeSubstringSet(SubstringSet* set) {
    if (set == NULL) {
        return;
    }
    
    if (set->substrings != NULL) {
        for (int i = 0; i < set->capacity; i++) {
            if (set->substrings[i] != NULL) {
                // Clear sensitive data before freeing (defense in depth)
                memset_s(set->substrings[i], strlen(set->substrings[i]), 0, strlen(set->substrings[i]));
                free(set->substrings[i]);
                set->substrings[i] = NULL;
            }
        }
        free(set->substrings);
        set->substrings = NULL;
    }
    
    free(set);
}
// Main function to count distinct echo substrings
// All inputs validated, bounds checked, memory properly managed
int distinctEchoSubstrings(const char* text) {
    // Input validation: check for NULL and empty string
    if (text == NULL) {
        return 0;
    }

    size_t n = strlen(text);

    // Validate length constraints
    if (n == 0 || n > MAX_TEXT_LENGTH) {
        return 0;
    }

    // Validate that text contains only lowercase English letters
    for (size_t i = 0; i < n; i++) {
        if (text[i] < 'a' || text[i] > 'z') {
            return 0;
        }
    }

    // Create set to store distinct substrings
    SubstringSet* set = createSubstringSet(MAX_DISTINCT_SUBSTRINGS);
    if (set == NULL) {
        return 0;
    }

    // Iterate through all possible starting positions
    for (size_t i = 0; i < n; i++) {
        // Iterate through all possible lengths of the repeating part
        // Prevent integer overflow: check i + 2*len <= n
        for (size_t len = 1; len <= (n - i) / 2; len++) {
            // Bounds validation: ensure we don't read beyond buffer
            if (i + 2 * len > n) {
                break;
            }

            // Compare the two halves for equality
            // Safe: both ranges are within bounds due to checks above
            if (memcmp(text + i, text + i + len, len) == 0) {
                // Allocate temporary buffer for the echo substring
                // Check for integer overflow
                if (2 * len >= SIZE_MAX - 1) {
                    continue;
                }

                char* echoSubstr = (char*)malloc(2 * len + 1);
                if (echoSubstr == NULL) {
                    freeSubstringSet(set);
                    return 0;
                }

                // Safe copy: bounds are validated
                memcpy(echoSubstr, text + i, 2 * len);
                echoSubstr[2 * len] = '\0';

                // Add to set (handles duplicates internally)
                addSubstring(set, echoSubstr, 2 * len);

                // Clear and free temporary buffer
                memset_s(echoSubstr, 2 * len, 0, 2 * len);
                free(echoSubstr);
            }
        }
    }

    int result = set->count;
    freeSubstringSet(set);

    return result;
}

// Test cases
int main() {
    // Test case 1
    const char* test1 = "abcabcabc";
    printf("Test 1: %d (expected 3)\\n", distinctEchoSubstrings(test1));
    
    // Test case 2
    const char* test2 = "leetcodeleetcode";
    printf("Test 2: %d (expected 2)\\n", distinctEchoSubstrings(test2));
    
    // Test case 3
    const char* test3 = "aaaa";
    printf("Test 3: %d (expected 2)\\n", distinctEchoSubstrings(test3));
    
    // Test case 4
    const char* test4 = "abcdef";
    printf("Test 4: %d (expected 0)\\n", distinctEchoSubstrings(test4));
    
    // Test case 5
    const char* test5 = "a";
    printf("Test 5: %d (expected 0)\\n", distinctEchoSubstrings(test5));
    
    return 0;
}
