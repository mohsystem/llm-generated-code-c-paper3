
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char *str) {
    if (!str[0]) return true;
    
    char temp[strlen(str) + 1];
    int i = 0;
    
    while (str[i]) {
        temp[i] = tolower(str[i]);
        i++;
    }
    temp[i] = '\\0';
    
    for (i = 0; temp[i]; i++) {
        for (int j = i + 1; temp[j]; j++) {
            if (temp[i] == temp[j]) return false;
        }
    }
    return true;
}

int main() {
    printf("%d\\n", isIsogram("Dermatoglyphics")); // 1
    printf("%d\\n", isIsogram("aba")); // 0
    printf("%d\\n", isIsogram("moOse")); // 0
    printf("%d\\n", isIsogram("")); // 1
    printf("%d\\n", isIsogram("thumbscrewjapingly")); // 1
    return 0;
}
