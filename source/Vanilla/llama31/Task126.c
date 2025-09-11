#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void countLinesAndWords() {
    int lines = 0;
    int words = 0;
    int inWord = 0;
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            lines++;
        }
        if (isspace(c)) {
            inWord = 0;
        } else if (!inWord) {
            words++;
            inWord = 1;
        }
    }
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
}

int main() {
    // Test cases
    printf("Test Case 1:\n");
    countLinesAndWords();

    printf("\nTest Case 2:\n");
    countLinesAndWords();

    printf("\nTest Case 3:\n");
    countLinesAndWords();

    printf("\nTest Case 4:\n");
    countLinesAndWords();

    printf("\nTest Case 5:\n");
    countLinesAndWords();

    return 0;
}