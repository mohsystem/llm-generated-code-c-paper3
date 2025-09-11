#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidWalk(const char *walk, int length) {
    if (length != 10) return false;
    int n = 0, s = 0, e = 0, w = 0;
    for (int i = 0; i < length; i++) {
        switch (walk[i]) {
            case 'n': n++; break;
            case 's': s++; break;
            case 'e': e++; break;
            case 'w': w++; break;
        }
    }
    return n == s && e == w;
}

int main() {
    printf("%s\n", isValidWalk("nsnsnsnsns", 10) ? "true" : "false"); // true
    printf("%s\n", isValidWalk("wewewewewe", 10) ? "true" : "false"); // true
    printf("%s\n", isValidWalk("nnnsnssnsn", 10) ? "true" : "false"); // false
    printf("%s\n", isValidWalk("neswneswne", 10) ? "true" : "false"); // false
    printf("%s\n", isValidWalk("nsewnsewns", 10) ? "true" : "false"); // true
    return 0;
}