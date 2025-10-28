
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024)
#define MAX_FILENAME_LEN 255
#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 8192

/* Allowed file extensions */
static const char* ALLOWED_EXTENSIONS[] = {
    "txt", "pdf", "jpg", "jpeg", "png", "doc", "docx", NULL
};

/* Function prototypes */
char* sanitize_filename(const char* filename);
char* get_file_extension(const char* filename);
int is_extension_allowed(const char* extension);
char* generate_unique_filename(const char* original_filename);
void create_upload_directory(void);
char* normalize_and_validate_path(const char* base_path, const char* filename);
int upload_file(const char* filename, const unsigned char* content, size_t content_size);

/* Secure file upload handler */
int upload_file(const char* filename, const unsigned char* content, size_t content_size) {
    char* sanitized_filename = NULL;
    char* extension = NULL;
    char* unique_filename = NULL;
    char* target_path = NULL;
    int fd = -1;
    int result = -1;
    struct stat st;
    ssize_t bytes_written = 0;
    
    /* Input validation: reject NULL or empty filename */
    if (filename == NULL || filename[0] == '\0') {
        fprintf(stderr, "Error: Invalid filename\\n");
        goto cleanup;
    }
    
    /* Validate content pointer and size */
    if (content == NULL) {
        fprintf(stderr, "Error: Invalid content\\n");
        goto cleanup;
    }
    
    /* Validate file size */
    if (content_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File size exceeds maximum allowed size\\n");
        goto cleanup;
    }
    
    /* Sanitize filename to prevent path traversal */
    sanitized_filename = sanitize_filename(filename);
    if (sanitized_filename == NULL || sanitized_filename[0] == '\0') {
        fprintf(stderr, "Error: Invalid filename after sanitization\\n");
        goto cleanup;
    }
    
    /* Validate file extension */
    extension = get_file_extension(sanitized_filename);
    if (extension == NULL || !is_extension_allowed(extension)) {
        fprintf(stderr, "Error: File type not allowed\\n");
        goto cleanup;
    }
    
    /* Create uploads directory with restrictive permissions */
    create_upload_directory();
    
    /* Generate unique filename */
    unique_filename = generate_unique_filename(sanitized_filename);
    if (unique_filename == NULL) {
        fprintf(stderr, "Error: Failed to generate unique filename\\n");
        goto cleanup;
    }
    
    /* Normalize and validate target path */
    target_path = normalize_and_validate_path(UPLOAD_DIR, unique_filename);
    if (target_path == NULL) {
        fprintf(stderr, "Error: Path validation failed\\n");
        goto cleanup;
    }
    
    /* Open file with O_CREAT|O_EXCL|O_WRONLY for atomic creation
     * O_EXCL prevents TOCTOU by failing if file exists
     * O_NOFOLLOW prevents following symlinks */
    fd = open(target_path, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        fprintf(stderr, "Error: Failed to create file: %s\\n", strerror(errno));
        goto cleanup;
    }
    
    /* Validate opened file descriptor using fstat */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Error: Failed to stat file\\n");
        close(fd);
        unlink(target_path);
        goto cleanup;
    }
    
/* Ensure it's a regular file */
if (!S_ISREG(st.st_mode)) {
    fprintf(stderr, "Error: Target is not a regular file\n");
    close(fd);
    unlink(target_path);
    goto cleanup;
}

/* Write content to file */
bytes_written = write(fd, content, content_size);
if (bytes_written < 0 || (size_t) bytes_written != content_size) {
    fprintf(stderr, "Error: Failed to write file content\n");
    close(fd);
    unlink(target_path);
    goto cleanup;
}

/* Flush to disk */
if (fsync(fd) != 0) {
    fprintf(stderr, "Error: Failed to sync file to disk\n");
    close(fd);
    unlink(target_path);
    goto cleanup;
}

close(fd);
printf("File uploaded successfully: %s\n", unique_filename);
result = 0;

cleanup:
/* Free allocated memory */
if (sanitized_filename != NULL) free(sanitized_filename);
if (extension != NULL) free(extension);
if (unique_filename != NULL) free(unique_filename);
if (target_path != NULL) free(target_path);

return result;
}

char* sanitize_filename(const char* filename) {
    if (filename == NULL) return NULL;

    size_t len = strlen(filename);
    if (len == 0 || len > MAX_FILENAME_LEN) return NULL;

    /* Allocate memory for sanitized filename */
    char* sanitized = (char*) malloc(len + 1);
    if (sanitized == NULL) return NULL;

    size_t j = 0;
    /* Remove path separators and null bytes */
    for (size_t i = 0; i < len; i++) {
        if (filename[i] != '/' && filename[i] != '\\' && filename[i] != '\0') {
            sanitized[j++] = filename[i];
        }
    }
    sanitized[j] = '\0';

    /* Remove leading/trailing dots and spaces */
    size_t start = 0;
    while (sanitized[start] == '.' || sanitized[start] == ' ') start++;

    size_t end = strlen(sanitized);
    while (end > start && (sanitized[end - 1] == '.' || sanitized[end - 1] == ' ')) end--;

    if (start >= end) {
        free(sanitized);
        return NULL;
    }

    memmove(sanitized, sanitized + start, end - start);
    sanitized[end - start] = '\0';

    return sanitized;
}

