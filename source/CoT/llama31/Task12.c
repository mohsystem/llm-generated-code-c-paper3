#include <stdio.h>
#include <string.h>

char* highestScoringWord(char* inputString) {
    char* token = strtok(inputString, " ");
    int maximumScore = 0;
    char* maxScoreWord = NULL;

    while (token != NULL) {
        int currScore = 0;
        for (int i = 0; i < strlen(token); i++) {
            currScore += token[i] - 'a' + 1;
        }
        if (currScore > maximumScore) {
            maximumScore = currScore;
            maxScoreWord = token;
        }
        token = strtok(NULL, " ");
    }
    return maxScoreWord;
}

int main() {
    char testCases[][100] = {
        "abad abad abad",
        "abc def ghi",
        "xyz abc def",
        "a b c d e f g h i j k l m n o p q r s t u v w x y z",
        "aa bb cc dd"
    };

    for (int i = 0; i < 5; i++) {
        char inputString[100];
        strcpy(inputString, testCases[i]);
        printf("Input: %s\n", inputString);
        printf("Highest Scoring Word: %s\n\n", highestScoringWord(inputString));
    }

    return 0;
}