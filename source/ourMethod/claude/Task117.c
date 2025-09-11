
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#define BUFFER_SIZE 4096
#define MAX_PATH 4096

typedef struct {
    char filename[MAX_PATH];
    size_t size;
} ArchiveEntry;

int is_path_safe(const char* base_path, const char* target_path) {
    char real_base[PATH_MAX];
    char real_target[PATH_MAX];
    
    // Get canonical paths
    if (!realpath(base_path, real_base) || !realpath(target_path, real_target)) {
        return 0;
    }

    // Check if target is under base directory
    return strncmp(real_base, real_target, strlen(real_base)) == 0;
}

int create_directories(const char* path) {
    char tmp[MAX_PATH];
    char *p = NULL;
    size_t len;

    // Input validation
    if (path == NULL || strlen(path) >= MAX_PATH) {
        return -1;
    }

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/') {
        tmp[len - 1] = 0;
    }

    // Create each directory in path
    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }
    
    if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
        return -1;
    }

    return 0;
}

int extract_archive(const char* archive_path, const char* dest_path) {
    FILE *archive = NULL;
    FILE *outfile = NULL;
    char buffer[BUFFER_SIZE];
    char out_path[MAX_PATH];
    ArchiveEntry entry;
    size_t bytes_read;
    int result = -1;

    // Input validation
    if (!archive_path || !dest_path || 
        strlen(archive_path) >= MAX_PATH || 
        strlen(dest_path) >= MAX_PATH) {
        fprintf(stderr, "Invalid input parameters\\n");
        return -1;
    }

    // Open archive file
    archive = fopen(archive_path, "rb");
    if (!archive) {
        fprintf(stderr, "Failed to open archive file: %s\\n", archive_path);
        return -1;
    }

    // Create destination directory
    if (create_directories(dest_path) != 0) {
        fprintf(stderr, "Failed to create destination directory\\n");
        goto cleanup;
    }

    // Process archive entries
    while (fread(&entry, sizeof(entry), 1, archive) == 1) {
        // Validate filename
        if (strlen(entry.filename) >= MAX_PATH) {
            fprintf(stderr, "Invalid filename length\\n");
            goto cleanup;
        }

        // Construct output path
        if (snprintf(out_path, sizeof(out_path), "%s/%s", dest_path, entry.filename) >= MAX_PATH) {
            fprintf(stderr, "Path too long\\n");
            goto cleanup;
        }

        // Check for path traversal
        if (!is_path_safe(dest_path, out_path)) {
            fprintf(stderr, "Invalid path detected: %s\\n", entry.filename);
            goto cleanup;
        }

        // Create parent directories
        char *last_slash = strrchr(out_path, '/');
        if (last_slash) {
            *last_slash = '\\0';
            if (create_directories(out_path) != 0) {
                fprintf(stderr, "Failed to create directory: %s\\n", out_path);
                goto cleanup;
            }
            *last_slash = '/';
        }

        // Open output file
        outfile = fopen(out_path, "wb");
        if (!outfile) {
            fprintf(stderr, "Failed to create output file: %s\\n", out_path);
            goto cleanup;
        }

        // Copy file contents
        size_t remaining = entry.size;
        while (remaining > 0) {
            bytes_read = fread(buffer, 1, 
                             remaining > BUFFER_SIZE ? BUFFER_SIZE : remaining, 
                             archive);
            if (bytes_read == 0) break;
            
            if (fwrite(buffer, 1, bytes_read, outfile) != bytes_read) {
                fprintf(stderr, "Failed to write to output file\\n");
                goto cleanup;
            }
            remaining -= bytes_read;
        }

        fclose(outfile);
        outfile = NULL;
    }

    result = 0;

cleanup:
    if (archive) fclose(archive);
    if (outfile) fclose(outfile);
    return result;
}

int main() {
    // Test case 1', type='text')