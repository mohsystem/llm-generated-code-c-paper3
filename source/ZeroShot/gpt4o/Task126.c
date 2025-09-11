#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* redirectToPage(const char* userInput) {
    struct { const char* key; const char* value; } pageMap[] = {
        {"home", "HomePage"},
        {"profile", "UserProfilePage"},
        {"settings", "SettingsPage"},
        {"help", "HelpPage"},
        {"contact", "ContactPage"}
    };
    int mapSize = sizeof(pageMap) / sizeof(pageMap[0]);
    
    char lowerInput[50];
    strncpy(lowerInput, userInput, sizeof(lowerInput));
    for (int i = 0; lowerInput[i]; i++) {
        lowerInput[i] = tolower(lowerInput[i]);
    }
    
    for (int i = 0; i < mapSize; i++) {
        if (strcmp(lowerInput, pageMap[i].key) == 0) {
            return pageMap[i].value;
        }
    }
    
    return "ErrorPage";
}

int main() {
    printf("%s\n", redirectToPage("home"));
    printf("%s\n", redirectToPage("PROFILE"));
    printf("%s\n", redirectToPage("Settings"));
    printf("%s\n", redirectToPage("Help"));
    printf("%s\n", redirectToPage("unknown"));
    return 0;
}