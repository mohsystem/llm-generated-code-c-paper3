#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char *str) {
    int charSet[26] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        if (charSet[c - 'a'] != 0) {
            return false;
        }
        charSet[c - 'a'] = 1;
    }
    return true;
}

int main() {
    printf("%s\n", isIsogram("Dermatoglyphics") ? "true" : "false"); // true
    printf("%s\n", isIsogram("aba") ? "true" : "false"); // false
    printf("%s\n", isIsogram("moOse") ? "true" : "false"); // false
    printf("%s\n", isIsogram("isogram") ? "true" : "false"); // true
    printf("%s\n", isIsogram("") ? "true" : "false"); // true
    return 0;
}