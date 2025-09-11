
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <openssl/sha.h>
#include <errno.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE 10485760 // 10MB
#define HASH_LENGTH 32
#define MAX_PATH 256

typedef struct {
    const char* extension;
} AllowedExtension;

static const AllowedExtension ALLOWED_EXTENSIONS[] = {
    {".txt"},
    {".pdf"},
    {".doc"},
    {".docx"}
};

static const int ALLOWED_EXTENSIONS_COUNT = sizeof(ALLOWED_EXTENSIONS) / sizeof(AllowedExtension);

static void generate_unique_filename(const char* original_filename, char* unique_filename) {
    // Get timestamp
    time_t now = time(NULL);
    char timestamp[32];
    snprintf(timestamp, sizeof(timestamp), "%ld", now);
    
    // Get file extension
    const char* extension = strrchr(original_filename, '.');
    
    // Create hash input
    char hash_input[MAX_PATH];
    snprintf(hash_input, sizeof(hash_input), "%s%s", original_filename, timestamp);
    
    // Generate SHA-256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hash_input, strlen(hash_input));
    SHA256_Final(hash, &sha256);
    
    // Convert hash to hex string
    char hash_str[HASH_LENGTH * 2 + 1];
    for(int i = 0; i < HASH_LENGTH; i++) {
        sprintf(&hash_str[i * 2], "%02x", hash[i]);
    }
    hash_str[HASH_LENGTH * 2] = '\\0';
    
    // Combine hash and extension
    strncpy(unique_filename, hash_str, HASH_LENGTH);
    unique_filename[HASH_LENGTH] = '\\0';
    strcat(unique_filename, extension);
}

static int is_extension_allowed(const char* filename) {
    const char* extension = strrchr(filename, '.');
    if (!extension) return 0;
    
    for (int i = 0; i < ALLOWED_EXTENSIONS_COUNT; i++) {
        if (strcasecmp(extension, ALLOWED_EXTENSIONS[i].extension) == 0) {
            return 1;
        }
    }
    return 0;
}

char* upload_file(const char* filename, const unsigned char* content, size_t content_size) {
    char* result = malloc(MAX_PATH);
    if (!result) {
        return strdup("Error: Memory allocation failed");
    }
    
    // Create upload directory if it doesn't exist\n    #ifdef _WIN32\n        _mkdir(UPLOAD_DIR);\n    #else\n        mkdir(UPLOAD_DIR, 0777);\n    #endif\n\n    // Validate file size\n    if (content_size > MAX_FILE_SIZE) {\n        strcpy(result, "Error: File size exceeds maximum limit of 10MB");\n        return result;\n    }\n\n    // Validate file extension\n    if (!is_extension_allowed(filename)) {\n        strcpy(result, "Error: File type not allowed");\n        return result;\n    }\n\n    // Generate unique filename\n    char unique_filename[MAX_PATH];\n    generate_unique_filename(filename, unique_filename);\n\n    // Create full path\n    char full_path[MAX_PATH];\n    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, unique_filename);\n\n    // Write file securely\n    FILE* file = fopen(full_path, "wb");\n    if (!file) {\n        snprintf(result, MAX_PATH, "Error: Failed to create file - %s", strerror(errno));\n        return result;\n    }\n\n    size_t written = fwrite(content, 1, content_size, file);\n    fclose(file);\n\n    if (written != content_size) {\n        snprintf(result, MAX_PATH, "Error: Failed to write file completely");\n        return result;\n    }\n\n    snprintf(result, MAX_PATH, "File uploaded successfully: %s", unique_filename);\n    return result;\n}\n\nint main() {\n    // Test cases\n    unsigned char test_content1[] = "Test content 1";\n    unsigned char test_content2[] = "Test content 2";\n    unsigned char* large_content = malloc(MAX_FILE_SIZE + 1);\n    \n    if (large_content == NULL) {\n        printf("Failed to allocate memory for test\\n");\n        return 1;\n    }\n    \n    memset(large_content, 'X', MAX_FILE_SIZE + 1);\n\n    // Test case 1: Valid txt file\n    char* result = upload_file("test1.txt", test_content1, strlen((char*)test_content1));\n    printf("%s\\n", result);\n    free(result);\n\n    //', type='text')