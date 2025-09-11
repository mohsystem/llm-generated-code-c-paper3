
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000
#define MAX_WORD_LENGTH 100

int getWordScore(const char* word) {
    int score = 0;
    for (int i = 0; word[i] != '\\0'; i++) {
        score += (word[i] - 'a' + 1);
    }
    return score;
}

char* highestScoringWord(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return strdup("");
    }

    char* result = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    char temp[MAX_STRING_LENGTH];
    strncpy(temp, str, MAX_STRING_LENGTH - 1);
    temp[MAX_STRING_LENGTH - 1] = '\\0';

    char* word = strtok(temp, " \\t\\n");
    if (word == NULL) {
        free(result);
        return strdup("");
    }

    int maxScore = getWordScore(word);
    strncpy(result, word, MAX_WORD_LENGTH - 1);
    result[MAX_WORD_LENGTH - 1] = '\\0';

    while ((word = strtok(NULL, " \\t\\n")) != NULL) {
        int currentScore = getWordScore(word);
        if (currentScore > maxScore) {
            maxScore = currentScore;
            strncpy(result, word, MAX_WORD_LENGTH - 1);
            result[MAX_WORD_LENGTH - 1] = '\\0';
        }
    }

    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = highestScoringWord("man i need a taxi up to ubud");
    printf("%s\\n", result);  // taxi
    free(result);

    result = highestScoringWord("what time are we climbing up to the volcano");
    printf("%s\\n", result);  // volcano
    free(result);

    result = highestScoringWord("take me to semynak");
    printf("%s\\n", result);  // semynak
    free(result);

    result = highestScoringWord("aa b");
    printf("%s\\n", result);  // aa
    free(result);

    result = highestScoringWord("b aa");
    printf("%s\\n", result);  // b
    free(result);

    return 0;
}
