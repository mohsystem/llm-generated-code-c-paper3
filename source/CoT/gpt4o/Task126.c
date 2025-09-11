#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

const char* redirectUser(const char* input) {
    char lowerInput[50];
    strcpy(lowerInput, input);
    toLowerCase(lowerInput);

    if (strcmp(lowerInput, "home") == 0) {
        return "Redirecting to Home Page...";
    } else if (strcmp(lowerInput, "profile") == 0) {
        return "Redirecting to Profile Page...";
    } else if (strcmp(lowerInput, "settings") == 0) {
        return "Redirecting to Settings Page...";
    } else if (strcmp(lowerInput, "logout") == 0) {
        return "Redirecting to Logout Page...";
    } else {
        return "Unknown page requested.";
    }
}

int main() {
    const char* testInputs[] = {"home", "profile", "settings", "logout", "unknown"};
    for (int i = 0; i < 5; i++) {
        printf("Input: %s -> %s\n", testInputs[i], redirectUser(testInputs[i]));
    }
    return 0;
}