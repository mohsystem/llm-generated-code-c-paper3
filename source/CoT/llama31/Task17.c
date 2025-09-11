#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toJadenCase(char* phrase) {
    if (phrase == NULL || *phrase == '\0') {
        return;
    }
    bool capitalizeNext = true;
    for (char* c = phrase; *c != '\0'; ++c) {
        if (*c == ' ') {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            *c = toupper(*c);
            capitalizeNext = false;
        } else {
            *c = tolower(*c);
        }
    }
}

int main() {
    char testCases[][100] = {
        "How can mirrors be real if our eyes aren't real",
        "This is a test case",
        "another test case here",
        "",
        ""
    };

    for (int i = 0; i < 5; ++i) {
        printf("Not Jaden-Cased: \"%s\"\n", testCases[i]);
        toJadenCase(testCases[i]);
        printf("Jaden-Cased:     \"%s\"\n\n", testCases[i]);
    }

    return 0;
}