#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* highestScoringWord(char *s) {
    char *word = strtok(s, " ");
    char *highestWord = NULL;
    int highestScore = 0;

    while (word != NULL) {
        int score = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            score += word[i] - 'a' + 1;
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
    char *result1 = highestScoringWord(s1);
    printf("%s\n", result1); // taxi

    char s2[] = "what time are we climbing up the volcano";
    char *result2 = highestScoringWord(s2);
    printf("%s\n", result2); // volcano

    char s3[] = "take me to semynak";
    char *result3 = highestScoringWord(s3);
    printf("%s\n", result3); // semynak

    char s4[] = "aa b";
    char *result4 = highestScoringWord(s4);
    printf("%s\n", result4); // aa

    char s5[] = "hello world";
    char *result5= highestScoringWord(s5);
    printf("%s\n", result5); // world


    return 0;
}