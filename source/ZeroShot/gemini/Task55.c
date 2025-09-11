#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidEmail(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        return 1;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return 0;
    }
}

int main() {
    printf("%d\n", isValidEmail("test@example.com")); // 1 (true)
    printf("%d\n", isValidEmail("invalid-email")); // 0 (false)
    printf("%d\n", isValidEmail("another.test@sub.example.co.uk")); // 1 (true)
    printf("%d\n", isValidEmail("test+category@gmail.com")); // 1 (true)
    printf("%d\n", isValidEmail("")); // 0 (false)
    return 0;
}