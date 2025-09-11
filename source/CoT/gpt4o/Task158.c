#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize(const char *input, char *output) {
    regex_t regex;
    regcomp(&regex, "[^a-zA-Z0-9 .,-]", REG_EXTENDED);
    regmatch_t match;
    int len = strlen(input);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (regexec(&regex, &input[i], 1, &match, 0) == REG_NOMATCH) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    regfree(&regex);
}

char *execute_command(const char *user_input) {
    static char buffer[128];
    char sanitized_input[128];
    sanitize(user_input, sanitized_input);
    snprintf(buffer, sizeof(buffer), "echo %s", sanitized_input);
    FILE *pipe = popen(buffer, "r");
    if (!pipe) return "Error: failed to open pipe!";
    fgets(buffer, sizeof(buffer), pipe);
    pclose(pipe);
    return buffer;
}

int main() {
    printf("%s\n", execute_command("Hello World"));
    printf("%s\n", execute_command("Hello; rm -rf /"));
    printf("%s\n", execute_command("1234567890"));
    printf("%s\n", execute_command("!@#$%^&*()_+"));
    printf("%s\n", execute_command("C test"));
    return 0;
}