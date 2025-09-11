#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to store substrings and implement a simple set-like behavior
typedef struct {
    char **substrings;
    int count;
    int size;
} StringSet;

// Function to add a substring to the set (duplicates are ignored)
void addToStringSet(StringSet *set, const char *substring) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->substrings[i], substring) == 0) {
            return; 
        }
    }

    if (set->count == set->size) {
        set->size *= 2; // Resize if needed
        set->substrings = realloc(set->substrings, set->size * sizeof(char *));
    }
    set->substrings[set->count] = strdup(substring); // Allocate memory and copy
    set->count++;
}

int distinctEchoSubstrings(const char *text) {
    StringSet distinctEchoSubstrings;

    // Initialize the set
    distinctEchoSubstrings.count = 0;
    distinctEchoSubstrings.size = 1;  // Start with a small initial size
    distinctEchoSubstrings.substrings = malloc(sizeof(char *));


    int n = strlen(text);
    for (int len = 1; len <= n / 2; len++) {
        for (int i = 0; i <= n - 2 * len; i++) {
            char s1[2001]; // Use a char array instead of dynamically allocated substrings inside loop
            char s2[2001];
            strncpy(s1, text + i, len);
            s1[len] = '\0';
            strncpy(s2, text + i + len, len);
            s2[len] = '\0';

            if (strcmp(s1, s2) == 0) {
                char combined[4002];  // Char array to avoid concatenation-related issues
                strcpy(combined, s1);
                strcat(combined, s2);
                addToStringSet(&distinctEchoSubstrings, combined);
            }
        }
    }

    int result = distinctEchoSubstrings.count;

    // Free allocated memory - VERY IMPORTANT
    for (int i = 0; i < distinctEchoSubstrings.count; i++) {
        free(distinctEchoSubstrings.substrings[i]);
    }
    free(distinctEchoSubstrings.substrings);

    return result;
}

int main() {
    char *testCases[] = {"abcabcabc", "leetcodeleetcode", "abab", "aaa", "aaaba"};
    int expectedOutputs[] = {3, 2, 1, 1, 1};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        int output = distinctEchoSubstrings(testCases[i]);
        printf("Test case %d: %s\n", i + 1, testCases[i]);
        printf("Expected output: %d\n", expectedOutputs[i]);
        printf("Actual output: %d\n", output);
        printf("%s\n\n", (output == expectedOutputs[i] ? "Pass" : "Fail"));
    }
    return 0;
}