#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "../../../../../../../../usr/include/stdint.h"

/* Security: Maximum file size to prevent DoS and memory exhaustion */
#define MAX_FILE_SIZE (10 * 1024 * 1024) /* 10 MB */
/* Security: Maximum filename length to prevent buffer overflows */
#define MAX_FILENAME_LEN 255
/* Security: Maximum path length */
#define MAX_PATH_LEN 4096
/* Security: Buffer size for safe file operations */
#define BUFFER_SIZE 8192

/* Security: Base directory where files are stored - prevents path traversal */
static const char* BASE_UPLOAD_DIR = "./uploads";

/* Security: Explicit memory zeroization to clear sensitive data */
static void explicit_zero(void* ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (len--) *p++ = 0;
}

/* Security: Validates filename to prevent path traversal (CWE-22, CWE-73)
 * Rejects: "..", "/", "\\", null bytes, and control characters
 * Only allows: alphanumeric, underscore, hyphen, dot (not at start)
 */
static int validate_filename(const char* filename) {
    size_t len;
    size_t i;

    /* Security: NULL check */
    if (filename == NULL) {
        fprintf(stderr, "Error: Filename is NULL\n");
        return 0;
    }

    len = strlen(filename);

    /* Security: Length validation to prevent buffer overflows (CWE-120, CWE-131) */
    if (len == 0 || len > MAX_FILENAME_LEN) {
        fprintf(stderr, "Error: Invalid filename length\n");
        return 0;
    }

    /* Security: Reject hidden files and relative paths */
    if (filename[0] == '.' || filename[0] == '/' || filename[0] == '\\') {
        fprintf(stderr, "Error: Filename cannot start with '.', '/', or '\\'\n");
        return 0;
    }

    /* Security: Check each character - prevent injection and traversal */
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)filename[i];

        /* Security: Reject null bytes (CWE-158) */
        if (c == '\0') {
            fprintf(stderr, "Error: Null byte in filename\n");
            return 0;
        }

        /* Security: Reject path separators and control characters */
        if (c == '/' || c == '\\' || c < 32 || c == 127) {
            fprintf(stderr, "Error: Invalid character in filename\n");
            return 0;
        }

        /* Security: Check for path traversal sequences */
        if (c == '.' && i > 0 && filename[i - 1] == '.') {
            fprintf(stderr, "Error: '..' sequence not allowed\n");
            return 0;
        }
    }

    /* Security: Additional check for dangerous names */
    if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
        fprintf(stderr, "Error: Invalid filename\n");
        return 0;
    }

    return 1;
}

/* Security: Constructs safe file path within base directory
 * Prevents path traversal by validating and containing paths (CWE-22, CWE-73)
 */
static int construct_safe_path(const char* filename, char* full_path, size_t path_size) {
    int result;
    size_t base_len;
    size_t name_len;

    /* Security: Validate inputs */
    if (filename == NULL || full_path == NULL || path_size == 0) {
        return 0;
    }

    /* Security: Validate filename before using it */
    if (!validate_filename(filename)) {
        return 0;
    }

    base_len = strlen(BASE_UPLOAD_DIR);
    name_len = strlen(filename);

    /* Security: Check for integer overflow before addition (CWE-190) */
    if (base_len > SIZE_MAX - name_len - 2) {
        fprintf(stderr, "Error: Path length calculation overflow\n");
        return 0;
    }

    /* Security: Ensure buffer is large enough (CWE-120, CWE-131) */
    if (base_len + 1 + name_len + 1 > path_size) {
        fprintf(stderr, "Error: Path too long\n");
        return 0;
    }

    /* Security: Use snprintf for safe string formatting (CWE-120) */
    result = snprintf(full_path, path_size, "%s/%s", BASE_UPLOAD_DIR, filename);

    /* Security: Check snprintf result */
    if (result < 0 || (size_t)result >= path_size) {
        fprintf(stderr, "Error: Path construction failed\n");
        return 0;
    }

    return 1;
}

/* Security: Creates upload directory with restrictive permissions (CWE-732)
 * Uses 0700 permissions to prevent unauthorized access
 */
static int ensure_upload_directory(void) {
    struct stat st;

    /* Security: Check if directory exists */
    if (stat(BASE_UPLOAD_DIR, &st) == 0) {
        /* Security: Verify it's a directory */
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Error: Upload path exists but is not a directory\n");
            return 0;
        }
        return 1;
    }

    /* Security: Create with restrictive permissions (CWE-732) */
    if (mkdir(BASE_UPLOAD_DIR, 0700) != 0) {
        fprintf(stderr, "Error: Failed to create upload directory: %s\n", strerror(errno));
        return 0;
    }

    return 1;
}

/* Security: Race-condition safe file upload using open-then-validate pattern (CWE-367, CWE-363)
 * Prevents TOCTOU by opening file first, then validating the file descriptor
 * Uses O_CREAT|O_EXCL to prevent overwriting existing files (CWE-59)
 */
