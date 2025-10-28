
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <archive.h>
#include <archive_entry.h>
#include <limits.h>
#include <errno.h>

/* Maximum security limits to prevent resource exhaustion */
#define MAX_FILE_SIZE (100 * 1024 * 1024)  /* 100MB per file */
#define MAX_TOTAL_SIZE (500 * 1024 * 1024) /* 500MB total */
#define MAX_FILES 10000
#define BASE_DIR "/tmp/unpack"
#define BUFFER_SIZE 8192

/* Secure path validation preventing directory traversal */
int validate_path(const char* base, const char* path, char* resolved, size_t resolved_size) {
    /* Validate inputs are not NULL */
    if (!base || !path || !resolved || resolved_size == 0) {
        return 0;
    }
    
    /* Build full path safely with bounds checking */
    char full_path[PATH_MAX];
    int ret = snprintf(full_path, sizeof(full_path), "%s/%s", base, path);
    if (ret < 0 || ret >= (int)sizeof(full_path)) {
        return 0;
    }
    
    /* Resolve to canonical path (prevents .. and symlinks) */
    char* real = realpath(full_path, resolved);
    if (!real) {
        /* If file doesn't exist yet, validate parent directory */
        char parent[PATH_MAX];
        char* last_slash = strrchr(full_path, '/');
        if (!last_slash) {
            return 0;
        }

        size_t parent_len = last_slash - full_path;
        if (parent_len >= sizeof(parent)) {
            return 0;
        }

        memcpy(parent, full_path, parent_len);
        parent[parent_len] = '\0';

        char parent_real[PATH_MAX];
        if (!realpath(parent, parent_real)) {
            return 0;
        }

        /* Build resolved path from parent */
        ret = snprintf(resolved, resolved_size, "%s/%s", parent_real, last_slash + 1);
        if (ret < 0 || ret >= (int)resolved_size) {
            return 0;
        }
    }

    /* Validate resolved path starts with base directory */
    char base_real[PATH_MAX];
    if (!realpath(base, base_real)) {
        return 0;
    }

    size_t base_len = strlen(base_real);
    if (strncmp(resolved, base_real, base_len) != 0) {
        return 0;
    }

    /* Ensure there's a path separator after base (or it's exactly the base) */
    if (resolved[base_len] != '\0' && resolved[base_len] != '/') {
        return 0;
    }

    return 1;
}

