#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include <sys/stat.h>

void uploadFile(const char* fileName, const char* uploadDir) {
    // Check if the file exists
    struct stat buffer;
    if (stat(fileName, &buffer) != 0) {
        printf("File does not exist.\n");
        return;
    }

    // Restrict file types
    const char* allowedExtensions[] = {".jpg", ".pdf", ".txt"};
    if (!isAllowedExtension(fileName, allowedExtensions)) {
        printf("File type not allowed.\n");
        return;
    }

    // Generate a unique file name
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    char uuid[37];
    uuid_unparse(bin_uuid, uuid);
    char newFileName[1024];
    sprintf(newFileName, "%s%s", uuid, getFileExtension(fileName));

    // Store the file outside of the document root
    char uploadPath[1024];
    sprintf(uploadPath, "%s/%s", uploadDir, newFileName);
    if (rename(fileName, uploadPath) != 0) {
        printf("Error uploading file: %s\n", strerror(errno));
    } else {
        printf("File uploaded successfully as %s\n", newFileName);
    }
}

bool isAllowedExtension(const char* fileName, const char* allowedExtensions[]) {
    for (int i = 0; allowedExtensions[i] != NULL; ++i) {
        size_t len = strlen(allowedExtensions[i]);
        if (strncmp(fileName + strlen(fileName) - len, allowedExtensions[i], len) == 0) {
            return true;
        }
    }
    return false;
}

char* getFileExtension(const char* fileName) {
    char* dot = strrchr(fileName, '.');
    if (dot != NULL) {
        return dot;
    }
    return "";
}

int main() {
    const char* testFiles[] = {"test.jpg", "test.pdf", "test.exe", "test.zip", "test.txt"};
    for (int i = 0; i < 5; ++i) {
        uploadFile(testFiles[i], "uploads/");
    }
    return 0;
}