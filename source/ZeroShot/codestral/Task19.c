#include <stdio.h>
#include <string.h>

void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void spinWords(char* sentence) {
    char* word = strtok(sentence, " ");
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
    spinWords("Hey fellow warriors"); // Output: "Hey wollef sroirraw"
    spinWords("This is a test"); // Output: "This is a test"
    spinWords("This is another test"); // Output: "This is rehtona test"
    return 0;
}