#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uploadFile(const char* sourceFilePath, const char* destinationFilePath) {
    FILE* sourceFile = fopen(sourceFilePath, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Failed to open source file for reading.\n");
        return;
    }

    FILE* destinationFile = fopen(destinationFilePath, "wb");
    if (destinationFile == NULL) {
        fprintf(stderr, "Failed to open destination file for writing.\n");
        fclose(sourceFile);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, 1024, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File uploaded successfully.\n");
}

int main() {
    char sourceFilePath[256], destinationFilePath[256];
    printf("Enter the source file path: ");
    fgets(sourceFilePath, sizeof(sourceFilePath), stdin);
    sourceFilePath[strcspn(sourceFilePath, "\n")] = 0; // Remove the newline character

    printf("Enter the destination file path: ");
    fgets(destinationFilePath, sizeof(destinationFilePath), stdin);
    destinationFilePath[strcspn(destinationFilePath, "\n")] = 0; // Remove the newline character

    uploadFile(sourceFilePath, destinationFilePath);

    return 0;
}