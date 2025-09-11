#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toJadenCase(const char* phrase, char* result) {
    if (phrase == NULL || strlen(phrase) == 0) {
        strcpy(result, "");
        return;
    }
    
    int capitalize = 1;
    while (*phrase) {
        if (capitalize && isalpha(*phrase)) {
            *result++ = toupper(*phrase);
            capitalize = 0;
        } else {
            *result++ = *phrase;
        }
        if (*phrase == ' ') {
            capitalize = 1;
        }
        phrase++;
    }
    *result = '\0';
}

int main() {
    char result[256];
    
    toJadenCase("How can mirrors be real if our eyes aren't real", result);
    printf("%s\n", result);
    
    toJadenCase("the moment that truth is organized it becomes a lie", result);
    printf("%s\n", result);
    
    toJadenCase("school is the tool to brainwash the youth", result);
    printf("%s\n", result);
    
    toJadenCase("if newborn babies could speak they would be the most intelligent beings on planet earth", result);
    printf("%s\n", result);
    
    toJadenCase("", result);
    printf("%s\n", result);
    
    return 0;
}