#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILENAME_LEN 255
#define MAX_PATH_LEN 4096
#define BUFFER_SIZE 8192
#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10 MB limit

// Secure memory clearing function
static void secure_zero(void *ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) *p++ = 0;
}

// Validate filename: allow only alphanumeric, dash, underscore, and dot
// Reject path traversal attempts and hidden files
static int validate_filename(const char *filename) {
    if (filename == NULL || filename[0] == '\0') {
        return 0; // Empty filename
    }

    size_t len = strnlen(filename, MAX_FILENAME_LEN + 1);
    if (len == 0 || len > MAX_FILENAME_LEN) {
        return 0; // Too long or empty
    }

    // Reject if starts with dot (hidden file) or contains path separators
    if (filename[0] == '.' || strchr(filename, '/') != NULL || strchr(filename, '\\') != NULL) {
        return 0;
    }

    // Check for path traversal sequences
    if (strstr(filename, "..") != NULL) {
        return 0;
    }

    // Validate characters: allow alphanumeric, dash, underscore, dot
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)filename[i]) &&
            filename[i] != '-' &&
            filename[i] != '_' &&
            filename[i] != '.') {
            return 0;
        }
    }

    return 1;
}

// Create upload directory securely
static int create_upload_directory(void) {
    struct stat st;

    // Try to create directory with restrictive permissions (0700)
    if (mkdir(UPLOAD_DIR, 0700) == 0) {
        return 0; // Successfully created
    }

    if (errno != EEXIST) {
        return -1; // Failed to create for reasons other than already exists
    }

    // Directory exists - open and verify it's actually a directory
    int dirfd = open(UPLOAD_DIR, O_RDONLY | O_DIRECTORY | O_CLOEXEC | O_NOFOLLOW);
    if (dirfd < 0) {
        return -1; // Cannot open as directory or is a symlink
    }

    // Verify it's a directory using fstat on the opened descriptor
    if (fstat(dirfd, &st) != 0) {
        close(dirfd);
        return -1;
    }

    close(dirfd);

    if (!S_ISDIR(st.st_mode)) {
        return -1; // Not a directory
    }

    return 0;
}

