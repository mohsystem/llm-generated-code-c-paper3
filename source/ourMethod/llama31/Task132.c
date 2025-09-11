#include <stdio.h>
#include <string.h>

void logSecurityEvent(const char* eventType, const char* eventDetails) {
    // Simulate logging to a file or database
    printf("Security Event: %s - %s\n", eventType, eventDetails);
    // Here you can implement actual logging to a file, database, or other logging mechanism
}

int main() {
    // Test cases
    logSecurityEvent("Alert from antivirus", "Malware detected");
    logSecurityEvent("Firewall alert", "Blocked network traffic");
    logSecurityEvent("Failed login", "Repeated failed logins");
    logSecurityEvent("Unknown host connection", "Connection from unknown IP");
    logSecurityEvent("Privilege escalation", "Change in user privileges");
    return 0;
}