char* get_file_extension(const char* filename) {
    if (filename == NULL) return NULL;

    const char* dot = strrchr(filename, '.');
    if (dot == NULL || dot == filename || *(dot + 1) == '\0') {
        return NULL;
    }

    size_t ext_len = strlen(dot + 1);
    char* extension = (char*) malloc(ext_len + 1);
    if (extension == NULL) return NULL;

    strcpy(extension, dot + 1);

    /* Convert to lowercase for comparison */
    for (size_t i = 0; i < ext_len; i++) {
        extension[i] = tolower((unsigned char) extension[i]);
    }

    return extension;
}

int is_extension_allowed(const char* extension) {
    if (extension == NULL) return 0;

    for (int i = 0; ALLOWED_EXTENSIONS[i] != NULL; i++) {
        if (strcmp(extension, ALLOWED_EXTENSIONS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* generate_unique_filename(const char* original_filename) {
    if (original_filename == NULL) return NULL;

    /* Generate random hex string */
    unsigned char random_bytes[16];
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        /* Fallback to time-based seed */
        srand((unsigned int) time(NULL));
        for (int i = 0; i < 16; i++) {
            random_bytes[i] = (unsigned char) (rand() % 256);
        }
    } else {
        if (fread(random_bytes, 1, 16, urandom) != 16) {
            fclose(urandom);
            return NULL;
        }
        fclose(urandom);
    }

    char random_hex[33];
    for (int i = 0; i < 16; i++) {
        snprintf(random_hex + i * 2, 3, "%02x", random_bytes[i]);
    }
    random_hex[32] = '\0';

    /* Extract base name and extension */
    const char* dot = strrchr(original_filename, '.');
    size_t base_len = dot ? (size_t) (dot - original_filename) : strlen(original_filename);
    if (base_len > 50) base_len = 50;

    /* Allocate memory for unique filename */
    size_t unique_len = base_len + 1 + 32 + (dot ? strlen(dot) : 0) + 1;
    char* unique_filename = (char*) malloc(unique_len);
    if (unique_filename == NULL) return NULL;

    /* Construct unique filename */
    snprintf(
        unique_filename,
        unique_len,
        "%.*s_%s%s",
        (int) base_len,
        original_filename,
        random_hex,
        dot ? dot : ""
    );

    return unique_filename;
}

void create_upload_directory(void) {
    struct stat st;
    if (stat(UPLOAD_DIR, &st) != 0) {
        /* Directory doesn't exist, create it with restrictive permissions */
        if (mkdir(UPLOAD_DIR, S_IRWXU) != 0) {
            fprintf(stderr, "Warning: Failed to create upload directory\\n");
        }
    }
}

char* normalize_and_validate_path(const char* base_path, const char* filename) {
    if (base_path == NULL || filename == NULL) return NULL;
    
    /* Check for path traversal patterns */
    if (strstr(filename, "..") != NULL) {
        fprintf(stderr, "Error: Path traversal attempt detected\\n");
        return NULL;
    }
    
    /* Construct full path */
    size_t path_len = strlen(base_path) + 1 + strlen(filename) + 1;
    char* full_path = (char*)malloc(path_len);
    if (full_path == NULL) return NULL;
    
    snprintf(full_path, path_len, "%s/%s", base_path, filename);
    
    /* Ensure path starts with base directory */
    if (strncmp(full_path, base_path, strlen(base_path)) != 0) {
        free(full_path);
        return NULL;
    }
    
    return full_path;
}

int main(void) {
    /* Test case 1: Valid text file */
    {
        const char* content1 = "Test file content";
        if (upload_file("test.txt", (const unsigned char*)content1, strlen(content1)) == 0) {
            printf("Test 1 passed\\n");
        } else {
            printf("Test 1 failed\\n");
        }
    }
    
    /* Test case 2: Path traversal attempt (should fail) */
    {
        const char* content2 = "Malicious content";
        if (upload_file("../../../etc/passwd.txt", (const unsigned char*)content2, strlen(content2)) != 0) {
            printf("Test 2 passed: Rejected path traversal\\n");
        } else {
            printf("Test 2 failed: Should have rejected path traversal\\n");
        }
    }
    
    /* Test case 3: Invalid file extension (should fail) */
    {
        const char* content3 = "<?php system($_GET['cmd']); ?>";
        if (upload_file("shell.php", (const unsigned char*)content3, strlen(content3)) != 0) {
            printf("Test 3 passed: Rejected invalid extension\\n");
        } else {
            printf("Test 3 failed: Should have rejected .php extension\\n");
        }
    }
    
    /* Test case 4: Valid PDF file */
    {
        const char* content4 = "%PDF-1.4 test";
        if (upload_file("document.pdf", (const unsigned char*)content4, strlen(content4)) == 0) {
            printf("Test 4 passed\\n");
        } else {
            printf("Test 4 failed\\n");
        }
    }
    
    /* Test case 5: Empty filename (should fail) */
    {
        const char* content5 = "Content";
        if (upload_file("", (const unsigned char*)content5, strlen(content5)) != 0) {
            printf("Test 5 passed: Rejected empty filename\\n");
        } else {
            printf("Test 5 failed: Should have rejected empty filename\\n");
        }
    }
    
    return 0;
}
