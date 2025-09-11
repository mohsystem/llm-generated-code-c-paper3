#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char *spinWords(char *sentence) {
    char *result = (char *)malloc(strlen(sentence) * sizeof(char) + 1); // Allocate memory
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
    char *result1 = spinWords(sentence1);
    printf("%s\n", result1); // Output: Hey wollef sroirraw
    free(result1);

    char sentence2[] = "This is a test";
    char *result2 = spinWords(sentence2);
    printf("%s\n", result2); // Output: This is a test
    free(result2);


    char sentence3[] = "This is another test";
    char *result3 = spinWords(sentence3);
    printf("%s\n", result3); // Output: This is rehtona test
    free(result3);

    char sentence4[] = "Hello";
    char *result4 = spinWords(sentence4);
    printf("%s\n", result4); // Output: olleH
    free(result4);


    char sentence5[] = "What's up";
    char *result5 = spinWords(sentence5);
    printf("%s\n", result5);  // Output: What's up
    free(result5);

    return 0;
}