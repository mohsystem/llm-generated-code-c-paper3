#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Assuming a maximum phrase length
#define MAX_PHRASE_LENGTH 256

char* toJadenCase(const char* phrase) {
    if (phrase == NULL || strlen(phrase) == 0) {
        return NULL;
    }
    
    char* jadenCase = (char*)malloc(MAX_PHRASE_LENGTH * sizeof(char));
    if (jadenCase == NULL) {
        return NULL; // Handle memory allocation failure
    }
    jadenCase[0] = '\0'; // Initialize as empty string

    char* token = strtok((char*)phrase, " "); // Note: Modifies input string

    while (token != NULL) {
        if (strlen(token) > 0) {
            token[0] = toupper(token[0]);
            strcat(jadenCase, token);
            strcat(jadenCase, " ");
        }
        token = strtok(NULL, " ");
    }

    if (strlen(jadenCase) > 0) {
        jadenCase[strlen(jadenCase) - 1] = '\0'; // Remove trailing space
    }

    return jadenCase;
}

int main() {
    const char* testPhrases[] = {
        "How can mirrors be real if our eyes aren't real",
        "most trees are blue",
        "All The Rules In This World Were Made By Someone No Smarter Than You. So Make Your Own.",
        "",
        NULL
    };

    const char* expected[] = {
       "How Can Mirrors Be Real If Our Eyes Aren't Real",
        "Most Trees Are Blue",
        "All The Rules In This World Were Made By Someone No Smarter Than You. So Make Your Own.",
        NULL,
        NULL
    };
    
    for (int i = 0; i < sizeof(testPhrases) / sizeof(testPhrases[0]); i++) {
        char* result = toJadenCase(testPhrases[i]);
        printf("Test case %d: %s\n", i + 1, result == NULL ? "NULL" : result);
        printf("Expected: %s\n", expected[i] == NULL ? "NULL" : expected[i]);
        if ( (result == NULL && expected[i] == NULL) || (result != NULL && expected[i] != NULL && strcmp(result, expected[i]) == 0) ) {
            printf("true\n");
        }
        else
        {
            printf("false\n");
        }
        if(result!=NULL) free(result); // Free allocated memory
    }

    return 0;
}