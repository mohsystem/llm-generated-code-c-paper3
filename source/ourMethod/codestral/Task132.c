#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void logEvent(const char* event) {
    if (event == NULL || strlen(event) == 0) {
        fprintf(stderr, "Event cannot be null or empty\n");
        exit(EXIT_FAILURE);
    }
    printf("Security Event: %s\n", event);
}

void monitorEvents() {
    // Add your monitoring logic here
}

int main() {
    logEvent("User login attempt");
    logEvent("Unauthorized access attempt");
    logEvent("Password change");
    return 0;
}