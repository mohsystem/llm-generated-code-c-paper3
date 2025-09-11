#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* toJadenCase(char* phrase) {
    if (phrase == NULL || *phrase == '\0') {
        return NULL;
    }
    char* p = phrase;
    while (*p) {
        if (*p == ' ' || p == phrase) {
            *p = toupper(*p);
        } else {
            *p = tolower(*p);
        }
        if (*p == ' ') {
            p++;
            if (*p) {
                *p = toupper(*p);
            }
        } else {
            p++;
        }
    }
    return phrase;
}

int main() {
    char phrase1[] = "How can mirrors be real if our eyes aren't real";
    char phrase2[] = "Not Jaden-Cased: 'How can mirrors be real if our eyes aren't real'";
    char phrase3[] = "";
    char phrase4[] = "this is a test";
    
    printf("%s\n", toJadenCase(phrase1));
    printf("%s\n", toJadenCase(phrase2));
    printf("%s\n", toJadenCase(phrase3));
    printf("%s\n", toJadenCase(phrase4));
    
    return 0;
}