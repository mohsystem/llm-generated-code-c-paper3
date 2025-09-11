#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isPangram(const char *sentence) {
    bool seen[26] = {false};
    int count = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        char c = tolower(sentence[i]);
        if (c >= 'a' && c <= 'z') {
            if (!seen[c - 'a']) {
                seen[c - 'a'] = true;
                count++;
            }
        }
    }

    return count == 26;
}

int main() {
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy dog") ? "true" : "false"); // True
    printf("%s\n", isPangram("This is not a pangram.") ? "true" : "false"); // False
    printf("%s\n", isPangram("Pack my box with five dozen liquor jugs.") ? "true" : "false"); // True
    printf("%s\n", isPangram("How quickly daft jumping zebras vex.") ? "true" : "false"); // True
    printf("%s\n", isPangram("Waltz, bad nymph, for quick jigs vex.") ? "true" : "false"); // True
     return 0;
}