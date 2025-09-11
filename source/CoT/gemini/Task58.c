#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool xo(const char *str) {
    int x_count = 0;
    int o_count = 0;
    char lower_str[strlen(str) + 1];
    strcpy(lower_str, str);

    for (int i = 0; lower_str[i]; i++) {
        lower_str[i] = tolower(lower_str[i]);
    }


    for (int i = 0; lower_str[i]; i++) {
        if (lower_str[i] == 'x') {
            x_count++;
        } else if (lower_str[i] == 'o') {
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