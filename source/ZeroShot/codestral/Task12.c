#include <stdio.h>
#include <string.h>

void high(const char* s, char* result) {
    const char* word = s;
    char* end;
    int maxScore = 0;

    while (*word != '\0') {
        int score = 0;
        while (*word != ' ' && *word != '\0') {
            score += *word - 'a' + 1;
            word++;
        }
        if (score > maxScore) {
            maxScore = score;
            strncpy(result, word - score, score);
            result[score] = '\0';
        }
        if (*word != '\0') {
            word++;
        }
    }
}

int main() {
    char result[256];
    high("man i need a taxi up to ubud", result);
    printf("%s\n", result); // "taxi"
    high("what time are we climbing up the volcano", result);
    printf("%s\n", result); // "volcano"
    high("take me to semynak", result);
    printf("%s\n", result); // "semynak"
    high("massage yes massage yes massage", result);
    printf("%s\n", result); // "massage"
    high("take two bintang and a dance please", result);
    printf("%s\n", result); // "bintang" or "please"
    return 0;
}