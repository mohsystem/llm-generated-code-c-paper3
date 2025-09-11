
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>

#define SERVER_FILE_PATH "/secure/files/"
#define MAX_PATH_LENGTH 256
#define MAX_FILE_SIZE 10485760  // 10MB

// Function prototypes
static bool isValidFilename(const char* filename);
static bool isPathSafe(const char* path);
static char* constructPath(const char* basePath, const char* filename);

typedef struct {
    char* data;
    size_t size;
} FileContent;

FileContent* retrieveFile(const char* fileName) {
    if (fileName == NULL || strlen(fileName) == 0) {
        errno = EINVAL;
        return NULL;
    }
    
    // Validate filename
    if (!isValidFilename(fileName)) {
        errno = EINVAL;
        return NULL;
    }
    
    // Construct full path
    char* fullPath = constructPath(SERVER_FILE_PATH, fileName);
    if (fullPath == NULL) {
        return NULL;
    }
    
    // Verify path safety
    if (!isPathSafe(fullPath)) {
        free(fullPath);
        errno = EACCES;
        return NULL;
    }
    
    // Open and read file
    FILE* file = fopen(fullPath, "rb");
    free(fullPath);
    
    if (file == NULL) {
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    
    if (fileSize <= 0 || fileSize > MAX_FILE_SIZE) {
        fclose(file);
        errno = EFBIG;
        return NULL;
    }
    
    // Allocate memory for content
    FileContent* content = malloc(sizeof(FileContent));
    if (content == NULL) {
        fclose(file);
        errno = ENOMEM;
        return NULL;
    }
    
    content->data = malloc(fileSize);
    if (content->data == NULL) {
        free(content);
        fclose(file);
        errno = ENOMEM;
        return NULL;
    }
    
    // Read file content
    size_t bytesRead = fread(content->data, 1, fileSize, file);
    fclose(file);
    
    if (bytesRead != (size_t)fileSize) {
        free(content->data);
        free(content);
        errno = EIO;
        return NULL;
    }
    
    content->size = bytesRead;
    return content;
}

static bool isValidFilename(const char* filename) {
    if (filename == NULL) return false;
    
    for (size_t i = 0; filename[i]; i++) {
        char c = filename[i];
        if (!(isalnum(c) || c == '.' || c == '-' || c == '_')) {
            return false;
        }
    }
    return true;
}

static bool isPathSafe(const char* path) {
    if (path == NULL) return false;
    
    char normalizedPath[MAX_PATH_LENGTH];
    realpath(path, normalizedPath);
    
    return strncmp(normalizedPath, SERVER_FILE_PATH, strlen(SERVER_FILE_PATH)) == 0;
}

static char* constructPath(const char* basePath, const char* filename) {
    size_t baseLen = strlen(basePath);
    size_t fileLen = strlen(filename);
    
    if (baseLen + fileLen + 1 >= MAX_PATH_LENGTH) {
        errno = ENAMETOOLONG;
        return NULL;
    }
    
    char* fullPath = malloc(MAX_PATH_LENGTH);
    if (fullPath == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    
    snprintf(fullPath, MAX_PATH_LENGTH, "%s%s", basePath, filename);
    return fullPath;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test.txt",
        "../secret.txt",  // should fail
        "file.doc",
        "malicious/../file",  // should fail
        "normal_file.pdf"
    };
    
    for (size_t i = 0; i < sizeof(testFiles) / sizeof(testFiles[0]); i++) {
        FileContent* content = retrieveFile(testFiles[i]);
        if (content != NULL) {
            printf("Successfully retrieved: %s (size: %zu bytes)\\n", 
                   testFiles[i], content->size);
            free(content->data);
            free(content);
        } else {
            printf("Error retrieving %s: %s\\n", testFiles[i], strerror(errno));
        }
    }
    
    return 0;
}
