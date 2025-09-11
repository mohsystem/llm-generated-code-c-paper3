#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse(char* str) {
    int length = strlen(str);
    char* start = str;
    char* end = str + length - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char* reverseWords(char* str) {
    static char buffer[1024];
    strcpy(buffer, str);
    char* word = buffer;
    while (*word) {
        if (*word == ' ') {
            word++;
            continue;
        }
        char* start = word;
        while (*word && *word != ' ') {
            word++;
        }
        if (word - start >= 5) {
            reverse(start);
        }
        if (*word) {
            word++;
        }
    }
    return buffer;
}

int main() {
    printf("%s\n", reverseWords("Hey fellow warriors"));
    printf("%s\n", reverseWords("This is a test"));
    printf("%s\n", reverseWords("This is another test"));
    printf("%s\n", reverseWords("Short words only"));
    printf("%s\n", reverseWords("No words to reverse"));
    return 0;
}