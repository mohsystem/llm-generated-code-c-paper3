#include <stdio.h>
#include <string.h>

char* highestScoringWord(const char* sentence) {
    static char highestWord[100];
    int highestScore = 0;
    int currentScore = 0;
    const char* wordStart = sentence;
    const char* c = sentence;
    
    while (*c) {
        if (*c == ' ' || *(c + 1) == '\0') {
            if (*(c + 1) == '\0' && *c != ' ') {
                currentScore += *c - 'a' + 1;
            }
            if (currentScore > highestScore) {
                highestScore = currentScore;
                strncpy(highestWord, wordStart, c - wordStart + (*(c + 1) == '\0'));
                highestWord[c - wordStart + (*(c + 1) == '\0')] = '\0';
            }
            currentScore = 0;
            wordStart = c + 1;
        } else {
            currentScore += *c - 'a' + 1;
        }
        c++;
    }
    
    return highestWord;
}

int main() {
    printf("%s\n", highestScoringWord("abad abc abcd"));
    printf("%s\n", highestScoringWord("a aa aaa"));
    printf("%s\n", highestScoringWord("hello world"));
    printf("%s\n", highestScoringWord("test testing tester"));
    printf("%s\n", highestScoringWord("score scoring scored"));
    return 0;
}