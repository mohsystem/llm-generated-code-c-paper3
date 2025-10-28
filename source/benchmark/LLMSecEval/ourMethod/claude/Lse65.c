
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME_LENGTH 255
#define BUFFER_SIZE 8192

/* Secure random generation for unique filenames */
static void generate_random_id(char *output, size_t len) {
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f) {
        /* Fallback to time-based seed if /dev/urandom unavailable */
        srand((unsigned int)time(NULL));
        size_t i;
        for (i = 0; i < len - 1; i++) {
            output[i] = "0123456789abcdef"[rand() % 16];
        }
        output[len - 1] = '\0';
        return;
    }
    
    unsigned char bytes[16];
    if (fread(bytes, 1, sizeof(bytes), f) != sizeof(bytes)) {
        fclose(f);
        output[0] = '\0';
        return;
    }
    fclose(f);
    
    size_t i;
    for (i = 0; i < sizeof(bytes) && i * 2 < len - 1; i++) {
        snprintf(output + i * 2, 3, "%02x", bytes[i]);
    }
}
/* Sanitize filename: remove path components and dangerous characters */
static void sanitize_filename(char* output, const char* input, size_t max_len) {
    if (!input || !output || max_len == 0) return;

    /* Extract basename only (remove directory path) */
    const char* basename = strrchr(input, '/');
    if (basename) {
        basename++;
    } else {
        basename = strrchr(input, '\\');
        basename = basename ? basename + 1 : input;
    }

    /* Copy only alphanumeric and safe characters */
    size_t i, j = 0;
    for (i = 0; basename[i] && j < max_len - 1; i++) {
        char c = basename[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-') {
            output[j++] = c;
        } else {
            output[j++] = '_';
        }
    }
    output[j] = '\0';
}

/* Validate PDF magic bytes (PDF header: %PDF-) */
static int is_valid_pdf(const unsigned char* data, size_t len) {
    if (len < 5) return 0;
    return (data[0] == 0x25 && data[1] == 0x50 &&
            data[2] == 0x44 && data[3] == 0x46 && data[4] == 0x2D);
}

/* Check if path is within base directory (prevent path traversal) */
static int is_path_safe(const char* base_dir, const char* path) {
    char real_base[PATH_MAX];
    char real_path[PATH_MAX];

    /* Resolve base directory to canonical path */
    if (!realpath(base_dir, real_base)) return 0;

    /* For non-existent files, check parent directory */
    if (!realpath(path, real_path)) {
        char parent[PATH_MAX];
        strncpy(parent, path, sizeof(parent) - 1);
        parent[sizeof(parent) - 1] = '\0';

        char* last_slash = strrchr(parent, '/');
        if (last_slash) {
            *last_slash = '\0';
            if (!realpath(parent, real_path)) return 0;
        } else {
            return 0;
        }
    }

    /* Verify the resolved path starts with base directory */
    size_t base_len = strlen(real_base);
    return (strncmp(real_path, real_base, base_len) == 0);
}

