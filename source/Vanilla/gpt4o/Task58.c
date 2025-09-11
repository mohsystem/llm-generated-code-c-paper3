#include <stdio.h>
#include <ctype.h>
#include <string.h>

int XO(const char* str) {
    int countX = 0;
    int countO = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (c == 'x') countX++;
        else if (c == 'o') countO++;
    }
    return countX == countO;
}

int main() {
    printf("%s\n", XO("ooxx") ? "true" : "false");    // true
    printf("%s\n", XO("xooxx") ? "true" : "false");   // false
    printf("%s\n", XO("ooxXm") ? "true" : "false");   // true
    printf("%s\n", XO("zpzpzpp") ? "true" : "false"); // true
    printf("%s\n", XO("zzoo") ? "true" : "false");    // false
    return 0;
}