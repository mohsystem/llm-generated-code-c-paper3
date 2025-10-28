
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

/* Secure base directory for serving images - must be set to a trusted directory */
#define BASE_DIR "./images"
#define MAX_FILE_SIZE (10 * 1024 * 1024) /* 10MB limit */

/* Structure to hold file content and size */
typedef struct {
    unsigned char* data;
    size_t size;
} FileContent;

/* Secure function to read image file */
FileContent* img(const char* fileParam) {
    /* Input validation: reject NULL or empty file parameter */
    if (fileParam == NULL || fileParam[0] == '\0') {
        fprintf(stderr, "Error: File parameter is required\\n");
        return NULL;
    }

    /* Check for null bytes in the path (path injection attempt) */
    if (strlen(fileParam) != strcspn(fileParam, "\\0")) {
        fprintf(stderr, "Error: Invalid characters in file parameter\\n");
        return NULL;
    }

    /* Get the absolute base directory path */
    char baseResolved[PATH_MAX];
    if (realpath(BASE_DIR, baseResolved) == NULL) {
        fprintf(stderr, "Error: Base directory does not exist\\n");
        return NULL;
    }

    /* Construct the requested path */
    char requestedPath[PATH_MAX];
    int ret = snprintf(requestedPath, sizeof(requestedPath), "%s/%s", BASE_DIR, fileParam);
    if (ret < 0 || ret >= (int)sizeof(requestedPath)) {
        fprintf(stderr, "Error: Path too long\\n");
        return NULL;
    }

    /* Normalize and resolve the requested path */
    char resolvedPath[PATH_MAX];
    if (realpath(requestedPath, resolvedPath) == NULL) {
        fprintf(stderr, "Error: File not found\\n");
        return NULL;
    }

    /* Security check: ensure the resolved path is within BASE_DIR */
    /* This prevents directory traversal attacks like ../../../etc/passwd */
    size_t baseDirLen = strlen(baseResolved);
    if (strncmp(resolvedPath, baseResolved, baseDirLen) != 0) {
        fprintf(stderr, "Error: Access denied - path traversal attempt detected\\n");
        return NULL;
    }

    /* Open file descriptor with secure flags - O_NOFOLLOW prevents symlink following */
    int fd = open(resolvedPath, O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (fd < 0) {
        fprintf(stderr, "Error: Failed to open file\\n");
        return NULL;
    }

    /* Validate the opened file descriptor using fstat */
    struct stat fileStat;
    if (fstat(fd, &fileStat) != 0) {
        fprintf(stderr, "Error: Failed to stat file\\n");
        close(fd);
        return NULL;
    }
        /* Validate that it's a regular file (not a directory or symlink) */
        if (!S_ISREG(fileStat.st_mode)) {
            fprintf(stderr, "Error: Access denied - not a regular file\n");
            close(fd);
            return NULL;
        }

    /* Check file size before reading to prevent memory exhaustion */
    if (fileStat.st_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File too large\n");
        close(fd);
        return NULL;
    }

    /* Allocate memory for file content */
    FileContent* content = (FileContent*)malloc(sizeof(FileContent));
    if (content == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        close(fd);
        return NULL;
    }

    content->data = (unsigned char*)malloc(fileStat.st_size);
    if (content->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(content);
        close(fd);
        return NULL;
    }

    /* Read file content securely using the validated file descriptor */
    ssize_t totalRead = 0;
    while (totalRead < fileStat.st_size) {
        ssize_t bytesRead = read(fd, content->data + totalRead,
                                 fileStat.st_size - totalRead);
        if (bytesRead < 0) {
            fprintf(stderr, "Error: Failed to read file\n");
            free(content->data);
            free(content);
            close(fd);
            return NULL;
        }
        if (bytesRead == 0) {
            break; /* EOF */
        }
        totalRead += bytesRead;
    }

    close(fd);
    content->size = totalRead;
    return content;
}

/* Helper function to free FileContent */
void freeFileContent(FileContent* content) {
    if (content != NULL) {
        if (content->data != NULL) {
            free(content->data);
        }
        free(content);
    }
}

int main(void) {

    mkdir(BASE_DIR, 0700);

    printf("Test Case 1: Valid image file\\n");
    {
        /* Create a test file */
        char testPath[PATH_MAX];
        snprintf(testPath, sizeof(testPath), "%s/test1.jpg", BASE_DIR);
        FILE* testFile = fopen(testPath, "wb");
        if (testFile != NULL) {
            unsigned char testData[] = {0xFF, 0xD8, 0xFF, 0xE0};
            fwrite(testData, 1, sizeof(testData), testFile);
            fclose(testFile);
        }
        
        FileContent* result1 = img("test1.jpg");
        if (result1 != NULL) {
            printf("Success: Read %zu bytes\\n", result1->size);
            freeFileContent(result1);
        } else {
            printf("Error: Failed to read file\\n");
        }
    }

    printf("\\nTest Case 2: Path traversal attempt (should fail)\\n");
    {
        FileContent* result2 = img("../../../etc/passwd");
        if (result2 != NULL) {
            printf("Error: Should have been blocked\\n");
            freeFileContent(result2);
        } else {
            printf("Success: Path traversal blocked\\n");
        }
    }

    printf("\\nTest Case 3: NULL file parameter (should fail)\\n");
    {
        FileContent* result3 = img(NULL);
        if (result3 != NULL) {
            printf("Error: Should have been blocked\\n");
            freeFileContent(result3);
        } else {
            printf("Success: NULL parameter blocked\\n");
        }
    }

    printf("\\nTest Case 4: Non-existent file (should fail)\\n");
    {
        FileContent* result4 = img("nonexistent.jpg");
        if (result4 != NULL) {
            printf("Error: Should have failed\\n");
            freeFileContent(result4);
        } else {
            printf("Success: Non-existent file handled\\n");
        }
    }

    printf("\\nTest Case 5: Empty filename (should fail)\\n");
    {
        FileContent* result5 = img("");
        if (result5 != NULL) {
            printf("Error: Should have been blocked\\n");
            freeFileContent(result5);
        } else {
            printf("Success: Empty filename blocked\\n");
        }
    }

    return 0;
}
