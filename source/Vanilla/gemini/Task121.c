#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir on Linux/macOS
#include <sys/types.h> // For mkdir on Linux/macOS
#include <unistd.h> // For access on Linux/macOS

#ifdef _WIN32 // Windows-specific includes
#include <direct.h> // For mkdir on Windows
#include <io.h>     // For access on Windows
#define mkdir _mkdir // Define mkdir for Windows
#define access _access // Define access for Windows
#endif


void uploadFile(const char *sourceFilePath, const char *destinationDirectory) {
    FILE *sourceFile, *destinationFile;
    char destinationFilePath[1024]; // Adjust size if needed

    // Create destination directory if it doesn't exist
    struct stat st = {0};
    if (stat(destinationDirectory, &st) == -1) {
#ifdef _WIN32
        _mkdir(destinationDirectory);
#else
        mkdir(destinationDirectory, 0700); // Create with permissions
#endif
    }

    // Construct destination file path
    snprintf(destinationFilePath, sizeof(destinationFilePath), "%s/%s", destinationDirectory, strrchr(sourceFilePath, '/') ? strrchr(sourceFilePath, '/') + 1 : sourceFilePath);

    sourceFile = fopen(sourceFilePath, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    destinationFile = fopen(destinationFilePath, "wb");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return;
    }

    // Copy file contents
    char buffer[4096]; // Adjust buffer size as needed
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File uploaded successfully to: %s\n", destinationFilePath);
}

int main() {
    // Create dummy files for testing (replace with actual file creation if needed)
    fclose(fopen("test1.txt", "w"));
    fclose(fopen("test2.txt", "w"));
    fclose(fopen("test3.txt", "w"));
    fclose(fopen("test4.txt", "w"));
    fclose(fopen("test5.txt", "w"));


    uploadFile("test1.txt", "uploads");
    uploadFile("test2.txt", "uploads");
    uploadFile("test3.txt", "uploads/subdir");
    uploadFile("test4.txt", "uploads/subdir");
    uploadFile("test5.txt", "newuploads");

    return 0;
}