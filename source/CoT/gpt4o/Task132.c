#include <stdio.h>

void logEvent(const char* event) {
    // Log the security event
    printf("Security Event Logged: %s\n", event);
}

int main() {
    // Test cases
    logEvent("User login attempt");
    logEvent("File access violation");
    logEvent("Unauthorized access");
    logEvent("System settings change");
    logEvent("Suspicious network activity");

    return 0;
}