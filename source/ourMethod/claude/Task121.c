
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10MB
#define UPLOAD_DIR "uploads"
#define MAX_PATH 4096
#define MAX_FILENAME 256

typedef struct {
    const char* allowed_extensions[4];
    int num_extensions;
} FileUploader;

void init_uploader(FileUploader* uploader) {
    uploader->allowed_extensions[0] = ".txt";
    uploader->allowed_extensions[1] = ".pdf";
    uploader->allowed_extensions[2] = ".doc";
    uploader->allowed_extensions[3] = ".docx";
    uploader->num_extensions = 4;
}

char* get_filename_from_path(const char* path) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        return strdup(last_slash + 1);
    }
    return strdup(path);
}

void sanitize_filename(char* filename) {
    for (int i = 0; filename[i]; i++) {
        if (!isalnum(filename[i]) && filename[i] != '.' && filename[i] != '-') {
            filename[i] = '_';
        }
    }
}

bool is_valid_extension(FileUploader* uploader, const char* filename) {
    size_t len = strlen(filename);
    for (int i = 0; i < uploader->num_extensions; i++) {
        size_t ext_len = strlen(uploader->allowed_extensions[i]);
        if (len > ext_len && 
            strcasecmp(filename + len - ext_len, uploader->allowed_extensions[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool upload_file(FileUploader* uploader, const char* filename, 
                const unsigned char* content, size_t content_size) {
    if (!filename || !content || !uploader) {
        fprintf(stderr, "Invalid input parameters\\n");
        return false;
    }

    // Validate file size
    if (content_size == 0 || content_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Invalid file size\\n");
        return false;
    }

    // Create upload directory
    #ifdef _WIN32
        _mkdir(UPLOAD_DIR);
    #else
        mkdir(UPLOAD_DIR, 0777);
    #endif

    // Sanitize and validate filename
    char* safe_name = get_filename_from_path(filename);
    if (!safe_name) {
        fprintf(stderr, "Memory allocation failed\\n");
        return false;
    }
    sanitize_filename(safe_name);

    if (!is_valid_extension(uploader, safe_name)) {
        fprintf(stderr, "Invalid file extension\\n");
        free(safe_name);
        return false;
    }

    // Create full path
    char full_path[MAX_PATH];
    if (snprintf(full_path, sizeof(full_path), "%s/%s", UPLOAD_DIR, safe_name) >= MAX_PATH) {
        fprintf(stderr, "Path too long\\n");
        free(safe_name);
        return false;
    }

    // Open file for writing
    FILE* fp = fopen(full_path, "wb");
    if (!fp) {
        fprintf(stderr, "Could not create file: %s\\n", strerror(errno));
        free(safe_name);
        return false;
    }

    // Write content
    size_t written = fwrite(content, 1, content_size, fp);
    fclose(fp);

    free(safe_name);

    if (written != content_size) {
        fprintf(stderr, "Failed to write complete file\\n");
        return false;
    }

    return true;
}

int main() {
    FileUploader uploader;
    init_uploader(&uploader);

    // Test 1: Valid file upload
    unsigned char content1[] = "Hello World";
    printf("Test 1: %d\\n", upload_file(&uploader, "test.txt", content1, sizeof(content', type='text')