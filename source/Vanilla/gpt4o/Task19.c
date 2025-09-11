#include <stdio.h>
#include <string.h>
#include <ctype.h>

void spinWords(char *sentence) {
    char result[1024] = "";
    char *word = strtok(sentence, " ");
    while (word != NULL) {
        if (strlen(word) >= 5) {
            for (int i = strlen(word) - 1; i >= 0; --i) {
                strncat(result, &word[i], 1);
            }
        } else {
            strcat(result, word);
        }
        strcat(result, " ");
        word = strtok(NULL, " ");
    }
    // Remove trailing space
    result[strlen(result) - 1] = '\0';
    printf("%s\n", result);
}

int main() {
    char test1[] = "Hey fellow warriors";
    char test2[] = "This is a test";
    char test3[] = "This is another test";
    char test4[] = "Java programming";
    char test5[] = "Kata is fun";

    spinWords(test1); // "Hey wollef sroirraw"
    spinWords(test2); // "This is a test"
    spinWords(test3); // "This is rehtona test"
    spinWords(test4); // "Java gnimmargorp"
    spinWords(test5); // "Kata is fun"

    return 0;
}