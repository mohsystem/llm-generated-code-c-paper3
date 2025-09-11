#include <stdio.h>
#include <string.h>

void tweakLetters(const char* word, const int tweaks[], char* result) {
    for (int i = 0; i < strlen(word); i++) {
        result[i] = word[i] + tweaks[i];
    }
    result[strlen(word)] = '\0';
}

int main() {
    char result[100];
    
    tweakLetters("apple", (int[]){0, 1, -1, 0, -1}, result);
    printf("%s\n", result); // "aqold"
    
    tweakLetters("many", (int[]){0, 0, 0, -1}, result);
    printf("%s\n", result); // "manx"
    
    tweakLetters("rhino", (int[]){1, 1, 1, 1, 1}, result);
    printf("%s\n", result); // "sijop"
    
    tweakLetters("hello", (int[]){1, -1, 0, 0, 1}, result);
    printf("%s\n", result); // "hfllp"
    
    tweakLetters("world", (int[]){-1, 0, 1, -1, 0}, result);
    printf("%s\n", result); // "vorld"
    
    return 0;
}