/* Secure tar extraction function preventing path traversal and resource exhaustion */
int extract_tar_archive(const char* tar_file_path, const char* compression_type) {
    struct archive* a = NULL;
    struct archive_entry* entry = NULL;
    size_t total_bytes_extracted = 0;
    int file_count = 0;
    int result = -1;

    /* Validate inputs are not NULL */
    if (!tar_file_path) {
        fprintf(stderr, "Invalid tar file path\n");
        return -1;
    }

    /* Create base directory with restrictive permissions (0700) */
    struct stat st;
    if (stat(BASE_DIR, &st) != 0) {
        if (mkdir(BASE_DIR, 0700) != 0) {
            fprintf(stderr, "Failed to create base directory\n");
            return -1;
        }
    }

    /* Initialize libarchive for reading */
    a = archive_read_new();
    if (!a) {
        fprintf(stderr, "Failed to create archive reader\n");
        return -1;
    }

    /* Enable only tar format (no automatic format detection for security) */
    archive_read_support_format_tar(a);

    /* Set compression based on type */
    if (compression_type && strcmp(compression_type, "gzip") == 0) {
        archive_read_support_filter_gzip(a);
    } else if (compression_type && strcmp(compression_type, "bzip2") == 0) {
        archive_read_support_filter_bzip2(a);
    } else {
        archive_read_support_filter_none(a);
    }

    /* Open archive with validation */
    if (archive_read_open_filename(a, tar_file_path, 10240) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open archive: %s\n", archive_error_string(a));
        goto cleanup;
    }

    /* Process each entry in archive */
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        /* Limit number of files to prevent zip bombs */
        if (++file_count > MAX_FILES) {
            fprintf(stderr, "Archive contains too many files\n");
            goto cleanup;
        }

        /* Only process regular files */
        mode_t filetype = archive_entry_filetype(entry);
        if (!S_ISREG(filetype)) {
            archive_read_data_skip(a);
            continue;
        }

        /* Validate entry size */
        int64_t entry_size = archive_entry_size(entry);
        if (entry_size < 0 || (size_t)entry_size > MAX_FILE_SIZE) {
            fprintf(stderr, "Entry size exceeds maximum\n");
            goto cleanup;
        }

        /* Check total size */
        if (total_bytes_extracted + entry_size > MAX_TOTAL_SIZE) {
            fprintf(stderr, "Total extraction size exceeds maximum\n");
            goto cleanup;
        }

        /* Get and validate entry path */
        const char* entry_name = archive_entry_pathname(entry);
        if (!entry_name || entry_name[0] == '\0') {
            archive_read_data_skip(a);
            continue;
        }

        /* Remove leading slashes for security */
        while (*entry_name == '/' || *entry_name == '\\') {
            entry_name++;
        }

        /* Validate path doesn't attempt traversal */
        char resolved_path[PATH_MAX];
        if (!validate_path(BASE_DIR, entry_name, resolved_path, sizeof(resolved_path))) {
            fprintf(stderr, "Path traversal attempt detected: %s\\n", entry_name);
            goto cleanup;
        }
        
        /* Open output file with restrictive permissions (0600) using open-then-validate */
        int fd = open(resolved_path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
        if (fd < 0) {
            fprintf(stderr, "Failed to create file: %s\\n", resolved_path);
            goto cleanup;
        }
        
        /* Validate opened file descriptor */
        struct stat fd_stat;
        if (fstat(fd, &fd_stat) != 0 || !S_ISREG(fd_stat.st_mode)) {
            fprintf(stderr, "Opened descriptor is not a regular file\\n");
            close(fd);
            goto cleanup;
        }
        
        /* Extract data with size validation */
        size_t bytes_written = 0;
        char buffer[BUFFER_SIZE];
        
        ssize_t bytes_read;
        while ((bytes_read = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
            /* Check for integer overflow */
            if (bytes_written > SIZE_MAX - bytes_read) {
                fprintf(stderr, "Integer overflow detected\\n");
                close(fd);
                goto cleanup;
            }
            
            /* Validate against declared size */
            if (bytes_written + bytes_read > (size_t)entry_size) {
                fprintf(stderr, "Entry size mismatch\\n");
                close(fd);
                goto cleanup;
            }
            
            ssize_t written = write(fd, buffer, bytes_read);
            if (written != bytes_read) {
                fprintf(stderr, "Write error\\n");
                close(fd);
                goto cleanup;
            }
            
            bytes_written += bytes_read;
        }
        
        /* Ensure data is written to disk */
        fsync(fd);
        close(fd);
        
        total_bytes_extracted += bytes_written;
    }
    
    result = 0;

cleanup:
    if (a) {
        archive_read_free(a);
    }
    return result;
}

/* Secure file reading with TOCTOU prevention */
char* read_file(const char* file_path) {
    int fd = -1;
    char* content = NULL;
    
    /* Validate input */
    if (!file_path || file_path[0] == '\0') {
        fprintf(stderr, "Invalid file path\\n");
        return NULL;
    }
    
    /* Validate and resolve path */
    char resolved_path[PATH_MAX];
    if (!validate_path(BASE_DIR, file_path, resolved_path, sizeof(resolved_path))) {
        fprintf(stderr, "Path traversal attempt detected\\n");
        return NULL;
    }
    
    /* Open file first using open (TOCTOU prevention) */
    fd = open(resolved_path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file\\n");
        return NULL;
    }
    
    /* Validate opened file descriptor */
    struct stat fd_stat;
    if (fstat(fd, &fd_stat) != 0) {
        fprintf(stderr, "Failed to stat file\\n");
        close(fd);
        return NULL;
    }
    
    /* Ensure it's a regular file */
    if (!S_ISREG(fd_stat.st_mode)) {
        fprintf(stderr, "Not a regular file\n");
        close(fd);
        return NULL;
    }

    /* Check file size */
    if (fd_stat.st_size < 0 || (size_t)fd_stat.st_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File size exceeds maximum\n");
        close(fd);
        return NULL;
    }

    /* Allocate buffer with space for null terminator */
    size_t file_size = fd_stat.st_size;
    content = (char*)malloc(file_size + 1);
    if (!content) {
        fprintf(stderr, "Memory allocation failed\n");
        close(fd);
        return NULL;
    }

    /* Initialize buffer to ensure null termination */
    memset(content, 0, file_size + 1);

    /* Read file content */
    size_t total_read = 0;
    while (total_read < file_size) {
        ssize_t bytes_read = read(fd, content + total_read, file_size - total_read);
        if (bytes_read < 0) {
            fprintf(stderr, "Read error\n");
            free(content);
            close(fd);
            return NULL;
        }
        if (bytes_read == 0) {
            break;
        }
        total_read += bytes_read;
    }

    close(fd);
    content[total_read] = '\0';
    return content;
}

int main(void) {
    /* Test case 1: Extract uncompressed tar */
    printf("Test 1: Extract uncompressed tar\\n");
    /* extract_tar_archive("/path/to/archive.tar", NULL); */
    printf("Note: Requires actual tar file to test\\n");
    
    /* Test case 2: Extract gzip compressed tar */
    printf("\\nTest 2: Extract gzip tar\\n");
    /* extract_tar_archive("/path/to/archive.tar.gz", "gzip"); */
    printf("Note: Requires actual tar.gz file to test\\n");
    
    /* Test case 3: Extract bzip2 compressed tar */
    printf("\\nTest 3: Extract bzip2 tar\\n");
    /* extract_tar_archive("/path/to/archive.tar.bz2", "bzip2"); */
    printf("Note: Requires actual tar.bz2 file to test\\n");
    
    /* Test case 4: Read extracted file */
    printf("\\nTest 4: Read file\\n");
    /* char* content = read_file("example.txt"); */
    /* if (content) { printf("Content: %s\\n", content); free(content); } */
    printf("Note: Requires extracted file to test\\n");
    
    /* Test case 5: Path traversal prevention */
    printf("\\nTest 5: Path traversal prevention\\n");
    char* content = read_file("../../etc/passwd");
    if (content) {
        printf("FAIL: Should have returned NULL\\n");
        free(content);
    } else {
        printf("PASS: Path traversal blocked\\n");
    }
    
    return 0;
}
