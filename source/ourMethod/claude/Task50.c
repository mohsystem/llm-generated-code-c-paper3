
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <openssl/sha.h>
#include <ctype.h>
#include <errno.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE 10485760 // 10MB
#define MAX_PATH 256
#define SHA256_STRING_LENGTH 65

typedef struct {
    const char* extensions[4];
    int count;
} AllowedExtensions;

static const AllowedExtensions ALLOWED_EXTENSIONS = {
    {".txt", ".pdf", ".doc", ".docx"},
    4
};

char* get_file_extension(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return "";
    }
    return (char*)dot;
}

int is_allowed_extension(const char* extension) {
    for (int i = 0; i < ALLOWED_EXTENSIONS.count; i++) {
        if (strcasecmp(extension, ALLOWED_EXTENSIONS.extensions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void generate_unique_filename(const char* original_filename, char* unique_filename, size_t max_length) {
    time_t now = time(NULL);
    char to_hash[MAX_PATH * 2];
    snprintf(to_hash, sizeof(to_hash), "%s%ld", original_filename, now);
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, to_hash, strlen(to_hash));
    SHA256_Final(hash, &sha256);
    
    char hash_str[SHA256_STRING_LENGTH];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    
    const char* extension = get_file_extension(original_filename);
    snprintf(unique_filename, max_length, "%s%s", hash_str, extension);
}

char* upload_file(const char* filename, const unsigned char* content, size_t content_size) {
    char* result = malloc(MAX_PATH);
    if (!result) {
        return strdup("Memory allocation error");
    }

    // Validate inputs
    if (!filename || !content || strlen(filename) == 0) {
        snprintf(result, MAX_PATH, "Invalid input parameters");
        return result;
    }

    // Validate file size
    if (content_size > MAX_FILE_SIZE) {
        snprintf(result, MAX_PATH, "File size exceeds maximum allowed size of 10MB");
        return result;
    }

    // Validate file extension
    const char* extension = get_file_extension(filename);
    if (!is_allowed_extension(extension)) {
        snprintf(result, MAX_PATH, "File type not allowed");
        return result;
    }

    // Create upload directory if it doesn't exist\n    #ifdef _WIN32\n        _mkdir(UPLOAD_DIR);\n    #else\n        mkdir(UPLOAD_DIR, 0777);\n    #endif\n\n    // Generate unique filename\n    char unique_filename[MAX_PATH];\n    generate_unique_filename(filename, unique_filename, sizeof(unique_filename));\n\n    // Create full path\n    char filepath[MAX_PATH];\n    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, unique_filename);\n\n    // Write file\n    FILE* fp = fopen(filepath, "wb");\n    if (!fp) {\n        snprintf(result, MAX_PATH, "Error creating output file: %s", strerror(errno));\n        return result;\n    }\n\n    size_t written = fwrite(content, 1, content_size, fp);\n    fclose(fp);\n\n    if (written != content_size) {\n        snprintf(result, MAX_PATH, "Error writing file: %s", strerror(errno));\n        return result;\n    }\n\n    snprintf(result, MAX_PATH, "File uploaded successfully: %s", unique_filename);\n    return result;\n}\n\nint main() {\n    // Test case 1: Valid file upload\n    unsigned char content1[] = "Hello World";\n    printf("%s\\n", upload_file("test.txt", content1, strlen((char*)content1)));\n    \n    // Test case 2: Invalid extension\n    unsigned char content2[] = "Malicious";\n    printf("%s\\n", upload_file("test.exe", content2, strlen((char*)content2)));\n    \n    // Test case ', type='text')