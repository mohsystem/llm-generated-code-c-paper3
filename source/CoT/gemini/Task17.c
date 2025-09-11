#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *toJadenCase(char *phrase) {
    if (phrase == NULL || strlen(phrase) == 0) {
        return NULL;
    }

    char *result = (char *)malloc(strlen(phrase) * 2 + 1); // Allocate sufficient memory
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    char *word;
    char *saveptr;
    
    strcpy(result, "");

    word = strtok_r(phrase, " ", &saveptr);
    while (word != NULL) {
        if (strlen(word) > 0) {
            word[0] = toupper(word[0]);
            strcat(result, word);
            strcat(result, " ");
        }
        word = strtok_r(NULL, " ", &saveptr);
    }
    if (strlen(result) > 0) {
        result[strlen(result) - 1] = '\0'; // Remove trailing space
    }


    return result;
}

int main() {
    char *testCases[] = {
        "How can mirrors be real if our eyes aren't real",
        "most trees are blue",
        "",
        "the moment that truth is organized it becomes a lie"
    };
    char *expected[] = {
        "How Can Mirrors Be Real If Our Eyes Aren't Real",
        "Most Trees Are Blue",
        NULL,
        "The Moment That Truth Is Organized It Becomes A Lie"
    };

    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char *phrase_copy = strdup(testCases[i]); // Create a copy to avoid modifying the original string
        char *result = toJadenCase(phrase_copy);
        printf("Test case %d: %s %s\n", i + 1, (result == NULL) ? "NULL" : result,
               (result == NULL) ? ((expected[i] == NULL) ? "(PASS)" : "(FAIL)")
                                : (strcmp(result, expected[i]) == 0) ? "(PASS)" : "(FAIL)");

        free(phrase_copy); // Free the copy
        free(result); // Free the allocated memory
    }

    return 0;
}