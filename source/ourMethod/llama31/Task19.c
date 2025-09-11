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

char* reverseWords(const char* str) {
    char* result = (char*)malloc(strlen(str) + 1);
    strcpy(result, str);

    char* wordStart = result;
    for (char* p = result; *p; p++) {
        if (*p == ' ') {
            if (p - wordStart >= 5) {
                reverse(wordStart);
            }
            wordStart = p + 1;
        }
    }
    if (strlen(wordStart) >= 5) {
        reverse(wordStart);
    }
    return result;
}

int main() {
    printf("%s\n", reverseWords("Hey fellow warriors"));
    printf("%s\n", reverseWords("This is a test"));
    printf("%s\n", reverseWords("This is another test"));
    return 0;
}