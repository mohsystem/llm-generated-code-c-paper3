
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_PATH 4096
#define MAX_CONTENT 1048576  // 1MB max file size

struct Task36 {
    char error_message[256];
};

int is_regular_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;
    }
    return S_ISREG(path_stat.st_mode);
}

char* read_file(struct Task36* task, const char* file_path) {
    // Validate file path
    if (file_path == NULL || strlen(file_path) == 0) {
        strncpy(task->error_message, "File path cannot be empty", sizeof(task->error_message) - 1);
        return NULL;
    }
    
    if (strlen(file_path) >= MAX_PATH) {
        strncpy(task->error_message, "File path too long", sizeof(task->error_message) - 1);
        return NULL;
    }

    // Verify file exists and is regular file
    if (!is_regular_file(file_path)) {
        snprintf(task->error_message, sizeof(task->error_message) - 1, 
                "Path is not a regular file or does not exist: %s", file_path);
        return NULL;
    }

    // Open file
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        snprintf(task->error_message, sizeof(task->error_message) - 1,
                "Could not open file: %s", strerror(errno));
        return NULL;
    }

    // Allocate memory for content
    char* content = (char*)malloc(MAX_CONTENT);
    if (content == NULL) {
        fclose(file);
        strncpy(task->error_message, "Memory allocation failed", sizeof(task->error_message) - 1);
        return NULL;
    }
    memset(content, 0, MAX_CONTENT);

    // Read file content
    size_t bytes_read = fread(content, 1, MAX_CONTENT - 1, file);
    if (ferror(file)) {
        free(content);
        fclose(file);
        snprintf(task->error_message, sizeof(task->error_message) - 1,
                "Error reading file: %s", strerror(errno));
        return NULL;
    }

    content[bytes_read] = '\\0';
    fclose(file);
    return content;
}

int main() {
    struct Task36 task;
    const char* test_files[] = {
        "test1.txt",
        "test2.txt",
        "test3.txt",
        "test4.txt",
        "test5.txt"
    };

    // Run test cases
    for (int i = 0; i < 5; i++) {
        printf("\\nReading file: %s\\n", test_files[i]);
        char* content = read_file(&task, test_files[i]);
        if (content != NULL) {
            printf("Content:\\n%s\\n", content);
            free(content);
        } else {
            printf("Error: %s\\n", task.error_message);
        }
    }

    // Interactive mode
    char file_path[MAX_PATH];
    printf("\\nEnter file path to read: ");
    if (fgets(file_path, sizeof(file_path), stdin) != NULL) {
        // Remove trailing newline
        file_path[strcspn(file_path, "\\n")] = 0;
        
        char* content = read_file(&task, file_path);
        if (content != NULL) {
            printf("File contents:\\n%s\\n", content);
            free(content);
        } else {
            printf("Error: %s\\n", task.error_message);
        }
    }

    return 0;
}
