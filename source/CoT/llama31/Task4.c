#include <stdio.h>
#include <ctype.h>

int isIsogram(const char* str) {
    int mapHash[26] = {0};
    while (*str) {
        char c = tolower(*str);
        mapHash[c - 'a']++;
        if (mapHash[c - 'a'] > 1) {
            return 0;
        }
        str++;
    }
    return 1;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    printf("%d\n", isIsogram("")); // 1 (true)
    printf("%d\n", isIsogram("a")); // 1 (true)
    return 0;
}