#include <stdio.h>
#include <time.h>
#include <string.h>

void log_security_event(const char *event_type, const char *description) {
    time_t current_time;
    char time_string[20]; 
    time(&current_time);
    strftime(time_string, sizeof(time_string), "%Y-%m-%dT%H:%M:%S", localtime(&current_time));

    FILE *logfile = fopen("security_log.txt", "a");
    if (logfile != NULL) {
        fprintf(logfile, "%s - %s - %s\n", time_string, event_type, description);
        fclose(logfile);
    } else {
        fprintf(stderr, "Error opening log file.\n");
    }
}

int main() {
    log_security_event("Login Attempt", "User 'admin' logged in successfully from IP 192.168.1.1");
    log_security_event("File Access", "User 'guest' attempted to access restricted file '/etc/passwd'");
    log_security_event("Network Connection", "Outbound connection to 8.8.8.8 on port 53");
    log_security_event("System Event", "System restarted unexpectedly");
    log_security_event("Logout", "User 'admin' logged out.");
    return 0;
}