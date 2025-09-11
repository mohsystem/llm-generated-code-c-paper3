#include<regex.h>
#include<stdio.h>
int isValidEmail(const char *email) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *regex_str = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
    regcomp(&regex, regex_str, 0);
    reti = regexec(&regex, email, 0, NULL, 0);
    if (!reti)
        return 1;
    else if (reti == REG_NOMATCH)
        return 0;
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return -1;
    }
    regfree(&regex);
}
int main() {
    printf("%d\n", isValidEmail("test@example.com")); // 1 (true)
    printf("%d\n", isValidEmail("test@.com")); // 0 (false)
    printf("%d\n", isValidEmail("test@example")); // 0 (false)
    printf("%d\n", isValidEmail("test@example.c")); // 0 (false)
    printf("%d\n", isValidEmail("test@example.com.au")); // 1 (true)
    return 0;
}