#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME_LEN 255

typedef struct {
    char* data;
    size_t size;
} FileContent;

const char* ALLOWED_EXTENSIONS[] = {
    ".txt", ".pdf", ".jpg", ".png", ".doc", ".docx", NULL
};

void sanitize_filename(const char* input, char* output, size_t output_size) {
    size_t j = 0;
    const char* basename = strrchr(input, '/');
    if (!basename) basename = strrchr(input, '\\');
    if (basename) basename++; else basename = input;

    // Copy and sanitize
    for (size_t i = 0; basename[i] && j < output_size - 1; i++) {
        char c = basename[i];
        if (isalnum(c) || c == '.' || c == '-' || c == '_') {
            output[j++] = c;
        } else {
            output[j++] = '_';
        }
    }
    output[j] = '\0';

    // Remove leading dots
    size_t start = 0;
    while (output[start] == '.') start++;
    if (start > 0) {
        memmove(output, output + start, strlen(output + start) + 1);
    }
}

int is_allowed_extension(const char* filename) {
    size_t len = strlen(filename);
    for (int i = 0; ALLOWED_EXTENSIONS[i] != NULL; i++) {
        size_t ext_len = strlen(ALLOWED_EXTENSIONS[i]);
        if (len >= ext_len) {
            const char* file_ext = filename + len - ext_len;
            char lower_ext[20];
            for (size_t j = 0; j < ext_len && j < 19; j++) {
                lower_ext[j] = tolower(file_ext[j]);
            }
            lower_ext[ext_len] = '\0';

            if (strcmp(lower_ext, ALLOWED_EXTENSIONS[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int create_directory(const char* path) {
#ifdef _WIN32
    return _mkdir(path) == 0 || errno == EEXIST;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

char* upload_file(const FileContent* file_content, const char* filename) {
    static char result[512];
    char sanitized[MAX_FILENAME_LEN + 1];
    char filepath[512];

    // Validate filename
    if (!filename || strlen(filename) == 0) {
        snprintf(result, sizeof(result), "Error: Invalid filename");
        return result;
    }

    // Sanitize filename
    sanitize_filename(filename, sanitized, sizeof(sanitized));
    if (strlen(sanitized) == 0) {
        snprintf(result, sizeof(result), "Error: Invalid filename after sanitization");
        return result;
    }

    // Validate extension
    if (!is_allowed_extension(sanitized)) {
        snprintf(result, sizeof(result), "Error: File type not allowed");
        return result;
    }

    // Validate size
    if (file_content->size > MAX_FILE_SIZE) {
        snprintf(result, sizeof(result), "Error: File size exceeds limit");
        return result;
    }

    // Create directory
    create_directory(UPLOAD_DIR);

    // Create filepath
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, sanitized);

    // Check for path traversal
    if (strstr(filepath, "..") != NULL) {
        snprintf(result, sizeof(result), "Error: Invalid file path");
        return result;
    }

    // Save file
    FILE* f = fopen(filepath, "wb");
    if (!f) {
        snprintf(result, sizeof(result), "Error: Cannot create file");
        return result;
    }

    fwrite(file_content->data, 1, file_content->size, f);
    fclose(f);

    snprintf(result, sizeof(result), "Success: File uploaded to %s", filepath);
    return result;
}

int main() {
    // Test case 1: Valid file
    FileContent content1 = {"Test content", 12};
    printf("Test 1: %s\n", upload_file(&content1, "document.txt"));

    // Test case 2: Path traversal attempt
    FileContent content2 = {"Malicious", 9};
    printf("Test 2: %s\n", upload_file(&content2, "../../../etc/passwd"));

    // Test case 3: Invalid extension
    FileContent content3 = {"Script", 6};
    printf("Test 3: %s\n", upload_file(&content3, "malicious.exe"));

    // Test case 4: Valid image
    char buffer[1024];
    memset(buffer, 'x', sizeof(buffer));
    FileContent content4 = {buffer, 1024};
    printf("Test 4: %s\n", upload_file(&content4, "photo.jpg"));

    // Test case 5: Empty filename
    FileContent content5 = {"Content", 7};
    printf("Test 5: %s\n", upload_file(&content5, ""));

    return 0;
}
