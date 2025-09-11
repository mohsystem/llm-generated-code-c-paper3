#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isIsogram(char *str) {
    int counter[26] = {0};
    for (int i = 0; i < strlen(str); i++) {
        int index = tolower(str[i]) - 'a';
        counter[index]++;
        if (counter[index] > 1) {
            return 0;
        }
    }
    return 1;
}

int main() {
    printf("%d\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\n", isIsogram("aba")); // 0 (false)
    printf("%d\n", isIsogram("moOse")); // 0 (false)
    return 0;
}