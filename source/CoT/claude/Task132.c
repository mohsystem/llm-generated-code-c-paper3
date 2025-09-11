
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_ENTRY_LENGTH 256
#define LOG_FILE "security_events.log"

typedef struct {
    char** entries;
    int count;
} EventBuffer;

EventBuffer* createBuffer() {
    EventBuffer* buffer = (EventBuffer*)malloc(sizeof(EventBuffer));
    if (buffer == NULL) return NULL;
    
    buffer->entries = (char**)malloc(MAX_BUFFER_SIZE * sizeof(char*));
    if (buffer->entries == NULL) {
        free(buffer);
        return NULL;
    }
    
    buffer->count = 0;
    return buffer;
}

void sanitizeInput(const char* input, char* output, size_t outputSize) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\\0' && j < outputSize - 1; i++) {
        if (isalnum(input[i]) || input[i] == ' ' || input[i] == '-' || 
            input[i] == '_' || input[i] == '.') {
            output[j++] = input[i];
        }
    }
    output[j] = '\\0';
}

void flushBuffer(EventBuffer* buffer) {
    if (buffer == NULL || buffer->count == 0) return;

    FILE* file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening log file\\n");
        return;
    }

    for (int i = 0; i < buffer->count; i++) {
        fprintf(file, "%s\\n", buffer->entries[i]);
        free(buffer->entries[i]);
    }

    buffer->count = 0;
    fclose(file);
}

void logEvent(EventBuffer* buffer, const char* eventType, const char* description) {
    if (buffer == NULL) return;

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char timestamp[26];
    strftime(timestamp, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    char sanitizedType[MAX_ENTRY_LENGTH];
    char sanitizedDesc[MAX_ENTRY_LENGTH];
    sanitizeInput(eventType, sanitizedType, sizeof(sanitizedType));
    sanitizeInput(description, sanitizedDesc, sizeof(sanitizedDesc));

    char* entry = (char*)malloc(MAX_ENTRY_LENGTH * sizeof(char));
    if (entry == NULL) return;

    snprintf(entry, MAX_ENTRY_LENGTH, "[%s] %s: %s", 
             timestamp, sanitizedType, sanitizedDesc);

    buffer->entries[buffer->count++] = entry;
    printf("%s\\n", entry);

    if (buffer->count >= MAX_BUFFER_SIZE) {
        flushBuffer(buffer);
    }
}

void destroyBuffer(EventBuffer* buffer) {
    if (buffer == NULL) return;
    
    flushBuffer(buffer);
    free(buffer->entries);
    free(buffer);
}

int main() {
    EventBuffer* logger = createBuffer();
    if (logger == NULL) {
        fprintf(stderr, "Failed to create logger\\n");
        return 1;
    }

    // Test case 1: Login attempt
    logEvent(logger, "LOGIN", "User admin attempted login from IP 192.168.1.1");
    
    // Test case 2: Failed authentication
    logEvent(logger, "AUTH_FAIL", "Invalid credentials for user guest");
    
    // Test case 3: File access
    logEvent(logger, "FILE_ACCESS", "User admin accessed sensitive_file.txt");
    
    // Test case 4: Configuration change
    logEvent(logger, "CONFIG_CHANGE", "Firewall rules updated by system");
    
    // Test case 5: System alert
    logEvent(logger, "ALERT", "Multiple failed login attempts detected");

    destroyBuffer(logger);
    return 0;
}
