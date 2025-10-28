
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME 256

const char* ALLOWED_EXTENSIONS[] = {"txt", "pdf", "jpg", "jpeg", "png", "doc", "docx"};
const int NUM_EXTENSIONS = 7;

int is_valid_filename(const char* filename) {
    if (!filename || strlen(filename) == 0) return 0;
    
    // Check for path traversal attempts
    if (strstr(filename, "..") || strchr(filename, '/') || strchr(filename, '\\\\')) {        return 0;    }
    // Check for valid characters
    for (int i = 0; filename[i]; i++) {        char c = filename[i];        if (!isalnum(c) && c != '.' && c != '_' && c != '-') {            return 0;        }    }    return 1;}
void get_file_extension(const char* filename, char* extension) {    const char* dot = strrchr(filename, '.');    if (dot && dot != filename) {        strcpy(extension, dot + 1);    } else {        extension[0] = '\0';    }}
int is_allowed_extension(const char* extension) {    char lower_ext[32];    strcpy(lower_ext, extension);    for (int i = 0; lower_ext[i]; i++) {        lower_ext[i] = tolower(lower_ext[i]);    }        for (int i = 0; i < NUM_EXTENSIONS; i++) {        if (strcmp(lower_ext, ALLOWED_EXTENSIONS[i]) == 0) {            return 1;        }    }    return 0;}
void sanitize_filename(const char* filename, char* sanitized) {    int j = 0;    for (int i = 0; filename[i]; i++) {        char c = filename[i];        if (isalnum(c) || c == '.' || c == '_' || c == '-') {            sanitized[j++] = c;        } else {            sanitized[j++] = '_';        }    }    sanitized[j] = '\0';}
void generate_unique_filename(const char* filename, char* unique_name) {    char name[MAX_FILENAME];    char extension[32];        const char* dot = strrchr(filename, '.');    if (dot) {        strncpy(name, filename, dot - filename);        name[dot - filename] = '\0';        strcpy(extension, dot + 1);    } else {        strcpy(name, filename);        extension[0] = '\0';
    }
    
    long long timestamp = (long long)time(NULL) * 1000;
    sprintf(unique_name, "%s_%lld.%s", name, timestamp, extension);
}

void calculate_checksum(const unsigned char* data, size_t size, char* checksum) {
    // Simple checksum (for production use proper cryptographic hash)
    unsigned long hash = 0;
    for (size_t i = 0; i < size; i++) {
        hash = hash * 31 + data[i];
    }
    sprintf(checksum, "%016lx", hash);
}

void create_directory(const char* dir) {
#ifdef _WIN32
    _mkdir(dir);
#else
    mkdir(dir, 0755);
#endif
}

char* upload_file(const char* filename, const unsigned char* file_content, size_t content_size) {
    static char result[512];
    
    // Validate filename
    if (!is_valid_filename(filename)) {
        strcpy(result, "Error: Invalid filename");
        return result;
    }
    
    // Check file size
    if (content_size > MAX_FILE_SIZE) {
        strcpy(result, "Error: File size exceeds maximum allowed size (10MB)");
        return result;
    }
    
    // Check file extension
    char extension[32];
    get_file_extension(filename, extension);
    if (!is_allowed_extension(extension)) {
        strcpy(result, "Error: File type not allowed");
        return result;
    }
    
    // Create upload directory
    create_directory(UPLOAD_DIR);
    
    // Sanitize and generate unique filename
    char sanitized[MAX_FILENAME];
    char unique_name[MAX_FILENAME];
    char filepath[MAX_FILENAME * 2];
    
    sanitize_filename(filename, sanitized);
    generate_unique_filename(sanitized, unique_name);
    sprintf(filepath, "%s/%s", UPLOAD_DIR, unique_name);
    
    // Write file
    FILE* f = fopen(filepath, "wb");
    if (!f) {
        strcpy(result, "Error: Failed to create file");
        return result;
    }
    fwrite(file_content, 1, content_size, f);
    fclose(f);
    
    // Calculate checksum
    char checksum[33];
    calculate_checksum(file_content, content_size, checksum);
    
    sprintf(result, "Success: File uploaded successfully. Filename: %s, Size: %zu bytes, Checksum: %s",
            unique_name, content_size, checksum);
    
    return result;
}

int main() {
    printf("File Upload Server - Test Cases\\n\\n");
    
    // Test Case 1: Valid text file
    const char* data1 = "Hello World!";
    char* result1 = upload_file("test1.txt", (unsigned char*)data1, strlen(data1));
    printf("Test 1: %s\\n\\n", result1);
    
    // Test Case 2: Valid PDF file (simulated)
    const char* data2 = "PDF content simulation";
    char* result2 = upload_file("document.pdf", (unsigned char*)data2, strlen(data2));
    printf("Test 2: %s\\n\\n", result2);
    
    // Test Case 3: Invalid filename with path traversal
    const char* data3 = "malicious content";
    char* result3 = upload_file("../../../etc/passwd", (unsigned char*)data3, strlen(data3));
    printf("Test 3: %s\\n\\n", result3);
    
    // Test Case 4: Disallowed file extension
    const char* data4 = "executable content";
    char* result4 = upload_file("script.exe", (unsigned char*)data4, strlen(data4));
    printf("Test 4: %s\\n\\n", result4);
    
    // Test Case 5: Valid image file
    const char* data5 = "JPEG image data";
    char* result5 = upload_file("photo.jpg", (unsigned char*)data5, strlen(data5));
    printf("Test 5: %s\\n\\n", result5);
    
    return 0;
}