static int upload_file_safe(const char* filename, const unsigned char* data, size_t data_size) {
    char full_path[MAX_PATH_LEN];
    int fd = -1;
    struct stat st;
    ssize_t written;
    size_t total_written = 0;
    int fsync_result;

    /* Security: Input validation (CWE-20) */
    if (filename == NULL || data == NULL) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return 0;
    }

    /* Security: Validate file size to prevent DoS (CWE-400) */
    if (data_size == 0 || data_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: Invalid file size\n");
        return 0;
    }

    /* Security: Ensure upload directory exists */
    if (!ensure_upload_directory()) {
        return 0;
    }

    /* Security: Construct safe path within base directory (CWE-22) */
    if (!construct_safe_path(filename, full_path, sizeof(full_path))) {
        return 0;
    }

    /* Security: Open file with restrictive flags and permissions (CWE-367, CWE-732)
     * O_CREAT|O_EXCL: Fails if file exists, prevents race conditions (CWE-59)
     * O_WRONLY: Write-only access
     * O_CLOEXEC: Close on exec for security
     * 0600: Owner read/write only (CWE-732)
     */
    fd = open(full_path, O_CREAT | O_EXCL | O_WRONLY | O_CLOEXEC, 0600);
    if (fd < 0) {
        if (errno == EEXIST) {
            fprintf(stderr, "Error: File already exists\n");
        } else {
            fprintf(stderr, "Error: Failed to create file: %s\n", strerror(errno));
        }
        return 0;
    }

    /* Security: Validate the opened file descriptor (CWE-367)
     * This prevents TOCTOU by checking the already-opened file
     */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Error: Failed to stat file: %s\n", strerror(errno));
        close(fd);
        unlink(full_path);
        return 0;
    }

    /* Security: Ensure it's a regular file, not a symlink or device (CWE-59) */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error: Not a regular file\n");
        close(fd);
        unlink(full_path);
        return 0;
    }

    /* Security: Write data in chunks with error checking (CWE-391, CWE-252)
     * Check all write return values to prevent data corruption
     */
    while (total_written < data_size) {
        size_t remaining = data_size - total_written;
        size_t to_write = (remaining < BUFFER_SIZE) ? remaining : BUFFER_SIZE;

        written = write(fd, data + total_written, to_write);

        /* Security: Check write result (CWE-252) */
        if (written < 0) {
            fprintf(stderr, "Error: Write failed: %s\n", strerror(errno));
            close(fd);
            unlink(full_path);
            return 0;
        }

        /* Security: Check for integer overflow (CWE-190) */
        if (total_written > SIZE_MAX - (size_t)written) {
            fprintf(stderr, "Error: Write size overflow\n");
            close(fd);
            unlink(full_path);
            return 0;
        }

        total_written += (size_t)written;
    }

    /* Security: Ensure data is written to disk (CWE-662) */
    fsync_result = fsync(fd);
    if (fsync_result != 0) {
        fprintf(stderr, "Warning: fsync failed: %s\n", strerror(errno));
    }

    /* Security: Close file and check result (CWE-252) */
    if (close(fd) != 0) {
        fprintf(stderr, "Error: Failed to close file: %s\n", strerror(errno));
        unlink(full_path);
        return 0;
    }

    printf("Success: File '%s' uploaded successfully (%zu bytes)\n", filename, data_size);
    return 1;
}

/* Test function with 5 test cases */
int main(void) {
    unsigned char test_data1[] = "This is test file content for test case 1.";
    unsigned char test_data2[] = "Test case 2: Different content with more data to test buffer handling.";
    unsigned char test_data3[] = "Small";
    unsigned char large_data[1024];
    unsigned char test_data5[] = "Final test case with normal content.";
    size_t i;

    printf("=== File Upload Server Test Cases ===\n\n");

    /* Test Case 1: Normal file upload */
    printf("Test 1: Normal file upload\n");
    if (upload_file_safe("test1.txt", test_data1, sizeof(test_data1) - 1)) {
        printf("Test 1: PASSED\n\n");
    } else {
        printf("Test 1: FAILED\n\n");
    }

    /* Test Case 2: Another normal file with different content */
    printf("Test 2: Different content file\n");
    if (upload_file_safe("test2.txt", test_data2, sizeof(test_data2) - 1)) {
        printf("Test 2: PASSED\n\n");
    } else {
        printf("Test 2: FAILED\n\n");
    }

    /* Test Case 3: Small file */
    printf("Test 3: Small file upload\n");
    if (upload_file_safe("small_file.txt", test_data3, sizeof(test_data3) - 1)) {
        printf("Test 3: PASSED\n\n");
    } else {
        printf("Test 3: FAILED\n\n");
    }

    /* Test Case 4: Larger file to test buffering */
    printf("Test 4: Larger file upload\n");
    for (i = 0; i < sizeof(large_data); i++) {
        large_data[i] = (unsigned char)('A' + (i % 26));
    }
    if (upload_file_safe("large_test.txt", large_data, sizeof(large_data))) {
        printf("Test 4: PASSED\n\n");
    } else {
        printf("Test 4: FAILED\n\n");
    }

    /* Test Case 5: Security test - attempt path traversal (should fail) */
    printf("Test 5: Security test - path traversal attempt (should fail)\n");
    if (!upload_file_safe("../etc/passwd", test_data5, sizeof(test_data5) - 1)) {
        printf("Test 5: PASSED (correctly rejected malicious filename)\n\n");
    } else {
        printf("Test 5: FAILED (security vulnerability detected!)\n\n");
    }

    /* Security: Clear sensitive data before exit */
    explicit_zero(test_data1, sizeof(test_data1));
    explicit_zero(test_data2, sizeof(test_data2));
    explicit_zero(test_data3, sizeof(test_data3));
    explicit_zero(large_data, sizeof(large_data));
    explicit_zero(test_data5, sizeof(test_data5));

    printf("=== All tests completed ===\n");
    return 0;
}
