#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isIsogram(const char *str) {
    if (strlen(str) == 0) {
        return true;
    }

    char lowerStr[1000]; 
    strcpy(lowerStr, str);
    for (int i = 0; lowerStr[i]; i++) {
        lowerStr[i] = tolower(lowerStr[i]);
    }


    int seenChars[26] = {0}; // Assuming only letters a-z

    for (int i = 0; lowerStr[i]; i++) {
        int index = lowerStr[i] - 'a';
         if (seenChars[index]) {
            return false;
        }
        seenChars[index]++;
    }

    return true;
}

int main() {
    char *testCases[] = {"Dermatoglyphics", "aba", "moOse", "", "isogram"};
    bool expectedResults[] = {true, false, false, true, true};

    for (int i = 0; i < 5; i++) {
        bool actualResult = isIsogram(testCases[i]);
        printf("Input: \"%s\" --> Output: %s, Expected: %s\n", testCases[i], actualResult ? "true" : "false", expectedResults[i] ? "true" : "false");
    }

    return 0;
}