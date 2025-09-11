
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS 100
#define MAX_STRING_LENGTH 256

struct SecurityEvent {
    char eventType[MAX_STRING_LENGTH];
    char description[MAX_STRING_LENGTH];
    time_t timestamp;
};

struct SecurityMonitor {
    struct SecurityEvent events[MAX_EVENTS];
    int eventCount;
};

void initMonitor(struct SecurityMonitor* monitor) {
    monitor->eventCount = 0;
}

void logEvent(struct SecurityMonitor* monitor, const char* eventType, const char* description) {
    if (monitor->eventCount >= MAX_EVENTS) {
        printf("Event log is full\\n");
        return;
    }
    
    struct SecurityEvent* event = &monitor->events[monitor->eventCount];
    strncpy(event->eventType, eventType, MAX_STRING_LENGTH - 1);
    strncpy(event->description, description, MAX_STRING_LENGTH - 1);
    event->timestamp = time(NULL);
    
    char timeStr[26];
    ctime_r(&event->timestamp, timeStr);
    timeStr[24] = '\\0';  // Remove newline
    
    printf("Logged: [%s] %s: %s\\n", timeStr, event->eventType, event->description);
    
    monitor->eventCount++;
}

void displayLogs(const struct SecurityMonitor* monitor) {
    printf("\\nSecurity Event Log:\\n");
    for(int i = 0; i < monitor->eventCount; i++) {
        const struct SecurityEvent* event = &monitor->events[i];
        char timeStr[26];
        ctime_r(&event->timestamp, timeStr);
        timeStr[24] = '\\0';  // Remove newline
        printf("[%s] %s: %s\\n", timeStr, event->eventType, event->description);
    }
}

int main() {
    struct SecurityMonitor monitor;
    initMonitor(&monitor);
    
    // Test Case 1: Login attempt
    logEvent(&monitor, "LOGIN_ATTEMPT", "User 'admin' logged in successfully");
    
    // Test Case 2: Failed login
    logEvent(&monitor, "LOGIN_FAILED", "Multiple failed attempts from IP 192.168.1.100");
    
    // Test Case 3: File access
    logEvent(&monitor, "FILE_ACCESS", "Sensitive file 'data.txt' accessed by user 'john'");
    
    // Test Case 4: Configuration change
    logEvent(&monitor, "CONFIG_CHANGE", "Firewall rules updated");
    
    // Test Case 5: System alert
    logEvent(&monitor, "SYSTEM_ALERT", "Unusual network activity detected");
    
    // Display all logs
    displayLogs(&monitor);
    
    return 0;
}
