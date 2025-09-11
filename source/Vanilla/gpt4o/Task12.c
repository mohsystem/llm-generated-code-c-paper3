#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* highestScoringWord(const char* sentence) {
    static char highestScoringWord[100];
    char word[100];
    int highestScore = 0;
    int currentScore = 0;
    int wordIndex = 0;
    int highestWordIndex = 0;

    while (*sentence) {
        if (*sentence == ' ' || *sentence == '\0') {
            if (currentScore > highestScore) {
                highestScore = currentScore;
                highestWordIndex = wordIndex;
                strcpy(highestScoringWord, word);
            }
            currentScore = 0;
            wordIndex = 0;
        } else {
            currentScore += tolower(*sentence) - 'a' + 1;
            word[wordIndex++] = *sentence;
            word[wordIndex] = '\0';
        }
        sentence++;
    }

    if (currentScore > highestScore) {
        strcpy(highestScoringWord, word);
    }

    return highestScoringWord;
}

int main() {
    printf("%s\n", highestScoringWord("abad zoo")); // Expected: "zoo"
    printf("%s\n", highestScoringWord("a b c")); // Expected: "c"
    printf("%s\n", highestScoringWord("hello world")); // Expected: "world"
    printf("%s\n", highestScoringWord("abc abc")); // Expected: "abc"
    printf("%s\n", highestScoringWord("quiet mood")); // Expected: "quiet"
    return 0;
}