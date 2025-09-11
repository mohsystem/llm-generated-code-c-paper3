#include <stdio.h>

void logSecurityEvent(const char* event) {
    printf("Security Event: %s\n", event);
}

int main() {
    // Test cases
    logSecurityEvent("Alert from antivirus: Malware infection detected");
    logSecurityEvent("Firewall alert: Blocked network traffic from unknown host");
    logSecurityEvent("Failed login attempt: Multiple attempts from same IP");
    logSecurityEvent("Change in user privileges: Privilege escalation detected");
    logSecurityEvent("Use of new or unknown port: Potential security breach");
    return 0;
}