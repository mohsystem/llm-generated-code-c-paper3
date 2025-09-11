#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool XO(const char* str) {
    int countX = 0;
    int countO = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (tolower((unsigned char)str[i]) == 'x') {
            countX++;
        } else if (tolower((unsigned char)str[i]) == 'o') {
            countO++;
        }
    }
    return countX == countO;
}

int main() {
    printf("%d\n", XO("ooxx")); // 1 (true)
    printf("%d\n", XO("xooxx")); // 0 (false)
    printf("%d\n", XO("ooxXm")); // 1 (true)
    printf("%d\n", XO("zpzpzpp")); // 1 (true)
    printf("%d\n", XO("zzoo")); // 0 (false)
    return 0;
}