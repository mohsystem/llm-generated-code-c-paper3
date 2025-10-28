
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define PATH_MAX MAX_PATH
#endif

#define MAX_FILE_SIZE (10 * 1024 * 1024) /* 10MB max file size */
#define MAX_FILENAME_LENGTH 255
#define UPLOAD_DIR "uploads"

/* Generate cryptographically secure random filename */
char* generate_secure_filename(void) {
    static char filename[MAX_FILENAME_LENGTH];
    FILE* urandom = NULL;
    unsigned char random_bytes[16];
    size_t i;
    
#ifdef _WIN32
    /* Windows: use CryptGenRandom for secure random */
    HCRYPTPROV hCryptProv;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return NULL;
    }
    if (!CryptGenRandom(hCryptProv, sizeof(random_bytes), random_bytes)) {
        CryptReleaseContext(hCryptProv, 0);
        return NULL;
    }
    CryptReleaseContext(hCryptProv, 0);
#else
    /* POSIX: use /dev/urandom for secure random */
    urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        return NULL;
    }
    
    if (fread(random_bytes, 1, sizeof(random_bytes), urandom) != sizeof(random_bytes)) {
        fclose(urandom);
        return NULL;
    }
    fclose(urandom);
#endif
    
    /* Convert to hex string */
    for (i = 0; i < sizeof(random_bytes); i++) {
        snprintf(filename + (i * 2), 3, "%02x", random_bytes[i]);
    }
    strncat(filename, ".bin", MAX_FILENAME_LENGTH - strlen(filename) - 1);
    
    return filename;
}

/* Create directory with restrictive permissions */
int create_upload_directory(void) {
#ifdef _WIN32
    if (_mkdir(UPLOAD_DIR) != 0 && errno != EEXIST) {
        return 0;
    }
#else
    /* Create directory with restrictive permissions (0700 = owner only) */
    if (mkdir(UPLOAD_DIR, 0700) != 0 && errno != EEXIST) {
        return 0;
    }
#endif
    return 1;
}
/* Validate path to prevent directory traversal */
int is_safe_path(const char* base_dir, const char* filename, char* out_path, size_t out_size) {
    char full_path[PATH_MAX];

    /* Check filename length */
    if (strlen(filename) > MAX_FILENAME_LENGTH) {
        return 0;
    }

    /* Check for path traversal patterns */
    if (strstr(filename, "..") != NULL ||
        strstr(filename, "/") != NULL ||
        strstr(filename, "\\") != NULL) {
        return 0;
    }

    /* Construct full path */
    if (snprintf(full_path, sizeof(full_path), "%s/%s", base_dir, filename) >= sizeof(full_path)) {
        return 0;
    }

#ifdef _WIN32
    char resolved[PATH_MAX];
    if (_fullpath(resolved, full_path, PATH_MAX) == NULL) {
        return 0;
    }

    char base_resolved[PATH_MAX];
    if (_fullpath(base_resolved, base_dir, PATH_MAX) == NULL) {
        return 0;
    }

    if (strncmp(resolved, base_resolved, strlen(base_resolved)) != 0) {
        return 0;
    }

    strncpy(out_path, resolved, out_size - 1);
    out_path[out_size - 1] = '\0';
#else
    /* For POSIX, verify base directory exists and construct path */
    char base_resolved[PATH_MAX];
    if (realpath(base_dir, base_resolved) == NULL) {
        return 0;
    }

    /* Manually construct target path */
    if (snprintf(out_path, out_size, "%s/%s", base_resolved, filename) >= (int) out_size) {
        return 0;
    }
#endif

    return 1;
}

/* Explicit zero memory to clear sensitive data */
void explicit_zero(void* ptr, size_t size) {
    volatile unsigned char* p = (volatile unsigned char*) ptr;
    while (size--) {
        *p++ = 0;
    }
}

