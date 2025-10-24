
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

/* Maximum file size allowed: 10 MB */
#define MAX_FILE_SIZE (10 * 1024 * 1024)
/* Maximum filename length */
#define MAX_FILENAME_LEN 255
/* Upload directory - must be a trusted, absolute path */
#define UPLOAD_DIR "/tmp/uploads"

/* Portable explicit zero for sensitive data */
static void explicit_zero(void *ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) *p++ = 0;
}
/* Validate filename: allow only alphanumeric, dash, underscore, and single dot for extension */
static int validate_filename(const char *filename) {
    if (filename == NULL || filename[0] == '\0') {
        return 0; /* Invalid: empty or NULL */
    }

    size_t len = strlen(filename);
    if (len > MAX_FILENAME_LEN) {
        return 0; /* Invalid: too long */
    }

    /* Reject path traversal attempts */
    if (strstr(filename, "..") != NULL || strchr(filename, '/') != NULL || strchr(filename, '\\') != NULL) {
        return 0; /* Invalid: contains path traversal or separators */
    }

    /* Reject hidden files */
    if (filename[0] == '.') {
        return 0; /* Invalid: hidden file */
    }

    /* Validate characters: allow alphanumeric, dash, underscore, and single dot */
    int dot_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (filename[i] == '.') {
            dot_count++;
            if (dot_count > 1 || i == len - 1) {
                return 0; /* Invalid: multiple dots or ends with dot */
            }
        } else if (!isalnum((unsigned char)filename[i]) && filename[i] != '-' && filename[i] != '_') {
            return 0; /* Invalid: forbidden character */
        }
    }

    return 1; /* Valid */
}

/* Build full path using base directory and validated filename */
static int build_safe_path(const char *base_dir, const char *filename, char *output, size_t output_size) {
    if (base_dir == NULL || filename == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    /* Validate filename before building path */
    if (!validate_filename(filename)) {
        return -1;
    }

    /* Build path with bounds checking */
    int result = snprintf(output, output_size, "%s/%s", base_dir, filename);
    if (result < 0 || (size_t)result >= output_size) {
        return -1; /* Path too long or error */
    }

    return 0;
}

/* Upload file function using secure file handling with TOCTOU prevention */
static int upload_file(const char *filename, const unsigned char *data, size_t data_size) {
    int fd = -1;
    int dir_fd = -1;
    char safe_path[PATH_MAX];
    char temp_path[PATH_MAX];
    struct stat st;
    ssize_t written = 0;
    int ret = -1;

    /* Input validation */
    if (filename == NULL || data == NULL || data_size == 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return -1;
    }

    /* Check file size limit before processing */
    if (data_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File size exceeds maximum allowed size\n");
        return -1;
    }

    /* Build safe path - validates filename internally */
    if (build_safe_path(UPLOAD_DIR, filename, safe_path, sizeof(safe_path)) != 0) {
        fprintf(stderr, "Error: Invalid filename\n");
        return -1;
    }

    /* Open upload directory to use as anchor for openat */
    dir_fd = open(UPLOAD_DIR, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (dir_fd < 0) {
        fprintf(stderr, "Error: Cannot open upload directory\n");
        return -1;
    }

    /* Create temporary file in same directory for atomic write */
    int temp_result = snprintf(temp_path, sizeof(temp_path), "%s/.upload_XXXXXX", UPLOAD_DIR);
    if (temp_result < 0 || (size_t)temp_result >= sizeof(temp_path)) {
        close(dir_fd);
        return -1;
    }

    /* Create temporary file with restrictive permissions (owner read/write only) */
    fd = mkstemp(temp_path);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot create temporary file\n");
        close(dir_fd);
        return -1;
    }

    /* Set restrictive permissions explicitly */
    if (fchmod(fd, S_IRUSR | S_IWUSR) != 0) {
        fprintf(stderr, "Error: Cannot set file permissions\n");
        goto cleanup;
    }

    /* Validate the opened file descriptor with fstat (TOCTOU prevention) */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Error: Cannot stat file\n");
        goto cleanup;
    }

    /* Ensure it's a regular file */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error: Not a regular file\n");
        goto cleanup;
    }

    /* Write data to temporary file with bounds checking */
    size_t total_written = 0;
    while (total_written < data_size) {
        /* Calculate remaining bytes to write */
        size_t remaining = data_size - total_written;

        /* Write data */
        written = write(fd, data + total_written, remaining);
        if (written < 0) {
            if (errno == EINTR) {
                continue; /* Retry on interrupt */
            }
            fprintf(stderr, "Error: Write failed\n");
            goto cleanup;
        }

        if (written == 0) {
            fprintf(stderr, "Error: Unexpected end of write\n");
            goto cleanup;
        }

        /* Check for overflow before addition */
        if (total_written > SIZE_MAX - (size_t)written) {
            fprintf(stderr, "Error: Integer overflow in write tracking\n");
            goto cleanup;
        }

        total_written += (size_t)written;
    }

    /* Flush and sync to ensure data is written to disk */
    if (fsync(fd) != 0) {
        fprintf(stderr, "Error: Cannot sync file\n");
        goto cleanup;
    }

    /* Close the file descriptor before rename */
    if (close(fd) != 0) {
        fprintf(stderr, "Error: Cannot close file\n");
        fd = -1; /* Prevent double close */
        goto cleanup;
    }
    fd = -1; /* Mark as closed */

    /* Atomically move temporary file to final destination using rename */
    if (rename(temp_path, safe_path) != 0) {
        fprintf(stderr, "Error: Cannot move file to final location\n");
        goto cleanup;
    }

    /* Sync directory to ensure rename is persistent */
    if (fsync(dir_fd) != 0) {
        fprintf(stderr, "Error: Cannot sync directory\n");
        /* File is already in place, so we continue despite this error */
    }

    ret = 0; /* Success */
    printf("File uploaded successfully: %s\n", filename);

