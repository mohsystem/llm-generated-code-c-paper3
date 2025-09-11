#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>


bool isValidAdminPassword(const char* password) {
    if (password == NULL || strlen(password) < 12) {
        return false;
    }

    // Check for at least one uppercase letter, one lowercase letter, and one digit
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9]).{12,}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, password, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return true;
    } else if (reti == REG_NOMATCH) {
        return false;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }
}

int main() {
    // Test cases
    const char* passwords[] = {
         "Admin123", // Invalid: Too short
        "admin12345678", // Invalid: No uppercase
        "ADMIN12345678", // Invalid: No lowercase
        "AdminPassword", // Invalid: No digit
        "AdminPassword123", // Valid
        NULL, //Invalid: null password
        "1234567890ABcd", // Valid
        "          ", // Invalid: Too short and no required characters
        "!@#$%^&*()_+=-`~[]\';,./{}|:\"<>?", // Invalid: No required characters
        "Admin1" // Invalid: Too short
    };
    bool expected[] = {
       false,
        false,
        false,
        false,
        true,
        false,
        true,
        false,
        false,
        false
    };


    for (int i = 0; i < sizeof(passwords) / sizeof(passwords[0]); ++i) {
        bool result = isValidAdminPassword(passwords[i]);
        printf("Password: \"%s\" - Valid: %s, Expected: %s\n", passwords[i] ? passwords[i] : "NULL", result ? "true" : "false", expected[i] ? "true" : "false");
    }

    return 0;
}