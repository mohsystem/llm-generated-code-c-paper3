#include <stdio.h>
#include <regex.h>
#include <string.h>

int isValidEmail(const char *email) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

int main() {
    printf("%d\n", isValidEmail("test@example.com")); // 1 (true)
    printf("%d\n", isValidEmail("invalid.email")); // 0 (false)
    printf("%d\n", isValidEmail("another.test@subdomain.example.co.uk")); // 1 (true)
    printf("%d\n", isValidEmail("12345@numbers.net")); // 1 (true)
    printf("%d\n", isValidEmail("invalid-email@.com")); // 0 (false)
    return 0;
}