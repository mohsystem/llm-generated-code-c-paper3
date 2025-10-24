
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_RESOURCE_NAME 256
#define MAX_RESOURCE_DESC 512
#define MAX_RESOURCES 10

/* Structure to hold resource information */
typedef struct {
    char name[MAX_RESOURCE_NAME];
    char description[MAX_RESOURCE_DESC];
} Resource;

/* Resource access control structure */
typedef struct {
    Resource resources[MAX_RESOURCES];
    size_t count;
} ResourceAccessControl;

/* Initialize the resource access control with whitelisted resources */
void initResourceControl(ResourceAccessControl* rac) {
    if (rac == NULL) {
        return;
    }
    
    rac->count = 0;
    
    /* Add whitelisted resources with safe string copying */
    strncpy(rac->resources[rac->count].name, "document1", MAX_RESOURCE_NAME - 1);
    rac->resources[rac->count].name[MAX_RESOURCE_NAME - 1] = '\0';
    strncpy(rac->resources[rac->count].description, 
            "Public document about services", MAX_RESOURCE_DESC - 1);
    rac->resources[rac->count].description[MAX_RESOURCE_DESC - 1] = '\0';
    rac->count++;
    
    strncpy(rac->resources[rac->count].name, "document2", MAX_RESOURCE_NAME - 1);
    rac->resources[rac->count].name[MAX_RESOURCE_NAME - 1] = '\0';
    strncpy(rac->resources[rac->count].description, 
            "User guide for application", MAX_RESOURCE_DESC - 1);
    rac->resources[rac->count].description[MAX_RESOURCE_DESC - 1] = '\0';
    rac->count++;
    
    strncpy(rac->resources[rac->count].name, "report_2024", MAX_RESOURCE_NAME - 1);
    rac->resources[rac->count].name[MAX_RESOURCE_NAME - 1] = '\0';
    strncpy(rac->resources[rac->count].description, 
            "Annual report data", MAX_RESOURCE_DESC - 1);
    rac->resources[rac->count].description[MAX_RESOURCE_DESC - 1] = '\0';
    rac->count++;
    
    strncpy(rac->resources[rac->count].name, "config_template", MAX_RESOURCE_NAME - 1);
    rac->resources[rac->count].name[MAX_RESOURCE_NAME - 1] = '\0';
    strncpy(rac->resources[rac->count].description, 
            "Configuration template", MAX_RESOURCE_DESC - 1);
    rac->resources[rac->count].description[MAX_RESOURCE_DESC - 1] = '\0';
    rac->count++;
}
/* Validate resource name to prevent path traversal and injection attacks */
bool isValidResourceName(const char* resourceName) {
    size_t len;
    size_t i;

    if (resourceName == NULL) {
        return false;
    }

    len = strlen(resourceName);

    /* Check length bounds */
    if (len == 0 || len >= MAX_RESOURCE_NAME) {
        return false;
    }

    /* Reject names starting with dot (hidden files) */
    if (resourceName[0] == '.') {
        return false;
    }

    /* Check each character for validity */
    for (i = 0; i < len; i++) {
        char c = resourceName[i];

        /* Reject path separators */
        if (c == '/' || c == '\\' || c == ':') {
            return false;
        }

        /* Reject null bytes */
        if (c == '\0') {
            break;
        }

        /* Only allow alphanumeric, underscore, hyphen, and dot */
        if (!isalnum((unsigned char)c) && c != '_' && c != '-' && c != '.') {
            return false;
        }
    }

    /* Check for path traversal sequences */
    if (strstr(resourceName, "..") != NULL) {
        return false;
    }

    return true;
}

/* Access resource with strict validation and whitelist checking */
int accessResource(const ResourceAccessControl* rac, const char* resourceName,
                   char* output, size_t outputSize) {
    size_t i;

    if (rac == NULL || resourceName == NULL || output == NULL || outputSize == 0) {
        return -1;
    }

    /* Initialize output buffer */
    output[0] = '\0';

    /* Validate resource name format */
    if (!isValidResourceName(resourceName)) {
        snprintf(output, outputSize, "Error: Invalid resource name format");
        return -1;
    }

    /* Search for resource in whitelist */
    for (i = 0; i < rac->count; i++) {
        if (strcmp(rac->resources[i].name, resourceName) == 0) {
            /* Resource found - return access granted message */
            snprintf(output, outputSize, "Access granted to: %s - %s",
                     rac->resources[i].name, rac->resources[i].description);
            return 0;
        }
    }

    /* Resource not found in whitelist */
    snprintf(output, outputSize, "Error: Resource not found or access denied");
    return -1;
}

/* List all available resources */
void listResources(const ResourceAccessControl* rac) {
    size_t i;

    if (rac == NULL) {
        return;
    }

    printf("[Available Resources]:\n");
    for (i = 0; i < rac->count; i++) {
        printf("  - %s\n", rac->resources[i].name);
    }
}

/* Safe input reading with bounds checking */
bool safeReadLine(char* buffer, size_t bufferSize) {
    char* newline;

    if (buffer == NULL || bufferSize == 0) {
        return false;
    }

    /* Read line with size limit */
    if (fgets(buffer, (int)bufferSize, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    /* Remove trailing newline */
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    /* Remove trailing whitespace */
    while (strlen(buffer) > 0 && isspace((unsigned char)buffer[strlen(buffer) - 1])) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    return true;
}

int main(void) {
    ResourceAccessControl rac;
    char output[1024];

    /* Initialize with NULL checks */
    memset(&rac, 0, sizeof(ResourceAccessControl));
    memset(output, 0, sizeof(output));

    initResourceControl(&rac);

    printf("=== Resource Access Control System ===\n");

    /* Test case 1: Valid resource access */
    printf("\n[Test 1] Accessing 'document1':\n");
    if (accessResource(&rac, "document1", output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        printf("%s\n", output);
    }

    /* Test case 2: Another valid resource */
    printf("\n[Test 2] Accessing 'report_2024':\n");
    if (accessResource(&rac, "report_2024", output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        printf("%s\n", output);
    }

    /* Test case 3: Path traversal attempt (blocked) */
    printf("\n[Test 3] Path traversal attempt '../etc/passwd':\n");
    accessResource(&rac, "../etc/passwd", output, sizeof(output));
    printf("%s\n", output);

    /* Test case 4: Non-existent resource */
    printf("\n[Test 4] Non-existent resource 'secret_data':\n");
    accessResource(&rac, "secret_data", output, sizeof(output));
    printf("%s\n", output);

    /* Test case 5: Invalid characters in resource name */
    printf("\n[Test 5] Invalid resource name 'doc/file':\n");
    accessResource(&rac, "doc/file", output, sizeof(output));
    printf("%s\n", output);

    /* List all available resources */
    printf("\n");
    listResources(&rac);

    return 0;
}
