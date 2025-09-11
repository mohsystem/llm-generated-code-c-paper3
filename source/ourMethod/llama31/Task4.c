#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isIsogram(const char* str) {
    int mapHash[26] = {0};
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c >= 'a' && c <= 'z') {
            mapHash[c - 'a']++;
            if (mapHash[c - 'a'] > 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const char* testCases[] = {"Dermatoglyphics", "aba", "moOse", ""};
    for (int i = 0; i < 4; i++) {
        printf("%s --> %s\n", testCases[i], isIsogram(testCases[i]) ? "true" : "false");
    }
    return 0;
}