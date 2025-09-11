#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool XO(const char *str) {
    int countX = 0;
    int countO = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (tolower(str[i]) == 'x') {
            countX++;
        } else if (tolower(str[i]) == 'o') {
            countO++;
        }
    }
    return countX == countO;
}

int main() {
    printf("%s\n", XO("ooxx") ? "true" : "false");     // true
    printf("%s\n", XO("xooxx") ? "true" : "false");    // false
    printf("%s\n", XO("ooxXm") ? "true" : "false");    // true
    printf("%s\n", XO("zpzpzpp") ? "true" : "false");  // true
    printf("%s\n", XO("zzoo") ? "true" : "false");     // false
    return 0;
}