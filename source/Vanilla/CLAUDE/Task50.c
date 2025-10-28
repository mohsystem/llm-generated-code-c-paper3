#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#else
#define MKDIR(dir) mkdir(dir, 0755)
#endif

#define UPLOAD_DIR "uploads"
#define MAX_FILENAME 256
#define MAX_MESSAGE 512

typedef struct {
    char message[MAX_MESSAGE];
} UploadResult;

typedef struct {
    int exists;
} FileCheckResult;

// Function to handle file upload
UploadResult handle_file_upload(const char* file_name, const unsigned char* file_data, size_t data_size) {
    UploadResult result;

    // Create upload directory if it doesn't exist
    MKDIR(UPLOAD_DIR);

    // Create full file path
    char file_path[MAX_FILENAME + 50];
    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, file_name);

    // Open file for writing in binary mode
    FILE* file = fopen(file_path, "wb");
    if (file == NULL) {
        snprintf(result.message, MAX_MESSAGE, "ERROR: Failed to create file");
        return result;
    }

    // Write data to file
    size_t written = fwrite(file_data, 1, data_size, file);
    fclose(file);

    if (written != data_size) {
        snprintf(result.message, MAX_MESSAGE, "ERROR: Failed to write complete file");
        return result;
    }

    snprintf(
        result.message,
        MAX_MESSAGE,
        "SUCCESS: File '%s' uploaded successfully. Size: %zu bytes",
        file_name,
        data_size
    );

    return result;
}

// Function to check if file exists
int file_exists(const char* file_name) {
    char file_path[MAX_FILENAME + 50];
    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, file_name);

    FILE* file = fopen(file_path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Client function to upload file
UploadResult upload_file(const char* file_name, const unsigned char* file_data, size_t data_size) {
    return handle_file_upload(file_name, file_data, data_size);
}

int main() {
    printf("File Upload System - Test Cases\n\n");

    // Test Case 1: Upload a text file
    printf("Test Case 1: Upload text file\n");
    const char* content1 = "Hello, this is a test file!";
    UploadResult result1 = upload_file("test1.txt", (const unsigned char*)content1, strlen(content1));
    printf("%s\n", result1.message);
    printf("File exists: %s\n\n", file_exists("test1.txt") ? "true" : "false");

    // Test Case 2: Upload a binary file
    printf("Test Case 2: Upload binary file\n");
    unsigned char binary_data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    UploadResult result2 = upload_file("test2.bin", binary_data, sizeof(binary_data));
    printf("%s\n", result2.message);
    printf("File exists: %s\n\n", file_exists("test2.bin") ? "true" : "false");

    // Test Case 3: Upload a larger file
    printf("Test Case 3: Upload larger file\n");
    char* large_content = (char*)malloc(50000);
    int offset = 0;
    for (int i = 0; i < 1000; i++) {
        offset += snprintf(large_content + offset, 50000 - offset, "Line %d: This is test data.\n", i);
    }
    UploadResult result3 = upload_file("test3.log", (const unsigned char*)large_content, (size_t)offset);
    printf("%s\n", result3.message);
    printf("File exists: %s\n\n", file_exists("test3.log") ? "true" : "false");
    free(large_content);

    // Test Case 4: Upload file with special characters in name
    printf("Test Case 4: Upload file with special characters\n");
    const char* content4 = "Special file content";
    UploadResult result4 = upload_file("test_file-4.txt", (const unsigned char*)content4, strlen(content4));
    printf("%s\n", result4.message);
    printf("File exists: %s\n\n", file_exists("test_file-4.txt") ? "true" : "false");

    // Test Case 5: Upload empty file
    printf("Test Case 5: Upload empty file\n");
    UploadResult result5 = upload_file("empty.txt", (const unsigned char*)"", 0);
    printf("%s\n", result5.message);
    printf("File exists: %s\n\n", file_exists("empty.txt") ? "true" : "false");

    return 0;
}
