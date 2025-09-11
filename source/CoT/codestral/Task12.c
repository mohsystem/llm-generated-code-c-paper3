#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* highestScoringWord(const char* s) {
    char* word = strtok((char*)s, " ");
    int maxScore = 0;
    char* maxWord = NULL;
    while (word != NULL) {
        int score = 0;
        for (int i = 0; i < strlen(word); i++) {
            score += word[i] - 'a' + 1;
        }
        if (score > maxScore) {
            maxScore = score;
            maxWord = word;
        }
        word = strtok(NULL, " ");
    }
    return maxWord;
}

int main() {
    printf("%s\n", highestScoringWord("abc def ghi"));  // Output: "ghi"
    printf("%s\n", highestScoringWord("abc zyx def"));  // Output: "zyx"
    printf("%s\n", highestScoringWord("abc abd def"));  // Output: "abc"
    printf("%s\n", highestScoringWord("aa b"));  // Output: "aa"
    printf("%s\n", highestScoringWord("bb ddd zzzz"));  // Output: "bb"
    return 0;
}