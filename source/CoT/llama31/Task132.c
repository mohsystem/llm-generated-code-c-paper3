#include <stdio.h>
#include <time.h>

void logEvent(const char* eventType, const char* user, const char* status) {
    FILE* logFile = fopen("security_log.log", "a");
    if (logFile != NULL) {
        time_t now = time(NULL);
        struct tm* ltm = localtime(&now);
        char timestamp[20];
        strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", ltm);
        fprintf(logFile, "%s - %s by %s: %s\n", timestamp, eventType, user, status);
        fclose(logFile);
    }
    printf("%s by %s: %s\n", eventType, user, status);
}

int main() {
    // Test cases
    logEvent("Login attempt", "User1", "Success");
    logEvent("Login attempt", "User2", "Failure");
    logEvent("File access", "User1", "Success");
    logEvent("Network connection", "User3", "Success");
    logEvent("System access", "User4", "Failure");
    return 0;
}