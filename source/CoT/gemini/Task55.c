#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidEmail(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0;
    }

    // Regular expression pattern for email validation
    const char *regex_str = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, regex_str, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0; // or handle the error appropriately
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex); 

    if (!reti) {
        return 1; // Match found (valid email)
    } else if (reti == REG_NOMATCH) {
        return 0; // No match (invalid email)
    } else {
        fprintf(stderr, "Regex match failed\n");
        return 0; // or handle the error appropriately
    }
}

int main() {
    char email1[] = "test@example.com";
    char email2[] = "invalid.email";
    char email3[] = "another.test@subdomain.example.co.uk";
    char email4[] = "12345@numbers.com";
    char email5[] = "test+mailing@example.org";

    printf("%d\n", isValidEmail(email1)); // Output: 1 (true)
    printf("%d\n", isValidEmail(email2)); // Output: 0 (false)
    printf("%d\n", isValidEmail(email3)); // Output: 1 (true)
    printf("%d\n", isValidEmail(email4)); // Output: 1 (true)
    printf("%d\n", isValidEmail(email5)); // Output: 1 (true)

    return 0;
}