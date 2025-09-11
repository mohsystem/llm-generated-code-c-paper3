#include <stdio.h>
#include <string.h>

void tweakLetters(const char* word, int tweaks[], int size, char* result) {
    for (int i = 0; i < size; i++) {
        result[i] = word[i] + tweaks[i];
    }
    result[size] = '\0';
}

int main() {
    char result[6];
    
    tweakLetters("apple", (int[]){0, 1, -1, 0, -1}, 5, result);
    printf("%s\n", result); // "aqold"
    
    tweakLetters("many", (int[]){0, 0, 0, -1}, 4, result);
    printf("%s\n", result); // "manx"
    
    tweakLetters("rhino", (int[]){1, 1, 1, 1, 1}, 5, result);
    printf("%s\n", result); // "sijop"
    
    tweakLetters("hello", (int[]){0, 0, 1, -1, 0}, 5, result);
    printf("%s\n", result); // "hempo"
    
    tweakLetters("world", (int[]){-1, 1, 0, 0, -1}, 5, result);
    printf("%s\n", result); // "vprke"
    
    return 0;
}