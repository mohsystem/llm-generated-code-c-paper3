#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* redirectUser(const char* userInput) {
    const char* pageMap[][2] = {
        {"home", "HomePage"},
        {"about", "AboutPage"},
        {"contact", "ContactPage"},
        {"services", "ServicesPage"},
        {"login", "LoginPage"}
    };

    char safeInput[100];
    sanitizeInput(userInput, safeInput);

    for (int i = 0; i < 5; i++) {
        if (strcmp(pageMap[i][0], safeInput) == 0) {
            return pageMap[i][1];
        }
    }
    return "ErrorPage";
}

void sanitizeInput(const char* input, char* output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalnum((unsigned char)input[i])) {
            output[j++] = tolower((unsigned char)input[i]);
        }
    }
    output[j] = '\0';
}

int main() {
    printf("%s\n", redirectUser("home"));
    printf("%s\n", redirectUser("about"));
    printf("%s\n", redirectUser("contact"));
    printf("%s\n", redirectUser("services"));
    printf("%s\n", redirectUser("unknown"));
    return 0;
}