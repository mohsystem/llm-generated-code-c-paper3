#include <stdio.h>
#include <string.h>

void escapeHtml(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '&': strcat(output, "&amp;"); break;
            case '"': strcat(output, "&quot;"); break;
            case '\'': strcat(output, "&#39;"); break;
            default: strncat(output, input, 1);
        }
        input++;
    }
}

void displayInput(const char *input) {
    char escaped[1024] = "";
    escapeHtml(input, escaped);
    printf("%s\n", escaped);
}

int main() {
    displayInput("Hello, World!");
    displayInput("<script>alert('XSS')</script>");
    displayInput("Welcome to the site");
    displayInput("John & Jane's Adventure");
    displayInput("<b>Bold Text</b>");
    return 0;
}