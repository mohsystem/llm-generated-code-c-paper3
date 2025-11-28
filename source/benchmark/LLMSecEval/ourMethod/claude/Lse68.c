
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/* Maximum allowed image size: 5MB */
#define MAX_IMAGE_SIZE (5 * 1024 * 1024)
/* Maximum filename length */
#define MAX_FILENAME_LEN 255
/* Base64 output buffer size for MAX_IMAGE_SIZE */
#define MAX_BASE64_SIZE ((((MAX_IMAGE_SIZE + 2) / 3) * 4) + 1)

/* Secure base64 encoding table */
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * Securely zeros memory to prevent sensitive data leakage.
 * Uses volatile to prevent compiler optimization.
 */
static void secure_zero(void *ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) *p++ = 0;
}
/**
 * Validates filename to prevent path traversal and injection attacks.
 * Returns 0 on success, -1 on failure.
 */
static int validate_filename(const char *filename) {
    if (filename == NULL) return -1;

    size_t len = strnlen(filename, MAX_FILENAME_LEN + 1);
    /* Rules#2: Check length bounds */
    if (len == 0 || len > MAX_FILENAME_LEN) return -1;

    /* Rules#2: Block path traversal patterns */
    if (strstr(filename, "..") != NULL) return -1;
    if (strchr(filename, '/') != NULL) return -1;
    if (strchr(filename, '\\') != NULL) return -1;

    /* Rules#2: Allow only alphanumeric, dash, underscore, and dot */
    for (size_t i = 0; i < len; i++) {
        char c = filename[i];
        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') ||
              c == '_' || c == '-' || c == '.')) {
            return -1;
        }
    }

    return 0;
}

/**
 * Encodes binary data to base64 with bounds checking.
 * Returns 0 on success, -1 on failure.
 */
static int base64_encode(const unsigned char *input, size_t input_len,
                         char *output, size_t output_size) {
    if (input == NULL || output == NULL) return -1;

    /* Rules#35: Check integer overflow before size calculation */
    if (input_len > SIZE_MAX / 4 * 3) return -1;

    /* Calculate required output size */
    size_t required_size = ((input_len + 2) / 3) * 4 + 1;

    /* Rules#34: Validate output buffer size */
    if (required_size > output_size) return -1;

    size_t i = 0, j = 0;

    while (i < input_len) {
        /* Rules#34: Bounds check for each iteration */
        if (j + 4 >= output_size) return -1;

        uint32_t octet_a = i < input_len ? input[i++] : 0;
        uint32_t octet_b = i < input_len ? input[i++] : 0;
        uint32_t octet_c = i < input_len ? input[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        output[j++] = base64_table[(triple >> 18) & 0x3F];
        output[j++] = base64_table[(triple >> 12) & 0x3F];
        output[j++] = base64_table[(triple >> 6) & 0x3F];
        output[j++] = base64_table[triple & 0x3F];
    }

    /* Add padding */
    size_t padding = (3 - (input_len % 3)) % 3;
    for (size_t p = 0; p < padding; p++) {
        if (j > 0) output[j - 1 - p] = '=';
    }

    /* Rules#36: Ensure null termination */
    output[j] = '\0';
    return 0;
}

/**
 * Simulated database insertion (placeholder for actual database code).
 * In production, use parameterized queries with a safe database library.
 */
static int db_insert_image(const char *filename, const char *base64_data) {
    /* Rules#32: This is a placeholder. In real code, use parameterized queries */
    printf("[DB] Inserting image: filename='%s', base64_len=%zu\n",
           filename, strlen(base64_data));

    /* In production:
     * - Use prepared statements/parameterized queries
     * - Never concatenate user input into SQL
     * - Example with SQLite: sqlite3_prepare_v2() + sqlite3_bind_text()
     */
    return 0;
}

/**
 * Securely reads and uploads an image file.
 * Rules#7: Open first, validate handle, operate only on handle.
 * Rules#45-52: Eliminates TOCTOU by opening then validating.
 */
int upload_image(int dirfd, const char *relative_filename) {
    int result = -1;
    int fd = -1;
    unsigned char *image_data = NULL;
    char *base64_data = NULL;

    /* Rules#36: Initialize pointers to NULL */

    /* Rules#2: Validate filename before use */
    if (validate_filename(relative_filename) != 0) {
        fprintf(stderr, "Invalid filename\n");
        return -1;
    }

    /* Rules#46,47: Open file first with safe flags, don't follow symlinks */
    fd = openat(dirfd, relative_filename, O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
        return -1;
    }

    /* Rules#48: Validate opened descriptor with fstat */
    struct stat st;
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Failed to stat file: %s\n", strerror(errno));
        goto cleanup;
    }

    /* Rules#48: Verify it's a regular file */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Not a regular file\n");
        goto cleanup;
    }

    /* Rules#35,38: Validate size and check for reasonable limits */
    if (st.st_size <= 0 || st.st_size > MAX_IMAGE_SIZE) {
        fprintf(stderr, "File size out of bounds: %lld\n", (long long)st.st_size);
        goto cleanup;
    }

    size_t file_size = (size_t)st.st_size;

    /* Rules#35: Check allocation size for overflow */
    if (file_size > SIZE_MAX - 1) {
        fprintf(stderr, "File size too large for allocation\n");
        goto cleanup;
    }

    /* Rules#37: Allocate buffer for image data */
    image_data = (unsigned char *)calloc(file_size + 1, sizeof(unsigned char));
    if (image_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    /* Rules#41: Read with bounds checking */
    ssize_t bytes_read = read(fd, image_data, file_size);
    if (bytes_read < 0 || (size_t)bytes_read != file_size) {
        fprintf(stderr, "Failed to read complete file\n");
        goto cleanup;
    }

    /* Rules#35: Allocate base64 output buffer with overflow check */
    size_t base64_size = MAX_BASE64_SIZE;
    base64_data = (char *)calloc(base64_size, sizeof(char));
    if (base64_data == NULL) {
        fprintf(stderr, "Memory allocation failed for base64\n");
        goto cleanup;
    }

    /* Encode to base64 */
    if (base64_encode(image_data, file_size, base64_data, base64_size) != 0) {
        fprintf(stderr, "Base64 encoding failed\n");
        goto cleanup;
    }

    /* Rules#32: Insert into database using safe parameterized approach */
    if (db_insert_image(relative_filename, base64_data) != 0) {
        fprintf(stderr, "Database insertion failed\n");
        goto cleanup;
    }

    result = 0;

cleanup:
    /* Rules#40: Clear sensitive data before free */
    if (image_data != NULL) {
        secure_zero(image_data, file_size);
        free(image_data);
    }

    /* Rules#40: Clear base64 data */
    if (base64_data != NULL) {
        secure_zero(base64_data, base64_size);
        free(base64_data);
    }

    /* Rules#38: Close file descriptor */
    if (fd >= 0) {
        close(fd);
    }

    return result;
}

