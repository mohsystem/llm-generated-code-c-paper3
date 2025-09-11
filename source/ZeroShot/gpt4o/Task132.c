#include <stdio.h>
#include <string.h>

#define MAX_LOGS 100
#define MAX_LOG_LENGTH 256

typedef struct {
    char logs[MAX_LOGS][MAX_LOG_LENGTH];
    int log_count;
} Task132;

void init_logger(Task132* logger) {
    logger->log_count = 0;
}

void log_event(Task132* logger, const char* event) {
    if (event && strlen(event) > 0 && logger->log_count < MAX_LOGS) {
        strncpy(logger->logs[logger->log_count], event, MAX_LOG_LENGTH - 1);
        logger->logs[logger->log_count][MAX_LOG_LENGTH - 1] = '\0'; // ensure null-terminated
        logger->log_count++;
    }
}

void get_logs(Task132* logger) {
    for (int i = 0; i < logger->log_count; i++) {
        printf("%s\n", logger->logs[i]);
    }
}

int main() {
    Task132 securityLogger;
    init_logger(&securityLogger);

    log_event(&securityLogger, "User login attempt");
    log_event(&securityLogger, "File accessed");
    log_event(&securityLogger, "Unauthorized access detected");
    log_event(&securityLogger, "Password change request");
    log_event(&securityLogger, "System settings modified");

    get_logs(&securityLogger);

    return 0;
}