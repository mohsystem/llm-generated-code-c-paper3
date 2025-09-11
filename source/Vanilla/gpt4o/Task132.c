#include <stdio.h>

void logSecurityEvent(const char *event) {
    printf("Security Event: %s\n", event);
}

int main() {
    logSecurityEvent("User login attempt");
    logSecurityEvent("Password change request");
    logSecurityEvent("Unauthorized access detected");
    logSecurityEvent("User logout");
    logSecurityEvent("Failed login attempt");
    return 0;
}