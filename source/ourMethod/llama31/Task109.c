#include <regex.h>
#include <stdio.h>

int validateInput(const char* input, const char* regex) {
    regex_t regex Compiled;
    int reti = regcomp(&regexCompiled, regex, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regexCompiled, input, 0, NULL, 0);
    regfree(&regexCompiled);
    return !reti;
}

int main() {
    const char* inputs[] = {"test@example.com", "invalid-email", "123-456-7890", "invalid-phone"};
    const char* emailRegex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    const char* phoneRegex = "^\\d{3}-\\d{3}-\\d{4}$";

    printf("Email: %s - %d\n", inputs[0], validateInput(inputs[0], emailRegex));
    printf("Email: %s - %d\n", inputs[1], validateInput(inputs[1], emailRegex));
    printf("Phone: %s - %d\n", inputs[2], validateInput(inputs[2], phoneRegex));
    printf("Phone: %s - %d\n", inputs[3], validateInput(inputs[3], phoneRegex));

    return 0;
}