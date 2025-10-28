
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#endif

#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME 256
#define UPLOAD_DIR "uploads"

typedef struct {
    int success;
    char message[512];
    char savedPath[512];
} UploadResult;

const char* allowed_extensions[] = {"txt", "pdf", "jpg", "jpeg", "png", "doc", "docx", NULL};

void to_lowercase(char* str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

const char* get_file_extension(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if(!dot || dot == filename || *(dot + 1) == '\0') return "";
    return dot + 1;
}

const char* get_basename(const char* path) {
    const char* lastSlash = strrchr(path, '/');
    const char* lastBackslash = strrchr(path, '\\');
    const char* base = path;

    if (lastSlash && lastSlash > base) base = lastSlash + 1;
    if (lastBackslash && lastBackslash > base) base = lastBackslash + 1;

    return base;
}

int is_valid_filename(const char* filename) {
    for (int i = 0; filename[i]; i++) {
        char c = filename[i];
        if (!isalnum((unsigned char)c) && c != '_' && c != '-' && c != '.') {
            return 0;
        }
    }
    return 1;
}

int is_allowed_extension(const char* ext) {
    char lower_ext[32];
    strncpy(lower_ext, ext, sizeof(lower_ext) - 1);
    lower_ext[sizeof(lower_ext) - 1] = '\0';
    to_lowercase(lower_ext);

    for (int i = 0; allowed_extensions[i] != NULL; i++) {
        if (strcmp(lower_ext, allowed_extensions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void generate_unique_filename(const char* original, char* output, size_t output_size) {
    char base[MAX_FILENAME];
    const char* ext = get_file_extension(original);
    size_t base_len = strlen(original) - strlen(ext) - 1;

    if (base_len >= sizeof(base)) base_len = sizeof(base) - 1;
    strncpy(base, original, base_len);
    base[base_len] = '\0';

    long long timestamp = (long long)time(NULL) * 1000;
    snprintf(output, output_size, "%s_%lld.%s", base, timestamp, ext);
}

UploadResult upload_file(const char* original_filename, const char* file_content, size_t content_size) {
    UploadResult result = {0, "", ""};

    // Validate filename
    if (original_filename == NULL || strlen(original_filename) == 0) {
        result.success = 0;
        strcpy(result.message, "Filename cannot be empty");
        return result;
    }

    // Validate file content
    if (file_content == NULL || content_size == 0) {
        result.success = 0;
        strcpy(result.message, "File content cannot be empty");
        return result;
    }

    // Check file size
    if (content_size > MAX_FILE_SIZE) {
        result.success = 0;
        strcpy(result.message, "File size exceeds maximum limit of 10MB");
        return result;
    }

    // Sanitize filename
    const char* sanitized = get_basename(original_filename);

    // Validate filename pattern
    if (!is_valid_filename(sanitized)) {
        result.success = 0;
        strcpy(result.message, "Invalid filename. Use only alphanumeric characters, hyphens, underscores, and dots");
        return result;
    }

    // Validate file extension
    const char* extension = get_file_extension(sanitized);
    if (!is_allowed_extension(extension)) {
        result.success = 0;
        strcpy(result.message, "File type not allowed");
        return result;
    }

    // Create upload directory
    #ifdef _WIN32
    mkdir(UPLOAD_DIR);
    #else
    mkdir(UPLOAD_DIR, 0700);
    #endif

    // Generate unique filename
    char unique_filename[MAX_FILENAME];
    generate_unique_filename(sanitized, unique_filename, sizeof(unique_filename));

    char upload_path[512];
    snprintf(upload_path, sizeof(upload_path), "%s/%s", UPLOAD_DIR, unique_filename);

    // Check if file already exists
    FILE* check = fopen(upload_path, "rb");
    if (check != NULL) {
        fclose(check);
        result.success = 0;
        strcpy(result.message, "File already exists");
        return result;
    }

    // Write file
    FILE* file = fopen(upload_path, "wb");
    if (file == NULL) {
        result.success = 0;
        strcpy(result.message, "Error opening file for writing");
        return result;
    }

    size_t written = fwrite(file_content, 1, content_size, file);
    fclose(file);

    if (written != content_size) {
        remove(upload_path);
        result.success = 0;
        strcpy(result.message, "Error writing file");
        return result;
    }

    // Set file permissions
    #ifndef _WIN32
    chmod(upload_path, S_IRUSR | S_IWUSR);
    #endif

    result.success = 1;
    strcpy(result.message, "File uploaded successfully");
    strcpy(result.savedPath, upload_path);

    return result;
}

int main() {
    printf("=== File Upload Program Test Cases ===\n\n");

    // Test Case 1: Valid text file upload
    printf("Test 1: Valid text file upload\n");
    const char* content1 = "Hello, this is a test file content.";
    UploadResult result1 = upload_file("test_document.txt", content1, strlen(content1));
    printf("Success: %s\n", result1.success ? "true" : "false");
    printf("Message: %s\n", result1.message);
    printf("Path: %s\n\n", result1.savedPath);

    // Test Case 2: Invalid file extension
    printf("Test 2: Invalid file extension (.exe)\n");
    const char* content2 = "Malicious content";
    UploadResult result2 = upload_file("malware.exe", content2, strlen(content2));
    printf("Success: %s\n", result2.success ? "true" : "false");
    printf("Message: %s\n\n", result2.message);

    // Test Case 3: Path traversal attempt
    printf("Test 3: Path traversal attempt\n");
    const char* content3 = "Attack content";
    UploadResult result3 = upload_file("../../etc/passwd.txt", content3, strlen(content3));
    printf("Success: %s\n", result3.success ? "true" : "false");
    printf("Message: %s\n\n", result3.message);

    // Test Case 4: Empty filename
    printf("Test 4: Empty filename\n");
    const char* content4 = "Some content";
    UploadResult result4 = upload_file("", content4, strlen(content4));
    printf("Success: %s\n", result4.success ? "true" : "false");
    printf("Message: %s\n\n", result4.message);

    // Test Case 5: File size exceeds limit
    printf("Test 5: File size exceeds limit\n");
    size_t large_size = MAX_FILE_SIZE + 1;
    char* content5 = (char*)malloc(large_size);
    if (content5) {
        memset(content5, 'A', large_size);
        UploadResult result5 = upload_file("large_file.txt", content5, large_size);
        printf("Success: %s\n", result5.success ? "true" : "false");
        printf("Message: %s\n\n", result5.message);
        free(content5);
    }

    return 0;
}

