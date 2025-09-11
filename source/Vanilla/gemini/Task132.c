#include <stdio.h>
#include <time.h>
#include <string.h>

void log_security_event(const char *event_type, const char *description) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%dT%H:%M:%S", tm_info);

    FILE *file = fopen("security_log.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    fprintf(file, "%s - %s - %s\n", buffer, event_type, description);
    fclose(file);
}

int main() {
    log_security_event("Login Attempt", "User 'admin' logged in successfully.");
    log_security_event("File Access", "User 'guest' attempted to access restricted file 'data.txt'.");
    log_security_event("Network Connection", "Incoming connection from IP address 192.168.1.100.");
    log_security_event("Logout", "User 'admin' logged out.");
    log_security_event("System Shutdown", "System initiated shutdown.");
    return 0;
}