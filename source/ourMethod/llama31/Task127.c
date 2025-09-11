#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void copyFileToTempLocation(const char* filePath) {
    FILE* source = fopen(filePath, "r");
    if (!source) {
        if (errno == ENOENT) {
            fprintf(stderr, "File not found: %s\n", filePath);
        } else if (errno == EACCES) {
            fprintf(stderr, "Permission denied for file: %s\n", filePath);
        } else {
            fprintf(stderr, "Error opening file: %s - %s\n", filePath, strerror(errno));
        }
        return;
    }

    char tempDir[] = "/tmp/temp_XXXXXX";
    mkdtemp(tempDir);
    char targetPath[1024];
    snprintf(targetPath, sizeof(targetPath), "%s/%s", tempDir, strrchr(filePath, '/') + 1);

    FILE* target = fopen(targetPath, "w");
    if (!target) {
        fprintf(stderr, "Error creating temporary file: %s - %s\n", targetPath, strerror(errno));
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, target);
    }

    fclose(source);
    fclose(target);
    printf("File copied to temporary location: %s\n", targetPath);
}

int main() {
    const char* testCases[] = {
        "path/to/existing/file.txt",
        "path/to/non/existent/file.txt",
        "path/to/directory",
        "path/to/file/with/no/permissions"
    };

    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        copyFileToTempLocation(testCases[i]);
    }

    return 0;
}