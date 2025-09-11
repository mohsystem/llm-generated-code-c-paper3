#include <stdio.h>
#include <string.h>
#include <ctype.h>

int XO(char *str) {
    int countX = 0, countO = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c == 'x') countX++;
        else if (c == 'o') countO++;
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