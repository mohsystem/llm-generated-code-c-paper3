#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char* reverseWords(const char* s) {
    int length = strlen(s);
    char* result = (char*)malloc(length + 1);
    char* word = (char*)malloc(length + 1);
    int resultIndex = 0;
    int wordIndex = 0;

    for (int i = 0; i <= length; i++) {
        if (i == length || s[i] == ' ') {
            if (wordIndex >= 5) {
                reverse(word);
            }
            strcpy(result + resultIndex, word);
            resultIndex += wordIndex + 1;
            word[0] = '\0';
            wordIndex = 0;
            if (i < length) {
                result[resultIndex - 1] = ' ';
            }
        } else {
            word[wordIndex++] = s[i];
        }
    }

    word[wordIndex] = '\0';
    return result;
}

int main() {
    printf("%s\n", reverseWords("Hey fellow warriors"));
    printf("%s\n", reverseWords("This is a test"));
    printf("%s\n", reverseWords("This is another test"));
    printf("%s\n", reverseWords("Hello World"));
    printf("%s\n", reverseWords("Python is fun"));
    return 0;
}