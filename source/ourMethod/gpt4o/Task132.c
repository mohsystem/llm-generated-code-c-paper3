#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **events;
    size_t size;
    size_t capacity;
} SecurityLog;

SecurityLog* createSecurityLog() {
    SecurityLog* log = (SecurityLog*)malloc(sizeof(SecurityLog));
    if (log == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    log->events = NULL;
    log->size = 0;
    log->capacity = 0;
    return log;
}

void logEvent(SecurityLog* log, const char* event) {
    if (event == NULL || strlen(event) == 0) {
        fprintf(stderr, "Event description cannot be null or empty.\n");
        return;
    }

    if (log->size == log->capacity) {
        log->capacity = (log->capacity == 0) ? 1 : log->capacity * 2;
        log->events = (char**)realloc(log->events, log->capacity * sizeof(char*));
        if (log->events == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
    }

    log->events[log->size] = strdup(event);
    if (log->events[log->size] == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    log->size++;

    printf("Event logged: %s\n", event);
}

void freeSecurityLog(SecurityLog* log) {
    for (size_t i = 0; i < log->size; i++) {
        free(log->events[i]);
    }
    free(log->events);
    free(log);
}

void printSecurityLog(const SecurityLog* log) {
    printf("Security Log:\n");
    for (size_t i = 0; i < log->size; i++) {
        printf("%s\n", log->events[i]);
    }
}

int main() {
    SecurityLog* log = createSecurityLog();
    logEvent(log, "User login from unknown IP.");
    logEvent(log, "Failed login attempt.");
    logEvent(log, "Suspicious file download detected.");
    logEvent(log, "Unauthorized access attempt.");
    logEvent(log, "Security policy update.");

    printSecurityLog(log);

    freeSecurityLog(log);
    return 0;
}