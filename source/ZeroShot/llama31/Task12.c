#include <stdio.h>
#include <string.h>

char* high(char* str) {
    static char highestScoreWord[100];
    int highestScore = 0;
    char* word = strtok(str, " ");
    while (word != NULL) {
        int currentWordScore = 0;
        for (int i = 0; i < strlen(word); i++) {
            currentWordScore += word[i] - 'a' + 1;
        }
        if (currentWordScore > highestScore) {
            highestScore = currentWordScore;
            strcpy(highestScoreWord, word);
        }
        word = strtok(NULL, " ");
    }
    return highestScoreWord;
}

int main() {
    char str1[] = "man i need a taxi up to ubud";
    char str2[] = "what time are we climbing up the volcano";
    char str3[] = "take me to semynak";
    char str4[] = "aa b";
    char str5[] = "bb d";

    printf("%s\n", high(str1)); // taxi
    printf("%s\n", high(str2)); // volcano
    printf("%s\n", high(str3)); // semynak
    printf("%s\n", high(str4)); // aa
    printf("%s\n", high(str5)); // bb

    return 0;
}