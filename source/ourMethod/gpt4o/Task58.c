#include <stdio.h>
#include <ctype.h>

int XO(const char *str) {
    int countX = 0;
    int countO = 0;
    while (*str) {
        if (tolower(*str) == 'x') {
            countX++;
        } else if (tolower(*str) == 'o') {
            countO++;
        }
        str++;
    }
    return countX == countO;
}

int main() {
    printf("%d\n", XO("ooxx"));   // 1 (true)
    printf("%d\n", XO("xooxx"));  // 0 (false)
    printf("%d\n", XO("ooxXm"));  // 1 (true)
    printf("%d\n", XO("zpzpzpp"));// 1 (true)
    printf("%d\n", XO("zzoo"));   // 0 (false)
    return 0;
}