#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isIsogram(const char *str) {
    if (strlen(str) == 0) {
        return true;
    }
    char lowerStr[1000]; // Adjust size as needed
    strcpy(lowerStr, str);
    for (int i = 0; lowerStr[i]; i++) {
        lowerStr[i] = tolower(lowerStr[i]);
    }

    for (int i = 0; lowerStr[i]; i++) {
        for (int j = i + 1; lowerStr[j]; j++) {
            if (lowerStr[i] == lowerStr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    printf("%s\n", isIsogram("Dermatoglyphics") ? "true" : "false"); // true
    printf("%s\n", isIsogram("aba") ? "true" : "false"); // false
    printf("%s\n", isIsogram("moOse") ? "true" : "false"); // false
    printf("%s\n", isIsogram("") ? "true" : "false"); // true
    printf("%s\n", isIsogram("isogram") ? "true" : "false"); // true
    return 0;
}