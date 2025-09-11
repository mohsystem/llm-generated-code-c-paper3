#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool xo(const char *str) {
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
    printf("%s\n", xo("ooxx") ? "true" : "false"); // true
    printf("%s\n", xo("xooxx") ? "true" : "false"); // false
    printf("%s\n", xo("ooxXm") ? "true" : "false"); // true
    printf("%s\n", xo("zpzpzpp") ? "true" : "false"); // true
    printf("%s\n", xo("zzoo") ? "true" : "false"); // false
    return 0;
}