// Upload file function with comprehensive security checks
int upload_file(const char *source_path, const char *filename) {
    FILE *src = NULL;
    FILE *dest = NULL;
    unsigned char *buffer = NULL;
    char *dest_path = NULL;
    char *temp_path = NULL;
    int result = -1;
    struct stat src_stat;
    struct stat dest_stat;

    // Validate input parameters
    if (source_path == NULL || filename == NULL) {
        fprintf(stderr, "Invalid parameters\n");
        return -1;
    }

    // Validate filename against injection and traversal attacks
    if (!validate_filename(filename)) {
        fprintf(stderr, "Invalid filename\n");
        return -1;
    }

    // Create upload directory securely (TOCTOU-safe)
    if (create_upload_directory() != 0) {
        fprintf(stderr, "Failed to create upload directory\n");
        return -1;
    }

    // Allocate buffers with overflow checks
    buffer = (unsigned char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    // Calculate destination path length with overflow check
    size_t dir_len = strlen(UPLOAD_DIR);
    size_t filename_len = strnlen(filename, MAX_FILENAME_LEN);

    if (dir_len > MAX_PATH_LEN - 2 || filename_len > MAX_PATH_LEN - dir_len - 2) {
        fprintf(stderr, "Path too long\n");
        goto cleanup;
    }

    dest_path = (char *)malloc(MAX_PATH_LEN);
    temp_path = (char *)malloc(MAX_PATH_LEN);
    if (dest_path == NULL || temp_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    // Build paths safely using snprintf
    int ret = snprintf(dest_path, MAX_PATH_LEN, "%s/%s", UPLOAD_DIR, filename);
    if (ret < 0 || ret >= MAX_PATH_LEN) {
        fprintf(stderr, "Path construction failed\n");
        goto cleanup;
    }

    ret = snprintf(temp_path, MAX_PATH_LEN, "%s/.tmp_%s", UPLOAD_DIR, filename);
    if (ret < 0 || ret >= MAX_PATH_LEN) {
        fprintf(stderr, "Temp path construction failed\n");
        goto cleanup;
    }

    // Open source file and validate handle before use
    src = fopen(source_path, "rb");
    if (src == NULL) {
        fprintf(stderr, "Cannot open source file\n");
        goto cleanup;
    }

    // Validate source file using fstat on the opened handle
    if (fstat(fileno(src), &src_stat) != 0) {
        fprintf(stderr, "Cannot stat source file\n");
        goto cleanup;
    }

    if (!S_ISREG(src_stat.st_mode)) {
        fprintf(stderr, "Source is not a regular file\n");
        goto cleanup;
    }

    if (src_stat.st_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File exceeds size limit\n");
        goto cleanup;
    }

    // Open destination with exclusive creation (prevents TOCTOU)
    dest = fopen(temp_path, "wx");
    if (dest == NULL) {
        fprintf(stderr, "Cannot create destination file\n");
        goto cleanup;
    }

    if (fstat(fileno(dest), &dest_stat) != 0) {
        fprintf(stderr, "Cannot stat destination file\n");
        goto cleanup;
    }

    if (!S_ISREG(dest_stat.st_mode)) {
        fprintf(stderr, "Destination is not a regular file\n");
        goto cleanup;
    }

    size_t bytes_read;
    size_t total_written = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        if (total_written > SIZE_MAX - bytes_read) {
            fprintf(stderr, "Size overflow detected\n");
            goto cleanup;
        }

        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Write error\n");
            goto cleanup;
        }

        total_written += bytes_written;

        if (total_written > MAX_FILE_SIZE) {
            fprintf(stderr, "File size exceeded during copy\n");
            goto cleanup;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "Read error\n");
        goto cleanup;
    }

    if (fflush(dest) != 0) {
        fprintf(stderr, "Flush failed\n");
        goto cleanup;
    }

    if (fsync(fileno(dest)) != 0) {
        fprintf(stderr, "Fsync failed\n");
        goto cleanup;
    }

    if (fclose(dest) != 0) {
        fprintf(stderr, "Close failed\n");
        dest = NULL;
        goto cleanup;
    }
    dest = NULL;

    if (rename(temp_path, dest_path) != 0) {
        fprintf(stderr, "Rename failed\n");
        goto cleanup;
    }

    result = 0; // Success

cleanup:
    if (src != NULL) {
        fclose(src);
    }
    if (dest != NULL) {
        fclose(dest);
        unlink(temp_path);
    }
    if (buffer != NULL) {
        secure_zero(buffer, BUFFER_SIZE);
        free(buffer);
    }
    if (dest_path != NULL) {
        secure_zero(dest_path, MAX_PATH_LEN);
        free(dest_path);
    }
    if (temp_path != NULL) {
        secure_zero(temp_path, MAX_PATH_LEN);
        free(temp_path);
    }

    return result;
}

int main(void) {
    printf("Test 1: Valid filename\n");
    FILE *f1 = fopen("test1.txt", "w");
    if (f1) {
        fprintf(f1, "Test content 1\n");
        fclose(f1);
        if (upload_file("test1.txt", "uploaded1.txt") == 0) {
            printf("Success\n");
        } else {
            printf("Failed\n");
        }
        unlink("test1.txt");
    }

    printf("\nTest 2: Path traversal attempt\n");
    if (upload_file("test1.txt", "../evil.txt") == 0) {
        printf("Failed - should have rejected\n");
    } else {
        printf("Success - rejected path traversal\n");
    }

    printf("\nTest 3: Absolute path attempt\n");
    if (upload_file("test1.txt", "/etc/passwd") == 0) {
        printf("Failed - should have rejected\n");
    } else {
        printf("Success - rejected absolute path\n");
    }

    printf("\nTest 4: Hidden file attempt\n");
    if (upload_file("test1.txt", ".hidden") == 0) {
        printf("Failed - should have rejected\n");
    } else {
        printf("Success - rejected hidden file\n");
    }

    printf("\nTest 5: Valid filename with extension\n");
    FILE *f5 = fopen("test5.dat", "w");
    if (f5) {
        fprintf(f5, "Test content 5\n");
        fclose(f5);
        if (upload_file("test5.dat", "data_file.dat") == 0) {
            printf("Success\n");
        } else {
            printf("Failed\n");
        }
        unlink("test5.dat");
    }

    return 0;
}
