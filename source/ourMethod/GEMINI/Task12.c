#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Calculates the score of a word based on alphabet position.
 * a=1, b=2, etc.
 * @param word The word to score.
 * @return The calculated score.
 */
int calculate_score(const char* word) {
    int score = 0;
    if (word == NULL) {
        return 0;
    }
    for (size_t i = 0; i < strlen(word); ++i) {
        score += word[i] - 'a' + 1;
    }
    return score;
}

/**
 * @brief Finds the highest scoring word in a string.
 * If scores are tied, the word appearing earliest wins.
 * The caller is responsible for freeing the returned string.
 * @param s The input string of words.
 * @return A new dynamically allocated string with the highest scoring word.
 */
char* highestScoringWord(const char* s) {
    if (s == NULL || *s == '\0') {
        char* empty_result = (char*)malloc(1);
        if (empty_result == NULL) return NULL;
        empty_result[0] = '\0';
        return empty_result;
    }

    char* s_copy = (char*)malloc(strlen(s) + 1);
    if (s_copy == NULL) {
        return NULL;
    }
    strcpy(s_copy, s);

    int max_score = -1;
    char* best_word_token = NULL;
    const char* delimiters = " ";

    char* token = strtok(s_copy, delimiters);
    while (token != NULL) {
        int current_score = calculate_score(token);
        if (current_score > max_score) {
            max_score = current_score;
            best_word_token = token;
        }
        token = strtok(NULL, delimiters);
    }
    
    char* result = NULL;
    if (best_word_token != NULL) {
        result = (char*)malloc(strlen(best_word_token) + 1);
        if (result != NULL) {
            strcpy(result, best_word_token);
        }
    } else {
        result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
    }

    free(s_copy);
    return result;
}

int main() {
    const char* testCases[] = {
        "man i need a taxi up to dublin",
        "what time are we climbing up the volcano",
        "take me to semynak",
        "aa b",
        "b aa"
    };
    const char* expectedResults[] = {
        "dublin",
        "volcano",
        "semynak",
        "aa",
        "b"
    };
    int num_tests = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < num_tests; i++) {
        char* result = highestScoringWord(testCases[i]);
        printf("Test Case: \"%s\"\n", testCases[i]);
        printf("Expected: %s\n", expectedResults[i]);
        if (result != NULL) {
            printf("Got: %s\n", result);
            printf("Result: %s\n", strcmp(expectedResults[i], result) == 0 ? "PASS" : "FAIL");
            free(result);
        } else {
            printf("Got: NULL\n");
            printf("Result: FAIL (Allocation error)\n");
        }
        printf("\n");
    }

    return 0;
}