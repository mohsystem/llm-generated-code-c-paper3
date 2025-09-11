#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* high(const char *s) {
    char *token = strtok((char *)s, " ");
    int maxScore = 0;
    char *maxWord = NULL;
    while (token != NULL) {
        int score = 0;
        for (int i = 0; i < strlen(token); i++) {
            score += token[i] - 'a' + 1;
        }
        if (score > maxScore) {
            maxScore = score;
            maxWord = token;
        }
        token = strtok(NULL, " ");
    }
    return maxWord;
}

int main() {
    printf("%s\n", high("man i need a taxi up to ubud"));
    printf("%s\n", high("what time are we climbing up the volcano"));
    printf("%s\n", high("take me to semynak"));
    printf("%s\n", high("massage yes massage yes massage"));
    printf("%s\n", high("take two bintang and a dance please"));
    return 0;
}