#include <stdio.h>

// Note: C doesn't have decorators or built-in web frameworks// This is a simplified implementation showing the core security logic
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include <limits.h>
#define IMAGES_DIR "images"
#define MAX_FILENAME 256
#define MAX_PATH 4096

int is_valid_filename(const char *filename) {
    regex_t regex;
    int result;
    // Pattern: ^[a-zA-Z0-9_-]+\\.(jpg|jpeg|png|gif|bmp)$

    const char *pattern = "^[a-zA-Z0-9_-]+\\\\.(jpg|jpeg|png|gif|bmp)$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) { return 0; }
    result = regexec(&regex, filename, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

int is_path_safe(const char *filepath) {
    char resolved[MAX_PATH];
    char images_dir[MAX_PATH];
    // Resolve absolute paths
    if (realpath(filepath, resolved) == NULL) { return 0; }
    if (realpath(IMAGES_DIR, images_dir) == NULL) { return 0; }
    // Check if resolved path starts with images directory
    if (strncmp(resolved, images_dir, strlen(images_dir)) != 0) { return 0; }
    return 1;
}

char *img(const char *name) {
    static char result[1024];
    char filepath[MAX_PATH];
    FILE *file;
    struct stat st;
    if (name == NULL || !is_valid_filename(name)) {
        snprintf(result, sizeof(result), "ERROR: Invalid filename");
        return result;
    }
    snprintf(filepath, sizeof(filepath), "%s/%s", IMAGES_DIR, name);
    if (!is_path_safe(filepath)) {
        snprintf(result, sizeof(result), "ERROR: Access denied");
        return result;
    }
    if (stat(filepath, &st) != 0) {
        snprintf(result, sizeof(result), "ERROR: File not found");
        return result;
    }
    file = fopen(filepath, "rb");
    if (file == NULL) {
        snprintf(result, sizeof(result), "ERROR: Cannot open file");
        return result;
    }
    size_t read_size = fread(result, 1, sizeof(result) - 1, file);
    result[read_size] = '\0';


    fclose(file);

    return
            result;
}

void setup_test_environment() {
    mkdir(IMAGES_DIR, 0755);

    FILE *file1 = fopen("images/test1.jpg", "w");
    if (file1) {
        fprintf(file1, "Fake JPG content");
        fclose(file1);
    }

    FILE *file2 = fopen("images/test2.png", "w");
    if (file2) {
        fprintf(file2, "Fake PNG content");
        fclose(file2);
    }
}

int main() {
    setup_test_environment();

    printf("Test Cases:");
    printf("1. Valid JPG: %s", img("test1.jpg"));
    printf("2. Valid PNG: %s", img("test2.png"));
    printf("3. Path traversal attempt: %s", img(".. / etc / passwd"));
    printf("4. Invalid extension: %s", img("test.txt"));
    printf("5. Non-existent file: %s", img("nonexistent.jpg"));

    return 0;
}
