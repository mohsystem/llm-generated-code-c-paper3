#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isPangram(const char* input) {
    bool alphabet[26] = { false };
    int index;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            index = tolower(input[i]) - 'a';
            alphabet[index] = true;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!alphabet[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy dog") ? "True" : "False"); // True
    printf("%s\n", isPangram("Hello World!") ? "True" : "False"); // False
    printf("%s\n", isPangram("Pack my box with five dozen liquor jugs") ? "True" : "False"); // True
    printf("%s\n", isPangram("Sphinx of black quartz, judge my vow") ? "True" : "False"); // True
    printf("%s\n", isPangram("Not a pangram") ? "True" : "False"); // False
    return 0;
}