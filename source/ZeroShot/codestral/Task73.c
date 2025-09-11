#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

bool isValidPassword(const char* password) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char* regex_string = "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$";

    reti = regcomp(&regex, regex_string, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, password, 0, NULL, 0);
    if (!reti) {
        return true;
    } else if (reti == REG_NOMATCH) {
        return false;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }

    regfree(&regex);
}

int main() {
    printf("%s\n", isValidPassword("Admin@123") ? "true" : "false"); // true
    printf("%s\n", isValidPassword("admin123") ? "true" : "false"); // false
    printf("%s\n", isValidPassword("Admin123") ? "true" : "false"); // false
    printf("%s\n", isValidPassword("Admin@12") ? "true" : "false"); // false
    printf("%s\n", isValidPassword("Admin@1234") ? "true" : "false"); // true
    return 0;
}