
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS 1000
#define MAX_STR_LEN 256

typedef struct {
    time_t timestamp;
    char eventType[MAX_STR_LEN];
    char description[MAX_STR_LEN];
    char severity[MAX_STR_LEN];
} SecurityEvent;

typedef struct {
    SecurityEvent events[MAX_EVENTS];
    int count;
} SecurityLogger;

SecurityLogger* createLogger() {
    SecurityLogger* logger = (SecurityLogger*)malloc(sizeof(SecurityLogger));
    if (logger != NULL) {
        logger->count = 0;
    }
    return logger;
}

void logSecurityEvent(SecurityLogger* logger, 
                     const char* eventType, 
                     const char* description, 
                     const char* severity) {
    if (logger == NULL || logger->count >= MAX_EVENTS) {
        return;
    }
    
    SecurityEvent* event = &logger->events[logger->count];
    
    event->timestamp = time(NULL);
    strncpy(event->eventType, eventType, MAX_STR_LEN - 1);
    strncpy(event->description, description, MAX_STR_LEN - 1);
    strncpy(event->severity, severity, MAX_STR_LEN - 1);
    
    event->eventType[MAX_STR_LEN - 1] = '\\0';
    event->description[MAX_STR_LEN - 1] = '\\0';
    event->severity[MAX_STR_LEN - 1] = '\\0';
    
    char timeStr[26];
    ctime_r(&event->timestamp, timeStr);
    timeStr[24] = '\\0';  // Remove newline
    
    printf("[%s] %s - %s (Severity: %s)\\n",
           timeStr, event->eventType, event->description, event->severity);
           
    logger->count++;
}

void clearEventLog(SecurityLogger* logger) {
    if (logger != NULL) {
        logger->count = 0;
        printf("Security event log cleared\\n");
    }
}

void destroyLogger(SecurityLogger* logger) {
    free(logger);
}

int main() {
    SecurityLogger* logger = createLogger();
    if (logger == NULL) {
        printf("Failed to create security logger\\n");
        return 1;
    }
    
    // Test case 1: Log login attempt
    logSecurityEvent(logger, "LOGIN_ATTEMPT", 
                    "Failed login attempt from IP 192.168.1.100", "HIGH");
    
    // Test case 2: Log file access
    logSecurityEvent(logger, "FILE_ACCESS", 
                    "Unauthorized access to sensitive file", "CRITICAL");
    
    // Test case 3: Log system update
    logSecurityEvent(logger, "SYSTEM_UPDATE", 
                    "Security patches installed successfully", "LOW");
    
    // Test case 4: Log network event
    logSecurityEvent(logger, "NETWORK", 
                    "Suspicious network traffic detected", "MEDIUM");
    
    // Test case 5: Log configuration change
    logSecurityEvent(logger, "CONFIG_CHANGE", 
                    "Firewall rules modified", "HIGH");
    
    destroyLogger(logger);
    return 0;
}
