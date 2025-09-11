
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE 8192
#define MAX_PATH 4096

typedef struct {
    char message[256];
    int code;
} Error;

void init_error(Error* err) {
    err->message[0] = '\\0';
    err->code = 0;
}

int copy_file(const char* source_path, const char* dest_dir, Error* err) {
    FILE *source = NULL, *dest = NULL;
    char dest_path[MAX_PATH];
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    struct stat st = {0};
    
    if (!source_path || !dest_dir) {
        strncpy(err->message, "Source or destination path cannot be null", sizeof(err->message) - 1);
        err->code = EINVAL;
        return -1;
    }

    // Check source file
    if (stat(source_path, &st) == -1) {
        snprintf(err->message, sizeof(err->message), "Source file error: %s", strerror(errno));
        err->code = errno;
        return -1;
    }

    if (!S_ISREG(st.st_mode)) {
        strncpy(err->message, "Source is not a regular file", sizeof(err->message) - 1);
        err->code = EINVAL;
        return -1;
    }

    // Create destination directory if needed
    if (stat(dest_dir, &st) == -1) {
        #ifdef _WIN32
            if (_mkdir(dest_dir) == -1) {
        #else
            if (mkdir(dest_dir, 0755) == -1) {
        #endif
            snprintf(err->message, sizeof(err->message), "Cannot create directory: %s", strerror(errno));
            err->code = errno;
            return -1;
        }
    }

    // Generate temp filename
    time_t t = time(NULL);
    snprintf(dest_path, sizeof(dest_path), "%s/temp_%ld.tmp", dest_dir, (long)t);

    // Open files
    source = fopen(source_path, "rb");
    if (!source) {
        snprintf(err->message, sizeof(err->message), "Cannot open source file: %s", strerror(errno));
        err->code = errno;
        return -1;
    }

    dest = fopen(dest_path, "wb");
    if (!dest) {
        snprintf(err->message, sizeof(err->message), "Cannot open destination file: %s", strerror(errno));
        err->code = errno;
        fclose(source);
        return -1;
    }

    // Copy data
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read) {
            snprintf(err->message, sizeof(err->message), "Write error: %s", strerror(errno));
            err->code = errno;
            fclose(source);
            fclose(dest);
            remove(dest_path);
            return -1;
        }
    }

    if (ferror(source)) {
        snprintf(err->message, sizeof(err->message), "Read error: %s", strerror(errno));
        err->code = errno;
        fclose(source);
        fclose(dest);
        remove(dest_path);
        return -1;
    }

    fclose(source);
    fclose(dest);
    return 0;
}

int main() {
    Error err;

    // Test case 1: Valid copy
    init_error(&err);
    if (copy_file("test.txt", "temp", &err) != 0) {
        printf("Error: %s\\n", err.message);
    }

    // Test case 2: NULL source path
    init_error(&err);
    if (copy_file(NULL, "temp", &err) != 0) {
        printf("Error: %s\\n", err.message);
    }

    // Test case 3: Non-existent file
    init_error(&err);
    if (copy_file("nonexistent.txt", "temp", &err) != 0) {
        printf("Error: %s\\n", err.message);
    }

    // Test case 4: Invalid destination
    init_error(&err);
    if (copy_file("test.txt", "", &err) != 0) {
        printf("Error: %s\\n", err.message);
    }

    // Test case 5: Source is directory
    init_error(&err);
    if (copy_file("src", "temp", &err) != 0) {
        printf("Error: %s\\n", err.message);
    }

    return 0;
}
