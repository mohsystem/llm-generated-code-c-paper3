#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
/* Security: Validate and sanitize filename to prevent path traversal */
int validate_filename(const char* filename) {
    if (filename == NULL || strlen(filename) == 0) {
        return 0;
    }

    /* Security: Reject path traversal patterns */
    if (strstr(filename, "..") != NULL ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL) {
        return 0;
        }

    return 1;
}

/* Security: Validate path is within base directory */
int validate_path_within_base(const char* base_dir, const char* filename, char* resolved_path, size_t path_size) {
    if (base_dir == NULL || filename == NULL || resolved_path == NULL) {
        return 0;
    }

    /* Security: Build and normalize the full path */
    char temp_path[PATH_MAX];
    int result = snprintf(temp_path, sizeof(temp_path), "%s/%s", base_dir, filename);
    if (result < 0 || result >= (int) sizeof(temp_path)) {
        return 0;
    }

    /* Security: Resolve to canonical path */
    char* real = realpath(temp_path, resolved_path);
    if (real == NULL) {
        /* If file doesn't exist, resolve parent and append filename */
        char parent[PATH_MAX];
        result = snprintf(parent, sizeof(parent), "%s", base_dir);
        if (result < 0 || result >= (int) sizeof(parent)) {
            return 0;
        }

        real = realpath(parent, resolved_path);
        if (real == NULL) {
            return 0;
        }

        size_t len = strlen(resolved_path);
        result = snprintf(resolved_path + len, path_size - len, "/%s", filename);
        if (result < 0 || result >= (int) (path_size - len)) {
            return 0;
        }
    }

    /* Security: Verify resolved path starts with base directory */
    char base_real[PATH_MAX];
    if (realpath(base_dir, base_real) == NULL) {
        return 0;
    }

    if (strncmp(resolved_path, base_real, strlen(base_real)) != 0) {
        return 0;
    }

    return 1;
}
