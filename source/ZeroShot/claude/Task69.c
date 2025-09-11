
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int delete_file(const char* file_path) {
    if (file_path == NULL || strlen(file_path) == 0) {
        return 0;
    }

    char resolved_path[PATH_MAX];
    if (realpath(file_path, resolved_path) == NULL) {
        return 0;
    }

    // Check if file exists and is accessible
    if (access(resolved_path, F_OK | W_OK) != 0) {
        return 0;
    }

    // Try to delete the file
    return remove(resolved_path) == 0;
}

int main() {
    // Test cases
    const char* test_paths[] = {
        "test1.txt",
        "nonexistent.txt",
        "../test2.txt",
        "",
        "directory/"
    };

    int num_tests = sizeof(test_paths) / sizeof(test_paths[0]);

    for (int i = 0; i < num_tests; i++) {
        int result = delete_file(test_paths[i]);
        printf("Deleting %s: %d\\n", test_paths[i], result);
    }

    return 0;
}