int main(void) {
    /* Test setup: open current directory as anchor */
    int dirfd = open(".", O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (dirfd < 0) {
        fprintf(stderr, "Failed to open directory\n");
        return 1;
    }

    printf("=== Image Upload Security Test Cases ===\n\n");

    /* Test case 1: Valid small file */
    printf("Test 1: Valid filename\n");
    FILE *f1 = fopen("test_image_1.jpg", "wb");
    if (f1) {
        unsigned char test_data[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
        fwrite(test_data, 1, sizeof(test_data), f1);
        fclose(f1);
        int r1 = upload_image(dirfd, "test_image_1.jpg");
        printf("Result: %s\n\n", r1 == 0 ? "SUCCESS" : "FAILED");
        unlink("test_image_1.jpg");
    }

    /* Test case 2: Path traversal attempt */
    printf("Test 2: Path traversal attack (should fail)\n");
    int r2 = upload_image(dirfd, "../etc/passwd");
    printf("Result: %s\n\n", r2 != 0 ? "BLOCKED (correct)" : "FAILED (security issue)");

    /* Test case 3: Invalid characters */
    printf("Test 3: Invalid characters in filename (should fail)\n");
    int r3 = upload_image(dirfd, "test;rm -rf.jpg");
    printf("Result: %s\n\n", r3 != 0 ? "BLOCKED (correct)" : "FAILED (security issue)");

    /* Test case 4: Null input */
    printf("Test 4: NULL filename (should fail)\n");
    int r4 = upload_image(dirfd, NULL);
    printf("Result: %s\n\n", r4 != 0 ? "BLOCKED (correct)" : "FAILED (security issue)");

    /* Test case 5: Oversized filename */
    printf("Test 5: Oversized filename (should fail)\n");
    char long_name[300];
    memset(long_name, 'a', sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';
    int r5 = upload_image(dirfd, long_name);
    printf("Result: %s\n\n", r5 != 0 ? "BLOCKED (correct)" : "FAILED (security issue)");

    close(dirfd);
    return 0;
}
