#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return true;
    }

    bool set[26] = { false };
    for (int i = 0; str[i]; i++) {
        int index = tolower(str[i]) - 'a';
        if (set[index]) {
            return false;
        }
        set[index] = true;
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1
    printf("%d\n", isIsogram("aba")); // 0
    printf("%d\n", isIsogram("moOse")); // 0
    printf("%d\n", isIsogram("")); // 1
    printf("%d\n", isIsogram(NULL)); // 1
    return 0;
}