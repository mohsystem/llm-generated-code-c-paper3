#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* high(const char* s) {
    static char maxScoreWord[256];
    int maxScore = 0;

    char word[256];
    int index = 0, wordIndex = 0, score = 0;
    
    while (1) {
        char c = s[index++];
        if (c == ' ' || c == '\0') {
            if (score > maxScore) {
                maxScore = score;
                strncpy(maxScoreWord, word, wordIndex);
                maxScoreWord[wordIndex] = '\0';
            }
            wordIndex = 0;
            score = 0;
            if (c == '\0') break;
        } else {
            word[wordIndex++] = c;
            score += c - 'a' + 1;
        }
    }
    
    return maxScoreWord;
}

int main() {
    printf("%s\n", high("abad bcad aced")); // Output: bcad
    printf("%s\n", high("hello world"));   // Output: world
    printf("%s\n", high("this is a test")); // Output: this
    printf("%s\n", high("a bb ccc dddd")); // Output: dddd
    printf("%s\n", high("alpha beta gamma")); // Output: gamma
    return 0;
}