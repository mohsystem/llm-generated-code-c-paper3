#include <stdio.h>
#include <string.h>

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseFiveOrMore(char *s) {
    char *word = strtok(s, " ");
    while (word != NULL) {
        if (strlen(word) >= 5) {
            reverse(word);
        }
        printf("%s ", word);
        word = strtok(NULL, " ");
    }
    printf("\n");
}

int main() {
    char s1[] = "Hey fellow warriors";
    char s2[] = "This is a test";
    char s3[] = "This is another test";
    reverseFiveOrMore(s1); // "Hey wollef sroirraw"
    reverseFiveOrMore(s2); // "This is a test"
    reverseFiveOrMore(s3); // "This is rehtona test"
    return 0;
}