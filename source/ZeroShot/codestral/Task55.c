#include <stdio.h>
#include <regex.h>

int isValidEmail(const char *email) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9_+&*-]+(?:\\."
                          "[a-zA-Z0-9_+&*-]+)*@"
                          "(?:[a-zA-Z0-9-]+\\.)+[a-z"
                          "A-Z]{2,7}$";

    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    if (!reti) {
        printf("Match\n");
        return 1;
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

    regfree(&regex);
}

int main() {
    printf("%d\n", isValidEmail("test@example.com"));  // 1
    printf("%d\n", isValidEmail("test@example"));     // 0
    printf("%d\n", isValidEmail("test@.com"));         // 0
    printf("%d\n", isValidEmail("test@example..com")); // 0
    printf("%d\n", isValidEmail("test@example-com"));  // 0
    return 0;
}