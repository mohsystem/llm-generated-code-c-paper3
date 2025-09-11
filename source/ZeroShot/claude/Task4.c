
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char *str) {
    if (!str || !*str) return true;
    
    bool seen[26] = {false};
    
    for (int i = 0; str[i] != '\\0'; i++) {
        if (isalpha(str[i])) {
            int index = tolower(str[i]) - 'a';
            if (seen[index]) return false;
            seen[index] = true;
        }
    }
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", isIsogram("Dermatoglyphics")); // 1
    printf("%d\\n", isIsogram("aba")); // 0
    printf("%d\\n", isIsogram("moOse")); // 0
    printf("%d\\n", isIsogram("")); // 1
    printf("%d\\n", isIsogram("thumbscrew-japingly")); // 1
    return 0;
}
