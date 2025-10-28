
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/types.h>
#endif

#define SAFE_DIRECTORY "safe_files"
#define MAX_FILENAME_LEN 256
#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_CONTENT_SIZE (10 * 1024 * 1024 + 1024)

const char* ALLOWED_EXTENSIONS[] = {".txt", ".log", ".csv", ".json", ".xml", NULL};

int isAllowedExtension(const char* fileName) {
    if (fileName == NULL) return 0;
    
    size_t len = strlen(fileName);
    for (int i = 0; ALLOWED_EXTENSIONS[i] != NULL; i++) {
        size_t extLen = strlen(ALLOWED_EXTENSIONS[i]);
        if (len >= extLen) {
            if (strcasecmp(fileName + len - extLen, ALLOWED_EXTENSIONS[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
void sanitizeFileName(char* dest, const char* src, size_t destSize) {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0' && j < destSize - 1; i++) {
        if (src[i] != '.' || (i > 0 && src[i - 1] != '.')) {
            if (src[i] != '/' && src[i] != '\\') {
                dest[j++] = src[i];
            }
        }
    }
    dest[j] = '\0';
}

int fileExists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode));
}

long getFileSize(const char* path) {
    struct stat buffer;
    if (stat(path, &buffer) == 0) {
        return buffer.st_size;
    }
    return -1;
}

char* retrieveFile(const char* fileName) {
    static char result[MAX_CONTENT_SIZE];
    char safeName[MAX_FILENAME_LEN];
    char filePath[MAX_FILENAME_LEN + 50];
    FILE* file;
    long fileSize;

    // Input validation
    if (fileName == NULL || strlen(fileName) == 0) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: File name cannot be empty");
        return result;
    }

    // Sanitize filename
    sanitizeFileName(safeName, fileName, MAX_FILENAME_LEN);

    // Validate file extension
    if (!isAllowedExtension(safeName)) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: File extension not allowed");
        return result;
    }

    // Create safe directory if it doesn't exist
    #ifdef _WIN32
    mkdir(SAFE_DIRECTORY);
    #else
    mkdir(SAFE_DIRECTORY, 0755);
    #endif

    // Build safe file path
    snprintf(filePath, sizeof(filePath), "%s/%s", SAFE_DIRECTORY, safeName);

    // Additional validation
    if (strstr(filePath, "..") != NULL) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: Access denied - path traversal detected");
        return result;
    }

    // Check if file exists
    if (!fileExists(filePath)) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: File not found");
        return result;
    }

    // Check file size
    fileSize = getFileSize(filePath);
    if (fileSize > MAX_FILE_SIZE || fileSize < 0) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: File too large or invalid");
        return result;
    }

    // Read file content
    file = fopen(filePath, "r");
    if (file == NULL) {
        snprintf(result, MAX_CONTENT_SIZE, "Error: Cannot open file");
        return result;
    }

    strcpy(result, "Success: File retrieved\n");
    size_t offset = strlen(result);
    size_t bytesRead = fread(result + offset, 1, MAX_CONTENT_SIZE - offset - 1, file);
    result[offset + bytesRead] = '\0';

    fclose(file);
    return result;
}


void setupTestFiles(void) {
    FILE* file;
    char path[MAX_FILENAME_LEN];
    
    #ifdef _WIN32
    mkdir(SAFE_DIRECTORY);
    #else
    mkdir(SAFE_DIRECTORY, 0755);
    #endif
    
    snprintf(path, sizeof(path), "%s/test1.txt", SAFE_DIRECTORY);
    file = fopen(path, "w");
    if (file != NULL) {
        fprintf(file, "This is a test file content.\\nSecure file retrieval system.");
        fclose(file);
    }
}

int main(void) {
    // Create test files
    setupTestFiles();
    
    // Test Case 1: Valid file retrieval
    printf("Test 1 - Valid file:\\n");
    printf("%s\\n", retrieveFile("test1.txt"));
    
    // Test Case 2: Path traversal attempt
    printf("\\nTest 2 - Path traversal attempt:\\n");
    printf("%s\\n", retrieveFile("../../../etc/passwd"));
    
    // Test Case 3: Invalid extension
    printf("\\nTest 3 - Invalid extension:\\n");
    printf("%s\\n", retrieveFile("malicious.exe"));
    
    // Test Case 4: Empty filename
    printf("\\nTest 4 - Empty filename:\\n");
    printf("%s\\n", retrieveFile(""));
    
    // Test Case 5: Non-existent file
    printf("\\nTest 5 - Non-existent file:\\n");
    printf("%s\\n", retrieveFile("nonexistent.txt"));
    
    return 0;
}
