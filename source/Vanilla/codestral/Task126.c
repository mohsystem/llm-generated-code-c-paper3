#include <stdio.h>
#include <string.h>

const char* redirectPage(const char* userInput) {
    if (strcmp(userInput, "home") == 0) {
        return "Home Page";
    } else if (strcmp(userInput, "profile") == 0) {
        return "Profile Page";
    } else if (strcmp(userInput, "settings") == 0) {
        return "Settings Page";
    } else {
        return "Error 404: Page Not Found";
    }
}

int main() {
    printf("%s\n", redirectPage("home"));
    printf("%s\n", redirectPage("profile"));
    printf("%s\n", redirectPage("settings"));
    printf("%s\n", redirectPage("blog"));
    printf("%s\n", redirectPage("contact"));
    return 0;
}