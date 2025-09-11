#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isIsogram(const char* str) {
    int charCount[26] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (charCount[c - 'a'] > 0) {
            return false;
        }
        charCount[c - 'a']++;
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