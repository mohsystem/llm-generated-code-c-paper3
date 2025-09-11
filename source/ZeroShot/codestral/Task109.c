#include <stdio.h>
#include <regex.h>

int validateInput(const char* input) {
    // A simple regex that matches any non-empty string
    const char* regex = "^(.*[^\\s])";

    regex_t preg;
    int ret;

    ret = regcomp(&preg, regex, 0);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    ret = regexec(&preg, input, 0, NULL, 0);
    regfree(&preg);

    return ret == 0;
}

int main() {
    printf("%d\n", validateInput("Hello, World!")); // Expected: 1
    printf("%d\n", validateInput(" ")); // Expected: 0
    printf("%d\n", validateInput("")); // Expected: 0
    printf("%d\n", validateInput("12345")); // Expected: 1
    printf("%d\n", validateInput("Test@123")); // Expected: 1

    return 0;
}