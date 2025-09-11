#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isIsogram(const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return true;
    }

    char lower_str[1000]; // Potential buffer overflow if input string is too large. Consider using dynamic allocation.
    strcpy(lower_str, str);
    for (int i = 0; lower_str[i]; i++) {
        lower_str[i] = tolower(lower_str[i]);
    }


    int seen[26] = {0}; // Assuming only English alphabet characters

    for (int i = 0; lower_str[i]; i++) {
        if (isalpha(lower_str[i])) {
            int index = lower_str[i] - 'a';
            if (seen[index]) {
                return false;
            }
            seen[index] = 1;
        }
    }

    return true;
}

int main() {
    printf("%s\n", isIsogram("Dermatoglyphics") ? "true" : "false"); // true
    printf("%s\n", isIsogram("aba") ? "true" : "false"); // false
    printf("%s\n", isIsogram("moOse") ? "true" : "false"); // false
    printf("%s\n", isIsogram("") ? "true" : "false"); // true
    printf("%s\n", isIsogram("isogram") ? "true" : "false"); // true

    return 0;
}