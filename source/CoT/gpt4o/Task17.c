#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* toJadenCase(char* phrase) {
    if (phrase == NULL || strlen(phrase) == 0) {
        return NULL;
    }
    static char result[256];
    memset(result, 0, sizeof(result));
    int capitalizeNext = 1;
    int index = 0;
    
    for (int i = 0; phrase[i] != '\0'; i++) {
        if (phrase[i] == ' ') {
            result[index++] = ' ';
            capitalizeNext = 1;
        } else if (capitalizeNext) {
            result[index++] = toupper(phrase[i]);
            capitalizeNext = 0;
        } else {
            result[index++] = phrase[i];
        }
    }
    return result;
}

int main() {
    printf("%s\n", toJadenCase("How can mirrors be real if our eyes aren't real")); // How Can Mirrors Be Real If Our Eyes Aren't Real
    printf("%s\n", toJadenCase("most trees are blue")); // Most Trees Are Blue
    printf("%s\n", toJadenCase("")); // (null)
    printf("%s\n", toJadenCase(NULL)); // (null)
    printf("%s\n", toJadenCase("the quick brown fox jumps over the lazy dog")); // The Quick Brown Fox Jumps Over The Lazy Dog
    return 0;
}