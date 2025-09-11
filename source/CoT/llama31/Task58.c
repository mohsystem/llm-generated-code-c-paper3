#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool XO(const char *str) {
    int xCount = 0;
    int oCount = 0;
    for (int i = 0; str[i]; i++) {
        if (tolower(str[i]) == 'x') xCount++;
        if (tolower(str[i]) == 'o') oCount++;
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