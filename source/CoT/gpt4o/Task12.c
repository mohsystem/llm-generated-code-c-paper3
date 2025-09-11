#include <stdio.h>
#include <string.h>

char* highestScoringWord(const char* input) {
    static char highestWord[256];
    char currentWord[256];
    int highestScore = 0;
    int currentScore = 0;
    int i = 0, j = 0;

    while (1) {
        char c = input[i++];
        if (c == ' ' || c == '\0') {
            currentWord[j] = '\0';
            if (currentScore > highestScore) {
                highestScore = currentScore;
                strcpy(highestWord, currentWord);
            }
            if (c == '\0') break;
            j = 0;
            currentScore = 0;
        } else {
            currentWord[j++] = c;
            currentScore += (c - 'a' + 1);
        }
    }
    return highestWord;
}

int main() {
    printf("%s\n", highestScoringWord("abad zxy")); // Output: abad
    printf("%s\n", highestScoringWord("hello world")); // Output: world
    printf("%s\n", highestScoringWord("java python csharp")); // Output: python
    printf("%s\n", highestScoringWord("a aa aaa aaaa")); // Output: aaaa
    printf("%s\n", highestScoringWord("abc xyz abc")); // Output: abc
    return 0;
}