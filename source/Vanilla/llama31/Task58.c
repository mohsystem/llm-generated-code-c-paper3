#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool xo(const char* str) {
    int xCount = 0;
    int oCount = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (tolower(str[i]) == 'x') xCount++;
        if (tolower(str[i]) == 'o') oCount++;
    }
    return xCount == oCount;
}

int main() {
    printf("%d\n", xo("ooxx")); // 1 (true)
    printf("%d\n", xo("xooxx")); // 0 (false)
    printf("%d\n", xo("ooxXm")); // 1 (true)
    printf("%d\n", xo("zpzpzpp")); // 1 (true)
    printf("%d\n", xo("zzoo")); // 0 (false)
    return 0;
}