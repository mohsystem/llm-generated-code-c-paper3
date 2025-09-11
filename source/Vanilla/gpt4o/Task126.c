#include <stdio.h>
#include <string.h>

const char* redirectToPage(const char* userInput) {
    if (strcasecmp(userInput, "home") == 0) {
        return "Redirecting to Home Page";
    } else if (strcasecmp(userInput, "profile") == 0) {
        return "Redirecting to Profile Page";
    } else if (strcasecmp(userInput, "settings") == 0) {
        return "Redirecting to Settings Page";
    } else if (strcasecmp(userInput, "help") == 0) {
        return "Redirecting to Help Page";
    } else {
        return "Page not found";
    }
}

int main() {
    printf("%s\n", redirectToPage("home"));
    printf("%s\n", redirectToPage("profile"));
    printf("%s\n", redirectToPage("settings"));
    printf("%s\n", redirectToPage("help"));
    printf("%s\n", redirectToPage("logout"));
    return 0;
}