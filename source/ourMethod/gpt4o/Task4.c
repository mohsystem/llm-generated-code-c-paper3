#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char* str) {
    bool charSet[26] = { false };
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (charSet[c - 'a']) {
            return false;
        }
        charSet[c - 'a'] = true;
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    printf("%d\n", isIsogram("")); // 1 (true)
    printf("%d\n", isIsogram("isogram")); // 1 (true)
    return 0;
}