#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isIsogram(const char *str) {
    if (strlen(str) == 0) {
        return true;
    }
    int seen[26] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (c >= 'a' && c <= 'z') {
            if (seen[c - 'a']) {
                return false;
            }
            seen[c - 'a'] = 1;
        }
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // true
    printf("%d\n", isIsogram("aba")); // false
    printf("%d\n", isIsogram("moOse")); // false
    printf("%d\n", isIsogram("")); // true
    printf("%d\n", isIsogram("isogram")); // true
    return 0;
}