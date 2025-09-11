#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *spinWords(const char *sentence) {
    char *result = malloc(strlen(sentence) + 1);
    strcpy(result, sentence);
    
    char *word = strtok(result, " ");
    char *res = malloc(strlen(sentence) + 1);
    res[0] = '\0';

    while (word != NULL) {
        if (strlen(word) >= 5) {
            reverse(word, word + strlen(word) - 1);
        }
        strcat(res, word);
        strcat(res, " ");
        word = strtok(NULL, " ");
    }
    
    res[strlen(res) - 1] = '\0'; // remove trailing space
    return res;
}

int main() {
    char *result;

    result = spinWords("Hey fellow warriors");
    printf("%s\n", result); // "Hey wollef sroirraw"
    free(result);

    result = spinWords("This is a test");
    printf("%s\n", result); // "This is a test"
    free(result);

    result = spinWords("This is another test");
    printf("%s\n", result); // "This is rehtona test"
    free(result);

    result = spinWords("Coding in C");
    printf("%s\n", result); // "gnidoC in C"
    free(result);

    result = spinWords("Hello world");
    printf("%s\n", result); // "olleH dlrow"
    free(result);

    return 0;
}