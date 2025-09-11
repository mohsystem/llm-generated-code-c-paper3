#include <stdio.h>
#include <string.h>

void tweakLetters(char* word, int* tweaks, int length) {
    for (int i = 0; i < length; i++) {
        word[i] += tweaks[i];
    }
}

int main() {
    char word1[] = "apple";
    int tweaks1[] = {0, 1, -1, 0, -1};
    tweakLetters(word1, tweaks1, strlen(word1));
    printf("%s\n", word1); // Output: "aqold"

    char word2[] = "many";
    int tweaks2[] = {0, 0, 0, -1};
    tweakLetters(word2, tweaks2, strlen(word2));
    printf("%s\n", word2); // Output: "manx"

    char word3[] = "rhino";
    int tweaks3[] = {1, 1, 1, 1, 1};
    tweakLetters(word3, tweaks3, strlen(word3));
    printf("%s\n", word3); // Output: "sijop"

    return 0;
}