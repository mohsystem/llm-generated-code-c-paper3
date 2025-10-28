
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

/* Security: Define maximum file size to prevent DoS (10MB) */
#define MAX_FILE_SIZE (10 * 1024 * 1024)
/* Security: Define upload directory */
#define UPLOAD_DIR "uploads"
/* Security: Maximum filename length to prevent buffer issues */
#define MAX_FILENAME_LENGTH 255
/* Security: Maximum path length */
#define MAX_PATH_LENGTH 512

/* Security: Allowed file extensions whitelist */
static const char* ALLOWED_EXTENSIONS[] = {".txt", ".pdf", ".jpg", ".png", NULL};

/* Security: Check if extension is allowed */
static int is_extension_allowed(const char* extension) {
    if (extension == NULL) {
        return 0;
    }

    for (int i = 0; ALLOWED_EXTENSIONS[i] != NULL; i++) {
        if (strcasecmp(extension, ALLOWED_EXTENSIONS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Security: Extract basename to prevent path traversal */
static const char* get_basename(const char* path) {
    if (path == NULL) {
        return NULL;
    }

    const char* last_slash = strrchr(path, '/');
    const char* last_backslash = strrchr(path, '\\');
    const char* basename = path;

    if (last_slash != NULL && last_slash > basename) {
        basename = last_slash + 1;
    }
    if (last_backslash != NULL && last_backslash > basename) {
        basename = last_backslash + 1;
    }

    return basename;
}

/* Security: Get file extension */
static const char* get_extension(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    const char* dot = strrchr(filename, '.');
    if (dot != NULL && dot > filename) {
        return dot;
    }
    return NULL;
}

/* Security: Validate filename contains only safe characters */
static int is_safe_filename(const char* filename) {
    if (filename == NULL || strlen(filename) == 0) {
        return 0;
    }

    for (size_t i = 0; i < strlen(filename); i++) {
        char c = filename[i];
        if (!isalnum((unsigned char) c) && c != '_' && c != '.' && c != '-') {
            return 0;
        }
    }
    return 1;
}

/* Security: Validate filename */
static int is_valid_filename(const char* filename) {
    if (filename == NULL || strlen(filename) == 0 || strlen(filename) > MAX_FILENAME_LENGTH) {
        return 0;
    }

    /* Security: Extract basename to prevent path traversal */
    const char* basename = get_basename(filename);
    if (basename == NULL || strlen(basename) == 0) {
        return 0;
    }

    /* Security: Validate filename contains only safe characters */
    if (!is_safe_filename(basename)) {
        return 0;
    }

    /* Security: Check file extension against whitelist */
    const char* extension = get_extension(basename);
    if (!is_extension_allowed(extension)) {
        return 0;
    }

    return 1;
}

/* Security: Create upload directory with restrictive permissions */
static int create_upload_directory(void) {
    struct stat st = {0};

    if (stat(UPLOAD_DIR, &st) == -1) {
        /* Security: Create directory with mode 0700 (owner only) */
        if (mkdir(UPLOAD_DIR, 0700) != 0) {
            perror("Failed to create upload directory");
            return 0;
        }
    }
    return 1;
}

/* Security: Save file with validation and safe operations */
static const char* save_file(const char* filename, const unsigned char* content, size_t content_size) {
    if (filename == NULL || content == NULL) {
        return "Error: Invalid input";
    }

    /* Security: Validate content size */
    if (content_size > MAX_FILE_SIZE) {
        return "Error: File too large";
    }

    /* Security: Validate filename */
    if (!is_valid_filename(filename)) {
        return "Error: Invalid filename";
    }

    /* Security: Generate random unique prefix */
    unsigned char random_bytes[16];
    if (RAND_bytes(random_bytes, sizeof(random_bytes)) != 1) {
        return "Error: Failed to generate random data";
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(random_bytes, sizeof(random_bytes), hash);

    char hex_prefix[33];
    memset(hex_prefix, 0, sizeof(hex_prefix));
    for (int i = 0; i < 16; i++) {
        snprintf(hex_prefix + (i * 2), 3, "%02x", hash[i]);
    }

    /* Security: Construct safe filename */
    char safe_filename[MAX_PATH_LENGTH];
    const char* basename = get_basename(filename);
    int ret = snprintf(safe_filename, sizeof(safe_filename), "%s/%s_%s", UPLOAD_DIR, hex_prefix, basename);
    if (ret < 0 || ret >= (int) sizeof(safe_filename)) {
        return "Error: Filename too long";
    }

    /* Security: Create temp file with O_CREAT | O_EXCL | O_NOFOLLOW */
    char temp_filename[MAX_PATH_LENGTH];
    ret = snprintf(temp_filename, sizeof(temp_filename), "%s/upload_XXXXXX.tmp", UPLOAD_DIR);
    if (ret < 0 || ret >= (int) sizeof(temp_filename)) {
        return "Error: Temp filename too long";
    }

    /* Security: Open with restrictive permissions (0600) */
    int fd = open(temp_filename, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW, 0600);
    if (fd < 0) {
        perror("Failed to create temp file");
        return "Error: Failed to create temp file";
    }

    /* Security: Write content */
    ssize_t written = write(fd, content, content_size);
    if (written < 0 || (size_t) written != content_size) {
        close(fd);
        unlink(temp_filename);
        return "Error: Failed to write file";
    }

    /* Security: Sync to disk */
    if (fsync(fd) != 0) {
        close(fd);
        unlink(temp_filename);
        return "Error: Failed to sync file";
    }

    close(fd);

    /* Security: Atomic rename to final location */
    if (rename(temp_filename, safe_filename) != 0) {
        unlink(temp_filename);
        return "Error: Failed to move file";
    }

    return "File uploaded successfully";
}

static void run_tests(void) {
    printf("\n=== Running Test Cases ===\n");

    /* Test 1: Valid filename */
    printf("Test 1: Valid filename 'test.txt' - Expected: Pass\n");
    printf("Result: %s\n", is_valid_filename("test.txt") ? "PASS" : "FAIL");

    /* Test 2: Path traversal attempt */
    printf("\nTest 2: Path traversal '../etc/passwd' - Expected: Fail\n");
    printf("Result: %s\n", !is_valid_filename("../etc/passwd") ? "PASS" : "FAIL");

    /* Test 3: Invalid extension */
    printf("\nTest 3: Invalid extension 'file.exe' - Expected: Fail\n");
    printf("Result: %s\n", !is_valid_filename("file.exe") ? "PASS" : "FAIL");

    /* Test 4: Special characters */
    printf("\nTest 4: Special characters 'file<>.txt' - Expected: Fail\n");
    printf("Result: %s\n", !is_valid_filename("file<>.txt") ? "PASS" : "FAIL");

    /* Test 5: Maximum length */
    printf("\nTest 5: Filename exceeds max length - Expected: Fail\n");
    char long_name[300];
    memset(long_name, 'a', 256);
    strcpy(long_name + 256, ".txt");
    printf("Result: %s\\n", !is_valid_filename(long_name) ? "PASS" : "FAIL");
}

int main(void) {
    /* Security: Initialize OpenSSL random number generator */
    if (RAND_status() != 1) {
        fprintf(stderr, "Failed to initialize random number generator\\n");
        return 1;
    }

    /* Security: Create upload directory */
    if (!create_upload_directory()) {
        fprintf(stderr, "Failed to create upload directory\\n");
        return 1;
    }

    printf("Secure File Upload Server Initialized\\n");
    printf("Upload directory: %s\\n", UPLOAD_DIR);
    printf("Max file size: %zu bytes\\n", (size_t)MAX_FILE_SIZE);

    /* Run test cases */
    run_tests();

    return 0;
}
