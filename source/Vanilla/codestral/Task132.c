#include <stdio.h>

void logEvent(const char* event) {
    // Logic to log the event would go here
    printf("Logged event: %s\n", event);
}

int main() {
    logEvent("User logged in");
    logEvent("Unauthorized access attempt");
    // add more test cases
    return 0;
}