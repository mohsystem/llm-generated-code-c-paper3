#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* toJadenCase(char* phrase) {
    if (phrase == NULL || *phrase == '\0') {
        return NULL;
    }
    char* result = phrase;
    bool newWord = true;
    for (char* p = phrase; *p; ++p) {
        if (*p == ' ') {
            newWord = true;
        } else {
            if (newWord) {
                *p = toupper(*p);
                newWord = false;
            } else {
                *p = tolower(*p);
            }
        }
    }
    return result;
}

int main() {
    char testCases[][100] = {
        "How can mirrors be real if our eyes aren't real",
        "What is the meaning of life?",
        "",
        ""
    };
    for (int i = 0; i < 4; ++i) {
        printf("Input: %s\n", testCases[i]);
        printf("Output: %s\n\n", toJadenCase(testCases[i]));
    }
    return 0;
}