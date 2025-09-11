#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* high(char *s) {
    char *word = strtok(s, " ");
    char *highestWord = NULL;
    int highestScore = 0;

    while (word != NULL) {
        int score = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            score += (word[i] - 'a' + 1);
        }
        if (score > highestScore) {
            highestScore = score;
            highestWord = word;
        }
        word = strtok(NULL, " ");
    }
    return highestWord;
}

int main() {
    char s1[] = "man i need a taxi up to ubud";
    char s2[] = "what time are we climbing up the volcano";
    char s3[] = "take me to semynak";
    char s4[] = "aa b";
    char s5[] = "b aa";


    printf("%s\n", high(s1)); // taxi
    printf("%s\n", high(s2)); // volcano
    printf("%s\n", high(s3)); // semynak
    printf("%s\n", high(s4)); // aa
    printf("%s\n", high(s5)); // b
    return 0;
}