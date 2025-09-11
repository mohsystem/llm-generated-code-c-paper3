#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

bool validatePin(const char *pin) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[0-9]{4}$|^[0-9]{6}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, pin, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

int main() {
    printf("%d\n", validatePin("1234")); // true
    printf("%d\n", validatePin("12345")); // false
    printf("%d\n", validatePin("a234")); // false
    printf("%d\n", validatePin("123456")); // true
    printf("%d\n", validatePin("1234567")); // false
    return 0;
}