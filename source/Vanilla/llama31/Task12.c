#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* highestScoringWord(char* input) {
    char* maxScoreWord = strtok(input, " ");
    int maxScore = 0;

    while (maxScoreWord != NULL) {
        int score = 0;
        for (char* c = maxScoreWord; *c != '\0'; c++) {
            score += *c - 'a' + 1;
        }
        if (score > maxScore) {
            maxScore = score;
            strcpy(input, maxScoreWord);
        }
        maxScoreWord = strtok(NULL, " ");
    }

    return input;
}

int main() {
    char testCases[][100] = {
        "man i need a taxi up to ubud",
        "what time are we climbing up the volcano",
        "take me to semynak",
        "aa b",
        "a b c"
    };

    for (int i = 0; i < 5; i++) {
        printf("Highest scoring word: %s\n", highestScoringWord(testCases[i]));
    }

    return 0;
}