cleanup:
    if (fd >= 0) {
        close(fd);
        /* Remove temporary file on failure */
        unlink(temp_path);
    }
    if (dir_fd >= 0) {
        close(dir_fd);
    }

    return ret;
}

/* Main function with test cases */
int main(void) {
    int result = 0;
    
    /* Ensure upload directory exists */
    if (mkdir(UPLOAD_DIR, 0700) != 0 && errno != EEXIST) {
        fprintf(stderr, "Error: Cannot create upload directory\\n");
        return 1;
    }
    
    /* Test case 1: Valid text file upload */
    printf("\\n=== Test Case 1: Valid text file ===\\n");
    const char *test1_data = "This is a test file with sample content.";
    result = upload_file("test1.txt", (const unsigned char *)test1_data, strlen(test1_data));
    printf("Result: %s\\n", result == 0 ? "SUCCESS" : "FAILED");
    
    /* Test case 2: Valid binary data file */
    printf("\\n=== Test Case 2: Valid binary file ===\\n");
    unsigned char test2_data[] = {0x00, 0x01, 0x02, 0x03, 0xFF, 0xFE, 0xFD, 0xFC};
    result = upload_file("test2.bin", test2_data, sizeof(test2_data));
    printf("Result: %s\\n", result == 0 ? "SUCCESS" : "FAILED");
    
    /* Test case 3: Invalid filename with path traversal attempt */
    printf("\\n=== Test Case 3: Invalid filename (path traversal) ===\\n");
    const char *test3_data = "Malicious content";
    result = upload_file("../../../etc/passwd", (const unsigned char *)test3_data, strlen(test3_data));
    printf("Result: %s (Expected FAILED)\\n", result == 0 ? "SUCCESS" : "FAILED");
    
    /* Test case 4: Invalid filename with special characters */
    printf("\\n=== Test Case 4: Invalid filename (special chars) ===\\n");
    const char *test4_data = "Another test";
    result = upload_file("test<>file.txt", (const unsigned char *)test4_data, strlen(test4_data));
    printf("Result: %s (Expected FAILED)\\n", result == 0 ? "SUCCESS" : "FAILED");
    
    /* Test case 5: Large file within limits */
    printf("\\n=== Test Case 5: Large file within limits ===\\n");
    size_t large_size = 1024 * 1024; /* 1 MB */
    unsigned char *large_data = (unsigned char *)malloc(large_size);
    if (large_data != NULL) {
        /* Fill with pattern */
        for (size_t i = 0; i < large_size; i++) {
            large_data[i] = (unsigned char)(i % 256);
        }
        result = upload_file("large_test.dat", large_data, large_size);
        printf("Result: %s\\n", result == 0 ? "SUCCESS" : "FAILED");
        
        /* Clear and free memory */
        explicit_zero(large_data, large_size);
        free(large_data);
    } else {
        printf("Result: FAILED (memory allocation)\\n");
    }
    
    return 0;
}
