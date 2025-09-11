#include <stdio.h>
#include <regex.h>

int isValidEmail(char *email) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$", 0);
    if(reti) {
        printf("Could not compile regex\n");
        return 0;
    }
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int main() {
    char *emails[] = {"test.email+alex@leetcode.com", "test.email.leet+alex@code.com"};
    for (int i = 0; i < 2; i++) {
        printf("%s: %d\n", emails[i], isValidEmail(emails[i]));
    }
    return 0;
}