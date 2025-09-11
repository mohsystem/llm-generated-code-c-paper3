#include <regex.h>
#include <stdio.h>
#include <stdbool.h>

bool validate_input(const char *input, const char *regex) {
    regex_t regex_compiled;
    regcomp(&regex_compiled, regex, REG_EXTENDED);
    int status = regexec(&regex_compiled, input, 0, NULL, 0);
    regfree(&regex_compiled);
    return status == 0;
}

int main() {
    const char *inputs[] = {"hello", "12345", "hello123", "", "hello@world"};
    const char *regex = "^[a-zA-Z0-9]+$"; // Alphanumeric characters only
    int num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_inputs; i++) {
        printf("%s: %d\n", inputs[i], validate_input(inputs[i], regex));
    }

    return 0;
}