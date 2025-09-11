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
    char* result = (char*)malloc((length + 1) * sizeof(char));
    char* word = (char*)malloc((length + 1) * sizeof(char));
    int resultIndex = 0;
    int wordIndex = 0;

    for (int i = 0; i <= length; i++) {
        if (s[i] == ' ' || s[i] == '\0') {
            if (wordIndex >= 5) {
                reverse(word);
            }
            strncpy(result + resultIndex, word, wordIndex);
            resultIndex += wordIndex;
            result[resultIndex++] = ' ';
            wordIndex = 0;
        } else {
            word[wordIndex++] = s[i];
        }
    }
    result[resultIndex - 1] = '\0'; // Remove the trailing space
    free(word);
    return result;
}

int main() {
    printf("%s\n", reverseWords("Hey fellow warriors"));
    printf("%s\n", reverseWords("This is a test"));
    printf("%s\n", reverseWords("This is another test"));
    printf("%s\n", reverseWords("Short words"));
    printf("%s\n", reverseWords("Single word"));
    return 0;
}