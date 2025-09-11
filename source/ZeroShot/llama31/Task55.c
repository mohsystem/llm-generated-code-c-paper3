#include <stdio.h>
#include <regex.h>

bool isValidEmail(const char* email) {
    regex_t regex;
    const char* pattern = "^(?=.{1,64}@)[\\w_-]+(\\.[\\w_-]+)*@[^-][\\w-]+(\\.[\\w-]+)*(\\.[\\w]{2,})$";
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return false;
    }
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

int main() {
    const char* testCases[] = {"test@example.com", "invalid.email", "test@example.co.uk", "test@.com", "test@example"};
    for (int i = 0; i < 5; i++) {
        printf("%s is valid: %s\n", testCases[i], isValidEmail(testCases[i]) ? "true" : "false");
    }
    return 0;
}