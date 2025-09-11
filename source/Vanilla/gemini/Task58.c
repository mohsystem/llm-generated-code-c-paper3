#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool XO(const char *str) {
    int x_count = 0;
    int o_count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (c == 'x') {
            x_count++;
        } else if (c == 'o') {
            o_count++;
        }
    }
    return x_count == o_count;
}

int main() {
    printf("%d\n", XO("ooxx")); // true, prints 1
    printf("%d\n", XO("xooxx")); // false, prints 0
    printf("%d\n", XO("ooxXm")); // true, prints 1
    printf("%d\n", XO("zpzpzpp")); // true, prints 1
    printf("%d\n", XO("zzoo")); // false, prints 0
    return 0;
}