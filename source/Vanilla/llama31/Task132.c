#include <stdio.h>

void logSecurityEvent(const char* event) {
    printf("Security Event: %s\n", event);
}

int main() {
    // Test cases
    logSecurityEvent("Alert from antivirus: Malware detected");
    logSecurityEvent("Firewall alert: Blocked network traffic from unknown host");
    logSecurityEvent("Failed login attempt");
    logSecurityEvent("Change in user privileges: Privilege escalation");
    logSecurityEvent("Connection from unknown IP");
    return 0;
}