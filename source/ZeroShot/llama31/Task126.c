#include <stdio.h>
#include <string.h>
#include <ctype.h>

void redirectUser(const char* code, const char* redirects[], const char* urls[], int size) {
    char trimmedCode[1024];
    strcpy(trimmedCode, code);
    trimmedCode[strcspn(trimmedCode, " \t\r\n")] = 0; // trim trailing whitespace

    for (int i = 0; i < strlen(trimmedCode); i++) {
        trimmedCode[i] = tolower(trimmedCode[i]);
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(trimmedCode, redirects[i]) == 0) {
            printf("Redirecting to: %s\n", urls[i]);
            return;
        }
    }

    printf("Invalid code\n");
}

int main() {
    const char* redirects[] = {"one", "two", "three"};
    const char* urls[] = {"https://example.com/one", "https://example.com/two", "https://example.com/three"};
    int size = sizeof(redirects) / sizeof(redirects[0]);

    for (int i = 0; i < 5; i++) {
        char code[1024];
        printf("Enter your code here: ");
        fgets(code, sizeof(code), stdin);
        code[strcspn(code, "\n")] = 0; // remove newline character
        redirectUser(code, redirects, urls, size);
    }

    return 0;
}