#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isIsogram(const char* str) {
    int charSet[26] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (charSet[c - 'a']) {
            return 0;
        }
        charSet[c - 'a'] = 1;
    }
    return 1;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // true
    printf("%d\n", isIsogram("aba")); // false
    printf("%d\n", isIsogram("moOse")); // false
    printf("%d\n", isIsogram("")); // true
    printf("%d\n", isIsogram("isogram")); // true
    return 0;
}