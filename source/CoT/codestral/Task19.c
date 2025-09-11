#include <stdio.h>
#include <string.h>

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void spinWords(char* sentence) {
    int length = strlen(sentence);
    int wordStart = 0;

    for (int i = 0; i <= length; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (i - wordStart >= 5) {
                reverse(&sentence[wordStart], i - wordStart);
            }
            wordStart = i + 1;
        }
    }
}

int main() {
    char sentence[100];

    strcpy(sentence, "Hey fellow warriors");
    spinWords(sentence);
    printf("%s\n", sentence); // "Hey wollef sroirraw"

    strcpy(sentence, "This is a test");
    spinWords(sentence);
    printf("%s\n", sentence); // "This is a test"

    strcpy(sentence, "This is another test");
    spinWords(sentence);
    printf("%s\n", sentence); // "This is rehtona test"

    return 0;
}