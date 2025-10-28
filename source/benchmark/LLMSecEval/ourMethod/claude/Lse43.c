
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024)  /* 10MB limit */
#define BASE_DIR "/safe/"
#define MAX_FILENAME 256

/**
 * Securely reads a file from /safe/ directory
 * Returns dynamically allocated buffer with file contents, or NULL on error
 * Caller must free returned buffer
 */
char* read_safe_file(const char* filename) {
    char* buffer = NULL;
    int fd = -1;
    struct stat st;
    ssize_t bytes_read;
    size_t total_read = 0;
    char full_path[PATH_MAX];

    /* Input validation - reject NULL or empty */
    if (filename == NULL || filename[0] == '\0') {
        fprintf(stderr, "Invalid filename\n");
        return NULL;
    }

    /* Reject filenames that are too long */
    if (strlen(filename) >= MAX_FILENAME) {
        fprintf(stderr, "Filename too long\n");
        return NULL;
    }

    /* Reject path traversal attempts */
    if (strstr(filename, "..") != NULL ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL) {
        fprintf(stderr, "Invalid filename characters\n");
        return NULL;
    }

    /* Construct full path safely */
    int ret = snprintf(full_path, sizeof(full_path), "%s%s", BASE_DIR, filename);
    if (ret < 0 || ret >= (int)sizeof(full_path)) {
        fprintf(stderr, "Path construction failed\n");
        return NULL;
    }

    /* Open file with O_NOFOLLOW to prevent symlink following */
    fd = open(full_path, O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (fd < 0) {
        fprintf(stderr, "File open failed\n");
        return NULL;
    }

    /* Validate file descriptor - must be regular file */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "File stat failed\n");
        close(fd);
        return NULL;
    }

    /* Check if regular file */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Not a regular file\n");
        close(fd);
        return NULL;
    }

    /* Check size limit */
    if (st.st_size > MAX_FILE_SIZE || st.st_size < 0) {
        fprintf(stderr, "File size invalid\n");
        close(fd);
        return NULL;
    }

    /* Allocate buffer (with space for null terminator) */
    buffer = (char*)calloc((size_t)st.st_size + 1, 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        close(fd);
        return NULL;
    }

    /* Read file contents */
    while (total_read < (size_t)st.st_size) {
        bytes_read = read(fd, buffer + total_read, (size_t)st.st_size - total_read);
        if (bytes_read < 0) {
            fprintf(stderr, "Read failed\n");
            free(buffer);
            close(fd);
            return NULL;
        }
        if (bytes_read == 0) {
            break;  /* EOF */
        }
        total_read += (size_t)bytes_read;
    }

    close(fd);
    buffer[total_read] = '\0';  /* Null terminate */
    return buffer;
}


int main(void) {
    char* result = NULL;
    
    /* Test case 1: Valid file */
    printf("Test 1: Valid file\\n");
    result = read_safe_file("test.txt");
    printf("Result: %s\\n", result ? "Success" : "Failed");
    free(result);
    
    /* Test case 2: Path traversal attempt */
    printf("\\nTest 2: Path traversal with ..\\n");
    result = read_safe_file("../etc/passwd");
    printf("Result: %s\\n", result == NULL ? "Blocked" : "Failed");
    free(result);
    
    /* Test case 3: Absolute path attempt */
    printf("\\nTest 3: Absolute path\\n");
    result = read_safe_file("/etc/passwd");
    printf("Result: %s\\n", result == NULL ? "Blocked" : "Failed");
    free(result);
    
    /* Test case 4: NULL input */
    printf("\\nTest 4: NULL input\\n");
    result = read_safe_file(NULL);
    printf("Result: %s\\n", result == NULL ? "Blocked" : "Failed");
    free(result);
    
    /* Test case 5: Empty filename */
    printf("\\nTest 5: Empty filename\\n");
    result = read_safe_file("");
    printf("Result: %s\\n", result == NULL ? "Blocked" : "Failed");
    free(result);
    
    return 0;
}
