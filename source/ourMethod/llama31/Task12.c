#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* highestScoringWord(char* input) {
    char* token = strtok(input, " ");
    char* maxScoreWord = token;
    int maxScore = calculateWordScore(token);

    while ((token = strtok(NULL, " ")) != NULL) {
        int currentScore = calculateWordScore(token);
        if (currentScore > maxScore) {
            maxScoreWord = token;
            maxScore = currentScore;
        }
    }

    return maxScoreWord;
}

int calculateWordScore(const char* word) {
    int score = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        score += word[i] - 'a' + 1;
    }
    return score;
}

int main() {
    char testCases[][100] = {
        "man i need a taxi up to ubud",
        "what time are we climbing up the volcano",
        "take me to semynak",
        "aa b c d e f g h i j k l m n o p q r s t u v w x y z",
        "abcdefghijklmnopqrstuvwxyz"
    };

    for (int i = 0; i < 5; ++i) {
        printf("Highest scoring word: %s\n", highestScoringWord(testCases[i]));
    }

    return 0;
}