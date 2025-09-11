#include<stdio.h>
#include<string.h>
#include<ctype.h>

int isPangram(char* str) {
    int count[26] = {0};
    for (int i = 0; str[i]; i++) {
        if ('a' <= tolower(str[i]) && tolower(str[i]) <= 'z') {
            count[tolower(str[i]) - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    printf("%d\n", isPangram("The quick brown fox jumps over the lazy dog")); // 1 (true)
    printf("%d\n", isPangram("This is not a pangram")); // 0 (false)
    printf("%d\n", isPangram("1234567890")); // 0 (false)
    printf("%d\n", isPangram("abcdefghijklmopqrstuvwxyz")); // 0 (false, missing 'n')
    printf("%d\n", isPangram("thequickbrownfoxjumpsoverthelazydog")); // 1 (true)
    return 0;
}