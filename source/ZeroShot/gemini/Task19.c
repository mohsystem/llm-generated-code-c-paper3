#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char *spinWords(char *sentence) {
    char *result = (char *)malloc(strlen(sentence) * sizeof(char) + 1);
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        if (strlen(token) >= 5) {
            reverse_string(token);
        }
        strcat(result, token);
        strcat(result, " ");
        token = strtok(NULL, " ");
    }
    result[strlen(result) - 1] = '\0'; // Remove trailing space
    return result;
}

int main() {
    char sentence1[] = "Hey fellow warriors";
    char sentence2[] = "This is a test";
    char sentence3[] = "This is another test";
    char sentence4[] = "Hello";
    char sentence5[] = "Welcome to the world";

    printf("%s\n", spinWords(sentence1));
    printf("%s\n", spinWords(sentence2));
    printf("%s\n", spinWords(sentence3));
    printf("%s\n", spinWords(sentence4));
    printf("%s\n", spinWords(sentence5));


    return 0;
}