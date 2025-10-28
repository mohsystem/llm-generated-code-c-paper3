#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#define ALLOWED_DIRECTORY "./images/"
#define MAX_PATH_LEN 512
#define MAX_FILE_SIZE 10485760  // 10MB limit

char* sanitize_filename(const char* filename) {
    if (!filename) return NULL;

    size_t len = strlen(filename);
    char* sanitized = (char*) malloc(len + 1);
    if (!sanitized) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = filename[i];
        if (isalnum(c) || c == '.' || c == '_' || c == '-') {
            sanitized[j++] = c;
        }
    }
    sanitized[j] = '\0';

    return sanitized;
}

int is_safe_path(const char* filepath) {
    // Check for path traversal patterns
    if (strstr(filepath, "..") != NULL ||
        strstr(filepath, "/") != NULL ||
        strstr(filepath, "\\\\") != NULL) {
        return 0;
    }
    return 1;
}

unsigned char* img(const char* fileParam, size_t* outSize) {
    *outSize = 0;

    if (!fileParam || strlen(fileParam) == 0) {
        fprintf(stderr, "File parameter is required\n");
        return NULL;
    }

    // Sanitize input
    char* sanitized = sanitize_filename(fileParam);
    if (!sanitized) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    if (!is_safe_path(sanitized)) {
        fprintf(stderr, "Invalid file name\n");
        free(sanitized);
        return NULL;
    }

    // Construct full path
    char fullPath[MAX_PATH_LEN];
    snprintf(fullPath, MAX_PATH_LEN, "%s%s", ALLOWED_DIRECTORY, sanitized);
    free(sanitized);

    // Check if file exists and get size
    struct stat st;
    if (stat(fullPath, &st) != 0 || !S_ISREG(st.st_mode)) {
        fprintf(stderr, "File not found or not readable\n");
        return NULL;
    }

    // Check file size limit
    if (st.st_size > MAX_FILE_SIZE || st.st_size <= 0) {
        fprintf(stderr, "File size invalid\n");
        return NULL;
    }

    // Open and read file
    FILE* file = fopen(fullPath, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }

    unsigned char* buffer = (unsigned char*) malloc(st.st_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, st.st_size, file);
    fclose(file);

    if (bytesRead != (size_t) st.st_size) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        return NULL;
    }

    *outSize = bytesRead;
    return buffer;
}

int main() {
    // Create test directory
#ifdef _WIN32
    _mkdir(ALLOWED_DIRECTORY);
#else
    mkdir(ALLOWED_DIRECTORY, 0755);
#endif

    // Create test files
    FILE* f1 = fopen(ALLOWED_DIRECTORY "test1.txt", "wb");
    if (f1) {
        fprintf(f1, "Test content 1");
        fclose(f1);
    }

    FILE* f2 = fopen(ALLOWED_DIRECTORY "test2.jpg", "wb");
    if (f2) {
        fprintf(f2, "Image content");
        fclose(f2);
    }

    size_t size;
    unsigned char* result;

    // Test case 1: Valid file
    printf("Test 1 - Valid file:\n");
    result = img("test1.txt", &size);
    if (result) {
        printf("Success: %.*s\n", (int) size, result);
        free(result);
    } else {
        printf("Failed\n");
    }

    // Test case 2: Another valid file
    printf("Test 2 - Valid image file:\n");
    result = img("test2.jpg", &size);
    if (result) {
        printf("Success: %.*s\n", (int) size, result);
        free(result);
    } else {
        printf("Failed\n");
    }

    // Test case 3: Path traversal attempt
    printf("Test 3 - Path traversal attempt:\n");
    result = img("../etc/passwd", &size);
    printf("%s\n", result ? "Success" : "Blocked (Expected)");
    if (result) free(result);

    // Test case 4: NULL parameter
    printf("Test 4 - NULL parameter:\n");
    result = img(NULL, &size);
    printf("%s\n", result ? "Success" : "Blocked (Expected)");
    if (result) free(result);

    // Test case 5: Non-existent file
    printf("Test 5 - Non-existent file:\n");
    result = img("nonexistent.txt", &size);
    printf("%s\n", result ? "Success" : "Failed (Expected)");
    if (result) free(result);

    return 0;
}
