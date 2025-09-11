
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RESULT 2000

// Structure to store unique strings
struct StringSet {
    char** strings;
    int count;
};

// Compare function for qsort
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Check if string is already in set
bool isInSet(struct StringSet* set, const char* str) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->strings[i], str) == 0) {
            return true;
        }
    }
    return false;
}

// Add string to set if not already present
void addToSet(struct StringSet* set, const char* str) {
    if (!isInSet(set, str)) {
        set->strings[set->count] = strdup(str);
        set->count++;
    }
}

int countRepeatedSubstrings(const char* text) {
    if (text == NULL || strlen(text) < 2) {
        return 0;
    }
    
    struct StringSet set;
    set.strings = (char**)malloc(MAX_RESULT * sizeof(char*));
    set.count = 0;
    
    int n = strlen(text);
    char* buffer = (char*)malloc((n + 1) * sizeof(char));
    
    // Check all possible substrings of even length
    for (int i = 0; i < n; i++) {
        for (int len = 2; i + len <= n && len % 2 == 0; len += 2) {
            // Create substring
            strncpy(buffer, text + i, len);
            buffer[len] = '\\0';
            
            // Check if first half equals second half
            bool isRepeated = true;
            for (int j = 0; j < len/2; j++) {
                if (buffer[j] != buffer[j + len/2]) {
                    isRepeated = false;
                    break;
                }
            }
            
            if (isRepeated) {
                addToSet(&set, buffer);
            }
        }
    }
    
    // Free allocated memory
    free(buffer);
    int result = set.count;
    for (int i = 0; i < set.count; i++) {
        free(set.strings[i]);
    }
    free(set.strings);
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "abcabcabc",
        "leetcodeleetcode",
        "aa",
        "aabaabaa",
        "abcd"
    };
    int numTests = 5;
    
    for (int i = 0; i < numTests; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Output: %d\\n\\n", countRepeatedSubstrings(tests[i]));
    }
    
    return 0;
}
