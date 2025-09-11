// C
#include <stdio.h>

void logEvent(const char* event) {
    printf("Security Event: %s\n", event);
    // Here you would add your monitoring and logging logic
}

int main() {
    logEvent("User login attempt");
    logEvent("Unauthorized access attempt");
    // Add more test cases as needed
    return 0;
}