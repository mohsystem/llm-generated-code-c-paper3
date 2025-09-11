#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toJadenCase(char* phrase) {
    if (phrase == NULL || *phrase == '\0') {
        return;
    }
    bool capitalizeNext = true;
    for (char* p = phrase; *p; ++p) {
        if (capitalizeNext) {
            *p = toupper(*p);
            capitalizeNext = false;
        } else {
            *p = tolower(*p);
        }
        if (*p == ' ') {
            capitalizeNext = true;
        }
    }
}

int main() {
    char testCases[][100] = {
        "How can mirrors be real if our eyes aren't real",
        "Most trees are blue",
        "If everybody in the world dropped out of school we would have a much more intelligent society",
        "There is no nutrients in our food anymore or in our soil or in our water",
        "You would have to eat 5 apples today to get the same nutritional value as an apple from 1950"
    };
    for (int i = 0; i < 5; ++i) {
        toJadenCase(testCases[i]);
        printf("%s\n", testCases[i]);
    }
    return 0;
}