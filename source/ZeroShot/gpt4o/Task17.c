#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* toJadenCase(const char* phrase) {
    if (phrase == NULL || strlen(phrase) == 0) return NULL;
    static char result[256];
    int i = 0;
    int newWord = 1;
    for (int j = 0; phrase[j] != '\0'; j++) {
        if (isspace(phrase[j])) {
            newWord = 1;
            result[i++] = phrase[j];
        } else if (newWord) {
            result[i++] = toupper(phrase[j]);
            newWord = 0;
        } else {
            result[i++] = phrase[j];
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    printf("%s\n", toJadenCase("How can mirrors be real if our eyes aren't real"));
    printf("%s\n", toJadenCase("the quick brown fox jumps over the lazy dog"));
    printf("%s\n", toJadenCase("hello world"));
    printf("%s\n", toJadenCase(""));
    printf("%s\n", toJadenCase(NULL));
    return 0;
}