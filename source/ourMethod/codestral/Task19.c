#include <stdio.h>
#include <string.h>

void reverse(char* str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void spinWords(char* sentence) {
    int wordStart = 0;
    int wordLength = 0;

    for (int i = 0; i <= strlen(sentence); i++) {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (wordLength >= 5) {
                reverse(sentence, wordStart, i - 1);
            }
            wordStart = i + 1;
            wordLength = 0;
        } else {
            wordLength++;
        }
    }
}

int main() {
    char sentence1[] = "Hey fellow warriors";
    char sentence2[] = "This is a test";
    char sentence3[] = "This is another test";

    spinWords(sentence1);
    spinWords(sentence2);
    spinWords(sentence3);

    printf("%s\n", sentence1);
    printf("%s\n", sentence2);
    printf("%s\n", sentence3);

    return 0;
}