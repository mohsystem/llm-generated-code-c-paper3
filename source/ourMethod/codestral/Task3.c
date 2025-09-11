#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_pangram(const char *str) {
    bool alphabet[26] = {false};
    for (const char *p = str; *p != '\0'; p++) {
        char c = tolower(*p);
        if (isalpha(c)) {
            alphabet[c - 'a'] = true;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!alphabet[i]) {
            return false;
        }
    }
    return true;
}

#include <stdio.h>

int main() {
    printf("%s\n", is_pangram("The quick brown fox jumps over the lazy dog") ? "True" : "False"); // True
    printf("%s\n", is_pangram("This is not a pangram") ? "True" : "False"); // False
    printf("%s\n", is_pangram("1234567890") ? "True" : "False"); // False
    printf("%s\n", is_pangram("") ? "True" : "False"); // False
    printf("%s\n", is_pangram("The five boxing wizards jump quickly") ? "True" : "False"); // True
    return 0;
}