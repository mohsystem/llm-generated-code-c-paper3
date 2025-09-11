#include <stdio.h>
#include <string.h>
#include <regex.h>

bool isValidInput(const char *input, const char *regex) {
    regex_t compiledRegex;
    int ret = regcompile(&compiledRegex, regex, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return false; // Or handle the error appropriately
    }

    ret = regexec(&compiledRegex, input, 0, NULL, 0);
    regfree(&compiledRegex);
    return ret == 0;
}

int main() {
    // Test cases
    printf("%d\n", isValidInput("12345", "^\\d{5}$")); // True - 5 digits
    printf("%d\n", isValidInput("abcde", "^[a-zA-Z]{5}$")); // True - 5 letters
    printf("%d\n", isValidInput("123456", "^\\d{5}$")); // False - 6 digits
    printf("%d\n", isValidInput("abcd", "^[a-zA-Z]{5}$")); // False - 4 letters
    printf("%d\n", isValidInput("123ab", "^\\d{5}$")); // False - mixed input
    return 0;
}