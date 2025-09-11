#include <stdio.h>
#include <string.h>
#include <ctype.h>

void spinWords(const char *sentence, char *output) {
    const char *word_start = sentence;
    char word[100];
    int word_length = 0;

    while (*sentence) {
        if (isspace(*sentence) || *(sentence + 1) == '\0') {
            if (*(sentence + 1) == '\0' && !isspace(*sentence)) {
                word[word_length++] = *sentence;
            }
            word[word_length] = '\0';
            if (word_length >= 5) {
                for (int i = 0; i < word_length; i++) {
                    output[i] = word[word_length - 1 - i];
                }
            } else {
                strcpy(output, word);
            }
            output += word_length;
            if (isspace(*sentence)) {
                *output++ = ' ';
            }
            word_length = 0;
        } else {
            word[word_length++] = *sentence;
        }
        sentence++;
    }
    *output = '\0';
}

int main() {
    char result[100];
    spinWords("Hey fellow warriors", result);
    printf("%s\n", result); // Hey wollef sroirraw
    spinWords("This is a test", result);
    printf("%s\n", result); // This is a test
    spinWords("This is another test", result);
    printf("%s\n", result); // This is rehtona test
    spinWords("Hello world", result);
    printf("%s\n", result); // olleH world
    spinWords("C programming", result);
    printf("%s\n", result); // C gnimmargorp
    return 0;
}