/* Save file securely with comprehensive validation */
char* save_file(const char* filename, const unsigned char* content, size_t content_len) {
    static char result[512];
    result[0] = '\0';

    /* Input validation: check all parameters */
    if (!filename || !content || content_len == 0 || content_len > MAX_FILE_SIZE) {
        snprintf(result, sizeof(result), "Invalid file data");
        return result;
    }

    /* Validate filename length */
    if (strlen(filename) > MAX_FILENAME_LENGTH) {
        snprintf(result, sizeof(result), "Filename too long");
        return result;
    }

    /* Sanitize filename to prevent path traversal and injection */
    char sanitized[MAX_FILENAME_LENGTH + 1];
    sanitize_filename(sanitized, filename, sizeof(sanitized));

    /* Validate PDF extension */
    size_t len = strlen(sanitized);
    if (len < 5 || strcasecmp(sanitized + len - 4, ".pdf") != 0) {
        snprintf(result, sizeof(result), "Only PDF files allowed");
        return result;
    }

    /* Validate PDF magic bytes to ensure file type */
    if (!is_valid_pdf(content, content_len)) {
        snprintf(result, sizeof(result), "Not a valid PDF file");
        return result;
    }

    /* Create uploads directory with restrictive permissions (owner-only) */
    struct stat st;
    if (stat(UPLOAD_DIR, &st) != 0) {
        if (mkdir(UPLOAD_DIR, 0700) != 0) {
            snprintf(result, sizeof(result), "Failed to create upload directory");
            return result;
        }
    }

    /* Generate unique filename to prevent overwrites */
    char random_id[33];
    generate_random_id(random_id, sizeof(random_id));

    char safe_filename[PATH_MAX];
    snprintf(safe_filename, sizeof(safe_filename), "%s/%s_%s",
             UPLOAD_DIR, random_id, sanitized);

    /* Verify path safety against traversal attacks */
    if (!is_path_safe(UPLOAD_DIR, safe_filename)) {
        snprintf(result, sizeof(result), "Path traversal attempt detected");
        return result;
    }

    /* Open file with secure flags:
       O_WRONLY: write-only access
       O_CREAT|O_EXCL: atomic creation, fail if exists
       O_NOFOLLOW: prevent symlink attacks
       O_CLOEXEC: close on exec for security
       0600: owner read/write only */
    int fd = open(safe_filename, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600);
    if (fd < 0) {
        snprintf(result, sizeof(result), "Failed to create file");
        return result;
    }

    /* Validate the opened file descriptor to ensure it's a regular file */
    struct stat file_stat;
    if (fstat(fd, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        close(fd);
        unlink(safe_filename);
        snprintf(result, sizeof(result), "File validation failed");
        return result;
    }

    /* Write content in chunks, checking each write operation */
    size_t written = 0;
    while (written < content_len) {
        ssize_t w = write(fd, content + written, content_len - written);
        if (w <= 0) {
            close(fd);
            unlink(safe_filename);
            snprintf(result, sizeof(result), "Write failed");
            return result;
        }
        written += (size_t) w;
    }

    /* Ensure data is written to disk before closing */
    if (fsync(fd) != 0) {
        close(fd);
        unlink(safe_filename);
        snprintf(result, sizeof(result), "Sync failed");
        return result;
    }

    close(fd);

    snprintf(result, sizeof(result), "File uploaded successfully: %s_%s",
             random_id, sanitized);
    return result;
}

int main(void) {
    printf("PDF Upload Server - Secure File Handler\\n\\n");
    printf("Test Cases:\\n");
    printf("1. Valid PDF upload\\n");
    printf("2. File too large\\n");
    printf("3. Invalid filename with path traversal\\n");
    printf("4. Non-PDF file\\n");
    printf("5. Empty file\\n\\n");
    
    /* Test case 1: Valid PDF with proper header */
    unsigned char valid_pdf[] = "%PDF-1.4\\n%Test content";
    char *result1 = save_file("test.pdf", valid_pdf, sizeof(valid_pdf) - 1);
    printf("Test 1: %s\\n", result1);
    
    /* Test case 2: File too large - validation prevents this */
    printf("Test 2: File too large (check implemented in validation)\\n");
    
    /* Test case 3: Path traversal attempt - should be blocked */
    char *result3 = save_file("../../../etc/passwd.pdf", valid_pdf, sizeof(valid_pdf) - 1);
    printf("Test 3: %s\\n", result3);
    
    /* Test case 4: Non-PDF file - should fail magic byte check */
    unsigned char invalid[] = "Not a PDF file";
    char *result4 = save_file("test.pdf", invalid, sizeof(invalid) - 1);
    printf("Test 4: %s\\n", result4);
    
    /* Test case 5: Empty file - should fail validation */
    char *result5 = save_file("test.pdf", NULL, 0);
    printf("Test 5: %s\\n", result5);
    
    return 0;
}
