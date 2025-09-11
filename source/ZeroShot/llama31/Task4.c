#include <stdio.h>
#include <ctype.h>

// Function to check if a string is an isogram or not
int isIsogram(const char* s) {
    int freq[26] = {0};
    while (*s != '\0') {
        if (*s >= 'a' && *s <= 'z') {
            freq[*s - 'a']++;
            if (freq[*s - 'a'] > 1) {
                return 0;
            }
        } else if (*s >= 'A' && *s <= 'Z') {
            freq[tolower(*s) - 'a']++;
            if (freq[tolower(*s) - 'a'] > 1) {
                return 0;
            }
        }
        s++;
    }
    return 1;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    printf("%d\n", isIsogram("")); // 1 (true)
    printf("%d\n", isIsogram("abcde")); // 1 (true)
    return 0;
}