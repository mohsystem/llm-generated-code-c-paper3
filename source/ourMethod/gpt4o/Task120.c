#include <stdio.h>
#include <string.h>
#include <regex.h>

void displayInputOnWebPage(const char* userInput) {
    regex_t regex;
    regcomp(&regex, "<[^>]*>", REG_EXTENDED);
    char buffer[1024];
    regmatch_t match;
    
    strcpy(buffer, userInput);
    while (regexec(&regex, buffer, 1, &match, 0) == 0) {
        buffer[match.rm_so] = '\0';
        strcat(buffer, buffer + match.rm_eo);
    }

    printf("%s\n", buffer);
    regfree(&regex);
}

int main() {
    displayInputOnWebPage("<script>alert('test')</script>"); // XSS attempt
    displayInputOnWebPage("<b>Hello</b>"); // Bold text
    displayInputOnWebPage("Plain text"); // Plain text
    displayInputOnWebPage("<img src='x' onerror='alert(1)'>"); // XSS attempt
    displayInputOnWebPage("<a href='http://example.com'>Link</a>"); // Link
    return 0;
}