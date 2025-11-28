#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Security: Maximum file size to prevent DoS - 10MB */
#define MAX_FILE_SIZE (10 * 1024 * 1024)
/* Security: Maximum filename length to prevent buffer overflow */
#define MAX_FILENAME_LEN 255
/* Security: Buffer size for safe I/O operations */
#define BUFFER_SIZE 8192

/* Security: Explicit memset that cannot be optimized away */
void secure_memset(void *ptr, int value, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) {
        *p++ = (unsigned char)value;
    }
}

/* Security: Validate filename to prevent path traversal and injection attacks
 * Rules#2: Input validation with allow list approach */
int validate_filename(const char *filename) {
    size_t len;
    size_t i;
    int has_pdf_ext = 0;

    if (filename == NULL) {
        return 0;
    }

    len = strnlen(filename, MAX_FILENAME_LEN + 1);

    /* Security: Reject if filename exceeds maximum length */
    if (len == 0 || len > MAX_FILENAME_LEN) {
        return 0;
    }

    /* Security: Check for path traversal attempts */
    if (strstr(filename, "..") != NULL ||
        strstr(filename, "/") != NULL ||
        strstr(filename, "\\") != NULL) {
        return 0;
    }

    /* Security: Validate allowed characters (alphanumeric, dash, underscore, dot) */
    for (i = 0; i < len; i++) {
        char c = filename[i];
        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') ||
              c == '-' || c == '_' || c == '.')) {
            return 0;
        }
    }

    /* Security: Verify .pdf extension */
    if (len > 4 && strcmp(filename + len - 4, ".pdf") == 0) {
        has_pdf_ext = 1;
    }

    return has_pdf_ext;
}

/* Security: Safe file upload with TOCTOU prevention
 * Rules#7: Open first, validate handle, operate only on handle */
int upload_pdf_file(const char *filename, const unsigned char *file_data, size_t file_size) {
    int dirfd = -1;
    int fd = -1;
    ssize_t written = 0;
    ssize_t total_written = 0;
    struct stat st;
    char safe_path[PATH_MAX];
    int result = -1;
    char temp_filename[MAX_FILENAME_LEN + 16];

    /* Security: Rules#2 - Validate all inputs */
    if (filename == NULL || file_data == NULL) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return -1;
    }

    /* Security: Rules#36 - Check file size limits to prevent DoS */
    if (file_size == 0 || file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: Invalid file size\n");
        return -1;
    }

    /* Security: Rules#2 - Validate filename to prevent path traversal */
    if (!validate_filename(filename)) {
        fprintf(stderr, "Error: Invalid filename\n");
        return -1;
    }

    /* Security: Rules#7 - Open uploads directory with O_DIRECTORY to anchor operations */
    dirfd = open("uploads", O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (dirfd == -1) {
        /* Create directory if it doesn't exist with restrictive permissions */
        if (mkdir("uploads", 0700) != 0 && errno != EEXIST) {
            fprintf(stderr, "Error: Cannot create uploads directory\n");
            return -1;
        }
        dirfd = open("uploads", O_RDONLY | O_DIRECTORY | O_CLOEXEC);
        if (dirfd == -1) {
            fprintf(stderr, "Error: Cannot open uploads directory\n");
            return -1;
        }
    }

    /* Security: Rules#52 - Write to temporary file first for atomic operation */
    /* Security: Rules#8 - Check snprintf return value and buffer size */
    if (snprintf(temp_filename, sizeof(temp_filename), ".tmp_%s", filename) >= (int)sizeof(temp_filename)) {
        fprintf(stderr, "Error: Filename too long\n");
        close(dirfd);
        return -1;
    }

    /* Security: Rules#7 - Use openat with O_NOFOLLOW to prevent symlink attacks
     * Rules#50 - Set restrictive permissions (0600) at creation time */
    fd = openat(dirfd, temp_filename, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: Cannot create temporary file\n");
        close(dirfd);
        return -1;
    }

    /* Security: Rules#48 - Validate opened file descriptor with fstat */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Error: Cannot stat file\n");
        goto cleanup;
    }

    /* Security: Verify it's a regular file */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error: Not a regular file\n");
        goto cleanup;
    }

    /* Security: Rules#8 - Write data with bounds checking and error handling */
    total_written = 0;
    while (total_written < (ssize_t)file_size) {
        size_t to_write = file_size - total_written;
        if (to_write > BUFFER_SIZE) {
            to_write = BUFFER_SIZE;
        }

        written = write(fd, file_data + total_written, to_write);
        if (written <= 0) {
            if (written == -1 && errno == EINTR) {
                continue;
            }
            fprintf(stderr, "Error: Write failed\n");
            goto cleanup;
        }

        /* Security: Rules#35 - Check for overflow before addition */
        if (total_written > SSIZE_MAX - written) {
            fprintf(stderr, "Error: Integer overflow in write\n");
            goto cleanup;
        }
        total_written += written;
    }

    /* Security: Rules#52 - Flush and sync before rename for durability */
    if (fsync(fd) != 0) {
        fprintf(stderr, "Error: fsync failed\n");
        goto cleanup;
    }

    /* Close the file descriptor before rename */
    close(fd);
    fd = -1;

    /* Security: Rules#52 - Atomic rename to final destination */
    if (renameat(dirfd, temp_filename, dirfd, filename) != 0) {
        fprintf(stderr, "Error: Rename failed\n");
        unlinkat(dirfd, temp_filename, 0);
        close(dirfd);
        return -1;
    }

    /* Security: Sync directory for durability */
    fsync(dirfd);

    result = 0;

cleanup:
    /* Security: Rules#8 - Proper cleanup and error handling */
    if (fd != -1) {
        close(fd);
        /* Remove temporary file on failure */
        unlinkat(dirfd, temp_filename, 0);
    }
    if (dirfd != -1) {
        close(dirfd);
    }

    return result;
}

/* Test cases */
int main(void) {
    int test_result;
    unsigned char test_data[1024];
    size_t i;

    /* Initialize test data */
    for (i = 0; i < sizeof(test_data); i++) {
        test_data[i] = (unsigned char)(i % 256);
    }

    printf("Test 1: Valid PDF upload\n");
    test_result = upload_pdf_file("test1.pdf", test_data, sizeof(test_data));
    printf("Result: %s\n\n", test_result == 0 ? "SUCCESS" : "FAILED");

    printf("Test 2: Path traversal attempt (should fail)\n");
    test_result = upload_pdf_file("../etc/passwd.pdf", test_data, sizeof(test_data));
    printf("Result: %s\n\n", test_result != 0 ? "SUCCESS (blocked)" : "FAILED");

    printf("Test 3: Invalid extension (should fail)\n");
    test_result = upload_pdf_file("test.txt", test_data, sizeof(test_data));
    printf("Result: %s\n\n", test_result != 0 ? "SUCCESS (blocked)" : "FAILED");

    printf("Test 4: Null filename (should fail)\n");
    test_result = upload_pdf_file(NULL, test_data, sizeof(test_data));
    printf("Result: %s\n\n", test_result != 0 ? "SUCCESS (blocked)" : "FAILED");

    printf("Test 5: Oversized file (should fail)\n");
    test_result = upload_pdf_file("large.pdf", test_data, MAX_FILE_SIZE + 1);
    printf("Result: %s\n\n", test_result != 0 ? "SUCCESS (blocked)" : "FAILED");

    return 0;
}
