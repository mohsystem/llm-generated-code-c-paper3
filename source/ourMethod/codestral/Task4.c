#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isIsogram(char* str) {
    bool set[26] = {false};
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int index = tolower(str[i]) - 'a';
        if (set[index]) {
            return false;
        }
        set[index] = true;
    }
    return true;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    return 0;
}