char* upload_file(const unsigned char* file_content, size_t content_size, const char* content_type) {
    static char result_msg[256];
    char* safe_filename = NULL;
    char target_path[PATH_MAX];
    int fd = -1;
    ssize_t written;

    /* Initialize result message */
    memset(result_msg, 0, sizeof(result_msg));

    /* Validate content type */
    if (content_type == NULL || strstr(content_type, "multipart/form-data") == NULL) {
        strncpy(result_msg, "Error: Invalid content type", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Enforce maximum file size to prevent DoS attacks */
    if (content_size > MAX_FILE_SIZE) {
        strncpy(result_msg, "Error: File too large", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Create upload directory if it doesn't exist */
    if (!create_upload_directory()) {
        strncpy(result_msg, "Error: Failed to create upload directory", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Generate cryptographically secure random filename */
    safe_filename = generate_secure_filename();
    if (safe_filename == NULL) {
        strncpy(result_msg, "Error: Failed to generate filename", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Validate and normalize path to prevent directory traversal */
    if (!is_safe_path(UPLOAD_DIR, safe_filename, target_path, sizeof(target_path))) {
        strncpy(result_msg, "Error: Invalid file path", sizeof(result_msg) - 1);
        return result_msg;
    }

#ifdef _WIN32
    /* Windows implementation */
    HANDLE hFile = CreateFileA(
        target_path,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        strncpy(result_msg, "Error: Upload failed", sizeof(result_msg) - 1);
        return result_msg;
    }

    DWORD bytesWritten;
    BOOL write_result = WriteFile(hFile, file_content, (DWORD) content_size, &bytesWritten, NULL);
    FlushFileBuffers(hFile);
    CloseHandle(hFile);

    if (!write_result || bytesWritten != content_size) {
        DeleteFileA(target_path);
        strncpy(result_msg, "Error: Upload failed", sizeof(result_msg) - 1);
        return result_msg;
    }
#else
    /* POSIX: use open with O_CREAT|O_EXCL|O_NOFOLLOW to prevent race conditions */
    fd = open(target_path, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600);
    if (fd < 0) {
        strncpy(result_msg, "Error: Upload failed", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Validate that we opened a regular file using fstat on the opened fd */
    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        unlink(target_path);
        strncpy(result_msg, "Error: Invalid file type", sizeof(result_msg) - 1);
        return result_msg;
    }

    /* Write data to the opened file descriptor */
    written = write(fd, file_content, content_size);

    /* Ensure data is written to disk */
    if (fsync(fd) != 0) {
        close(fd);
        unlink(target_path);
        strncpy(result_msg, "Error: Upload failed", sizeof(result_msg) - 1);
        return result_msg;
    }

    close(fd);

    if (written < 0 || (size_t) written != content_size) {
        unlink(target_path);
        strncpy(result_msg, "Error: Upload failed", sizeof(result_msg) - 1);
        return result_msg;
    }
#endif

    snprintf(result_msg, sizeof(result_msg), "File uploaded successfully: %s", safe_filename);
    return result_msg;
}

void run_test_cases(void) {
    printf("=== Running Test Cases ===\n");

    /* Test case 1: Valid small file upload */
    const char* test1_data = "Test content 1";
    char* result1 = upload_file((const unsigned char*) test1_data, strlen(test1_data), "multipart/form-data");
    printf("Test 1 (valid upload): %s\n", result1);

    /* Test case 2: Another valid upload */
    const char* test2_data = "Test content 2";
    char* result2 = upload_file((const unsigned char*) test2_data, strlen(test2_data), "multipart/form-data");
    printf("Test 2 (valid upload): %s\n", result2);

    /* Test case 3: Invalid content type */
    const char* test3_data = "Test content 3";
    char* result3 = upload_file((const unsigned char*) test3_data, strlen(test3_data), "text/plain");
    printf("Test 3 (invalid content type): %s\n", result3);

    /* Test case 4: Large file (1KB) */
    unsigned char* test4_data = (unsigned char*) malloc(1024);
    if (test4_data != NULL) {
        memset(test4_data, 'x', 1024);
        char* result4 = upload_file(test4_data, 1024, "multipart/form-data");
        printf("Test 4 (1KB file): %s\n", result4);
        explicit_zero(test4_data, 1024);
        free(test4_data);
    }

    /* Test case 5: Empty file */
    char* result5 = upload_file((const unsigned char*) "", 0, "multipart/form-data");
    printf("Test 5 (empty file): %s\n", result5);
}


int main(void) {
    run_test_cases();
    return 0;
}
