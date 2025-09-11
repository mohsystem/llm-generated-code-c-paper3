#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isPangram(const char* sentence) {
    bool letters[26] = { false };
    int index;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isalpha(sentence[i])) {
            index = tolower(sentence[i]) - 'a';
            letters[index] = true;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!letters[i]) return false;
    }
    return true;
}

int main() {
    printf("%d\n", isPangram("The quick brown fox jumps over the lazy dog")); // 1 (True)
    printf("%d\n", isPangram("Hello World!")); // 0 (False)
    printf("%d\n", isPangram("Pack my box with five dozen liquor jugs.")); // 1 (True)
    printf("%d\n", isPangram("Sphinx of black quartz, judge my vow.")); // 1 (True)
    printf("%d\n", isPangram("Not a pangram sentence.")); // 0 (False)
    return 0;
}