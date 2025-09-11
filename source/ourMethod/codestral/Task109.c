#include <stdio.h>
#include <regex.h>

int isValidInput(const char *input) {
    regex_t regex;
    int reti;
    const char *pattern = "^[a-zA-Z0-9]{5,10}$";

    reti = regcomp(&regex, pattern, 0);
    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if(!reti) {
        return 1;
    }
    else if(reti == REG_NOMATCH) {
        return 0;
    }
    else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main() {
    char input[100];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    if(isValidInput(input)) {
        printf("Input is valid.\n");
    } else {
        printf("Input is invalid.\n");
    }
    return 0;
}