#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char* s) {
    int freq[26] = {0};
    for (int i = 0; s[i]; i++) {
        char c = tolower(s[i]);
        freq[c - 'a']++;
        if (freq[c - 'a'] > 1) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    printf("%d\n", isIsogram("")); // 1 (true)
    printf("%d\n", isIsogram("a")); // 1 (true)
    return 0;
}