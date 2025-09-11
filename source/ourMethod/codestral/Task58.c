#include <stdio.h>
#include <ctype.h>
#include <string.h>

int XO(const char *str) {
    int xCount = 0, oCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (c == 'x') {
            xCount++;
        } else if (c == 'o') {
            oCount++;
        }
    }
    return xCount == oCount;
}

int main() {
    printf("%d\n", XO("ooxx")); // 1 (true)
    printf("%d\n", XO("xooxx")); // 0 (false)
    printf("%d\n", XO("ooxXm")); // 1 (true)
    printf("%d\n", XO("zpzpzpp")); // 1 (true)
    printf("%d\n", XO("zzoo")); // 0 (false)
    return 0;
}