#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* highestScoringWord(char *s) {
    char *word = strtok(s, " ");
    char *highestWord = NULL;
    int highestScore = 0;

    while (word != NULL) {
        int score = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            score += tolower(word[i]) - 'a' + 1;
        }

        if (score > highestScore) {
            highestScore = score;
            if (highestWord != NULL) free(highestWord);
            highestWord = strdup(word);
        }
        word = strtok(NULL, " ");
    }
    return highestWord;

}

int main() {
    char s1[] = "man i need a taxi up to ubud";
    char *result1 = highestScoringWord(strdup(s1));
    printf("%s\n", result1); // taxi
    free(result1);

    char s2[] = "what time are we climbing up the volcano";
    char *result2 = highestScoringWord(strdup(s2));
    printf("%s\n", result2); // volcano
    free(result2);

    char s3[] = "take me to semynak";
    char *result3 = highestScoringWord(strdup(s3));
    printf("%s\n", result3); // semynak
    free(result3);

    char s4[] = "aa b";
    char *result4 = highestScoringWord(strdup(s4));
    printf("%s\n", result4); // aa
    free(result4);
    
    char s5[] = "a b c d";
    char *result5 = highestScoringWord(strdup(s5));
    printf("%s\n", result5); // d
    free(result5);


    return 0;
}