#include <stdio.h>

void logSecurityEvent(const char* event) {
    printf("Security event: %s\n", event);
}

int main() {
    logSecurityEvent("Unauthorized access attempt");
    logSecurityEvent("Suspicious network activity");
    // add more test cases as needed
    return 0;
}