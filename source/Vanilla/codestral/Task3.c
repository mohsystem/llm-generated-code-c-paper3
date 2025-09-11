#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isPangram(const char* str) {
    bool alphabet[26] = {false};
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            alphabet[tolower(str[i]) - 'a'] = true;
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
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy dog") ? "true" : "false");  // true
    printf("%s\n", isPangram("This is not a pangram") ? "true" : "false");  // false
    // add more test cases here
    return 0;
}