#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool checkPangram(const char *sentence) {
    int seen[26] = {0};
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        char c = tolower(sentence[i]);
        if (isalpha(c)) {
            int index = c - 'a';
            if (seen[index] == 0) {
                seen[index] = 1;
                count++;
            }
        }
    }
    return count == 26;
}

int main() {
    printf("%d\n", checkPangram("The quick brown fox jumps over the lazy dog")); // True
    printf("%d\n", checkPangram("This is not a pangram.")); // False
    printf("%d\n", checkPangram("Waltz, bad nymph, for quick jigs vex.")); // True
    printf("%d\n", checkPangram("Glib jocks quiz nymph to vex dwarf.")); // True
    printf("%d\n", checkPangram("Sphinx of black quartz, judge my vow.")); // True
    return 0;
}