#include <stdio.h>
#include <time.h>
#include <string.h>

void logSecurityEvent(const char *eventType, const char *description) {
    FILE *file = fopen("security_log.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening log file.\n");
        return;
    }

    time_t now;
    time(&now);
    char timestamp[20]; 
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    fprintf(file, "%s - %s - %s\n", timestamp, eventType, description);
    fclose(file);
}

int main() {
    logSecurityEvent("Login Attempt", "User 'admin' logged in successfully.");
    logSecurityEvent("File Access", "User 'guest' attempted to access restricted file 'data.txt'.");
    logSecurityEvent("Network Connection", "Suspicious connection from IP address 192.168.1.100.");
    logSecurityEvent("System Alert", "High CPU usage detected.");
    logSecurityEvent("Logout", "User 'admin' logged out.");
    return 0;
}