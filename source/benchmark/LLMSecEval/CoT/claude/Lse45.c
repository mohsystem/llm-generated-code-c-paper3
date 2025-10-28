
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#define SAFE_DIRECTORY "/var/safe_files/"
#define MAX_FILENAME 256
#define MAX_CONTENT 65536

char* readFileFromSafeDirectory(const char* filename) {
    static char result[MAX_CONTENT];
    char sanitizedFilename[MAX_FILENAME];
    char fullPath[PATH_MAX];
    char resolvedPath[PATH_MAX];
    char safeDirResolved[PATH_MAX];
    FILE* file;
    struct stat statbuf;
    size_t bytesRead;
    
    // Input validation
    if (filename == NULL || strlen(filename) == 0) {
        strcpy(result, "Error: Invalid filename");
        return result;
    }
    
    // Sanitize filename - remove path separators
    int j = 0;
    for (int i = 0; filename[i] != '\0' && j < MAX_FILENAME - 1; i++) {
        if (filename[i] != '/' && filename[i] != '\\\\') {            sanitizedFilename[j++] = filename[i];        }    }    sanitizedFilename[j] = '\0';
    // Resolve safe directory canonical path
    if (realpath(SAFE_DIRECTORY, safeDirResolved) == NULL) {        strcpy(result, "Error: Safe directory not accessible");        return result;    }
    // Build full path
    snprintf(fullPath, PATH_MAX, "%s/%s", safeDirResolved, sanitizedFilename);
    // // Resolve requested file canonical path
    if (realpath(fullPath, resolvedPath) == NULL) {        strcpy(result, "Error: File not found");        return result;    }
    // Security check: ensure the resolved path is within safe directory
    if (strncmp(resolvedPath, safeDirResolved, strlen(safeDirResolved)) != 0) {
        strcpy(result, "Error: Access denied - file outside safe directory");        return result;
    }        // Check if it's a regular file
    if (stat(resolvedPath, &statbuf) != 0) {
        strcpy(result, "Error: Cannot access file");
        return result;
    }
    
    if (!S_ISREG(statbuf.st_mode)) {
        strcpy(result, "Error: Not a regular file");
        return result;
    }
    
    // Read file content
    file = fopen(resolvedPath, "r");
    if (file == NULL) {
        strcpy(result, "Error: Unable to open file");
        return result;
    }
    
    bytesRead = fread(result, 1, MAX_CONTENT - 1, file);
    result[bytesRead] = '\0';
    fclose(file);
    
    return result;
}

int main() {
    // Test cases
    printf("Test 1 - Valid file:%s",
           readFileFromSafeDirectory("document.txt"));
    
    printf(" Test 2 - Path traversal attempt:%s",
           readFileFromSafeDirectory("../etc/passwd"));
    
    printf("Test 3 - Absolute path attempt:%s",
           readFileFromSafeDirectory("/etc/passwd"));
    
    printf("Test 4 - NULL filename:%s",
           readFileFromSafeDirectory(NULL));
    
    printf("Test 5 - Non-existent file:%s",
           readFileFromSafeDirectory("nonexistent.txt"));
    
    return 0;
}
