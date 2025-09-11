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
    char test1[] = "man i need a taxi up to ubud";
    char test2[] = "what time are we climbing up the volcano";
    char test3[] = "take me to semynak";
    char test4[] = "aa b";
    char test5[] = "a aa";
    char s1[100], s2[100],s3[100],s4[100],s5[100];
    strcpy(s1, test1);
    strcpy(s2, test2);
    strcpy(s3, test3);
    strcpy(s4, test4);
    strcpy(s5, test5);


    printf("Test 1: %s\n", highestScoringWord(s1)); // Expected: taxi
    printf("Test 2: %s\n", highestScoringWord(s2)); // Expected: volcano
    printf("Test 3: %s\n", highestScoringWord(s3)); // Expected: semynak
    printf("Test 4: %s\n", highestScoringWord(s4)); // Expected: b
    printf("Test 5: %s\n", highestScoringWord(s5)); // Expected: a

    return 0;
}