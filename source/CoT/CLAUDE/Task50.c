
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#else
#include <sys/types.h>
#endif

#define UPLOAD_DIR "uploads"
#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME 256

typedef struct {
    int success;
    char message[512];
    char saved_path[512];
} UploadResult;

const char* ALLOWED_EXTENSIONS[] = {"txt", "pdf", "jpg", "jpeg", "png", "gif", "doc", "docx", NULL};

int is_allowed_extension(const char* ext) {
    for (int i = 0; ALLOWED_EXTENSIONS[i] != NULL; i++) {
        if (strcasecmp(ext, ALLOWED_EXTENSIONS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void get_file_extension(const char* filename, char* extension) {
    const char* dot = strrchr(filename, '.');
    if (dot && dot != filename) {
        strcpy(extension, dot + 1);
    } else {
        extension[0] = '\0';
    }
}

void sanitize_filename(const char* filename, char* sanitized) {
    const char* basename = strrchr(filename, '/');
    if (!basename) basename = strrchr(filename, '\\\\');
   basename = basename ? basename + 1 : filename;
    int j = 0;    for (int i = 0; basename[i] && j < MAX_FILENAME - 1; i++) {        char c = basename[i];
        if (isalnum(c) || c == '.' || c == '_' || c == '-') {            sanitized[j++] = c;        } else {            sanitized[j++] = '_';        }    }
    sanitized[j] = '\0';}void generate_unique_filename(const char* original, char* unique) {    char name_without_ext[MAX_FILENAME];    char extension[64];
    get_file_extension(original, extension);        const char* dot = strrchr(original, '.');    if (dot) {        int len = dot - original;
        strncpy(name_without_ext, original, len);        name_without_ext[len] = '\0';    } else {        strcpy(name_without_ext, original);    }
    long timestamp = (long)time(NULL) * 1000;        if (strlen(extension) > 0) {
        snprintf(unique, MAX_FILENAME, "%s_%ld.%s", name_without_ext, timestamp, extension);
    } else {        snprintf(unique, MAX_FILENAME, "%s_%ld", name_without_ext, timestamp);    }}int create_directory(const char* dir) {
    struct stat st = {0};    if (stat(dir, &st) == -1) {        return mkdir(dir, 0700) == 0;    }    return 1;
}
UploadResult upload_file(const char* filename, const char* file_content, size_t content_size) {
    UploadResult result = {0, "", ""};
    // Validate filename
    if (!filename || strlen(filename) == 0) {
        strcpy(result.message, "Invalid filename");        return result;
    }        // Sanitize filename
    char sanitized_filename[MAX_FILENAME];    sanitize_filename(filename, sanitized_filename);
    // Validate file extension
    char extension[64];    get_file_extension(sanitized_filename, extension);
    if (!is_allowed_extension(extension)) {
        snprintf(result.message, sizeof(result.message),
            "File type not allowed: %s", extension);        return result;
    }
    // Validate file size
    if (!file_content || content_size == 0) {
        strcpy(result.message, "Empty file content");        return result;
    }    if (content_size > MAX_FILE_SIZE) {        strcpy(result.message, "File size exceeds maximum limit");
        return result;    }
    // Create upload directory
    if (!create_directory(UPLOAD_DIR)) {
        strcpy(result.message, "Failed to create upload directory");
        return result;
    }
    // Generate unique filename
    char unique_filename[MAX_FILENAME];    generate_unique_filename(sanitized_filename, unique_filename);
    char target_path[512];    snprintf(target_path, sizeof(target_path), "%s/%s", UPLOAD_DIR, unique_filename);
    // Write file
    FILE* outfile = fopen(target_path, "wb");
    if (!outfile) {        strcpy(result.message, "Failed to create file");        return result;    }
    size_t written = fwrite(file_content, 1, content_size, outfile);    fclose(outfile);        if (written != content_size) {
        strcpy(result.message, "Failed to write complete file");        return result;
    }
    // Set file permissions (Unix-like systems)
    #ifndef _WIN32
    chmod(target_path, S_IRUSR | S_IWUSR);
    #endif
    result.success = 1;    snprintf(result.message, sizeof(result.message),             "File uploaded successfully: %s", unique_filename);
    strcpy(result.saved_path, target_path);        return result;}int main() {
    printf("=== Secure File Upload Server - Test Cases ===\\n\\n");
    // Test Case 1: Valid text file upload
    const char* content1 = "This is a test file content.";
    UploadResult result1 = upload_file("test_document.txt", content1, strlen(content1));
    printf("Test 1 - Valid text file:\\n");    printf("Success: %s\\n", result1.success ? "true" : "false");
    printf("Message: %s\\n\\n", result1.message);
    // Test Case 2: Valid PDF file upload
    char content2[1024];    memset(content2, 'A', sizeof(content2));
    UploadResult result2 = upload_file("report.pdf", content2, sizeof(content2));
    printf("Test 2 - Valid PDF file:\\n");
    printf("Success: %s\\n", result2.success ? "true" : "false");
    printf("Message: %s\\n\\n", result2.message);
    
    // Test Case 3: Invalid file extension
    const char* content3 = "malware";
    UploadResult result3 = upload_file("malicious.exe", content3, strlen(content3));
    printf("Test 3 - Invalid extension (.exe):\\n");
    printf("Success: %s\\n", result3.success ? "true" : "false");
    printf("Message: %s\\n\\n", result3.message);
    
    // Test Case 4: Path traversal attempt
    const char* content4 = "hack";
    UploadResult result4 = upload_file("../../etc/passwd.txt", content4, strlen(content4));
    printf("Test 4 - Path traversal attempt:\\n");
    printf("Success: %s\\n", result4.success ? "true" : "false");
    printf("Message: %s\\n\\n", result4.message);
    
    // Test Case 5: Empty file
    UploadResult result5 = upload_file("empty.txt", "", 0);
    printf("Test 5 - Empty file:\\n");
    printf("Success: %s\\n", result5.success ? "true" : "false");
    printf("Message: %s\\n\\n", result5.message);
    
    return 0;
}
