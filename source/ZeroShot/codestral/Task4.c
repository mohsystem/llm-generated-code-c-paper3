#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(char *str) {
    bool charSet[128] = {false};
    for (int i = 0; str[i]; i++) {
        int val = tolower(str[i]);
        if (charSet[val]) {
            return false;
        }
        charSet[val] = true;
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1
    printf("%d\n", isIsogram("aba")); // 0
    printf("%d\n", isIsogram("moOse")); // 0
    printf("%d\n", isIsogram("")); // 1
    printf("%d\n", isIsogram("isogram")); // 1
    return 0;
}