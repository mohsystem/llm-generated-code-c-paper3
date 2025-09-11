#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toJadenCase(const char *phrase, char *result) {
    if (phrase == NULL || result == NULL) {
        return;
    }

    int i = 0, j = 0;
    int newWord = 1; // Flag to indicate the start of a new word

    while (phrase[i] != '\0') {
        if (isspace(phrase[i])) {
            newWord = 1;
            result[j++] = phrase[i++];
        } else {
            if (newWord) {
                result[j++] = toupper(phrase[i++]);
                newWord = 0;
            } else {
                result[j++] = tolower(phrase[i++]);
            }
        }
    }
    result[j] = '\0';
}

int main() {
    char result[256];
    
    toJadenCase("How can mirrors be real if our eyes aren't real", result);
    printf("%s\n", result); // "How Can Mirrors Be Real If Our Eyes Aren't Real"
    
    toJadenCase("", result);
    printf("%s\n", result); // ""
    
    toJadenCase("jaden smith's twitter is so interesting", result);
    printf("%s\n", result); // "Jaden Smith's Twitter Is So Interesting"
    
    toJadenCase("life is a mystery to be lived", result);
    printf("%s\n", result); // "Life Is A Mystery To Be Lived"
    
    toJadenCase("one more test case", result);
    printf("%s\n", result); // "One More Test Case"

    return 0;
}