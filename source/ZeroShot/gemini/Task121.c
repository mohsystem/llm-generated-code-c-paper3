#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <dirent.h> // For directory operations

#define UPLOAD_DIRECTORY "uploads"

// Function to create directory if it doesn't exist
int createDirectory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0700) != 0) { // Create with permissions 700 (owner can read, write, execute)
            perror("mkdir failed");
            return -1;
        }
    }
    return 0;
}


char* uploadFile(FILE *fileInputStream, const char *fileName) {
    if (createDirectory(UPLOAD_DIRECTORY) == -1) {
         return strdup("Error creating directory."); // Allocate memory for the error message
    }

    char filePath[256]; // Increased buffer size for safety
    snprintf(filePath, sizeof(filePath), "%s/%s", UPLOAD_DIRECTORY, fileName);


    // Check for path traversal vulnerabilities (basic check)
    if (strstr(filePath, "..") != NULL) {
        return strdup("Invalid file path (potential path traversal).");
    }


    FILE *outputStream = fopen(filePath, "wb");
    if (outputStream == NULL) {
        return strdup("Could not open file for writing.");
    }

    char buffer[8192];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileInputStream)) > 0) {
        fwrite(buffer, 1, bytesRead, outputStream);
    }

    fclose(outputStream);

    // Calculate checksum
    unsigned char checksum[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    outputStream = fopen(filePath, "rb");
    if (outputStream == NULL) {
        return strdup("Could not open file for checksum calculation.");
    }

     while ((bytesRead = fread(buffer, 1, sizeof(buffer), outputStream)) > 0) {
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(checksum, &sha256);
    fclose(outputStream);


    char hexChecksum[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hexChecksum[i * 2], "%02x", checksum[i]);
    }


    char* result = (char*)malloc(strlen("File uploaded successfully. Checksum: ") + strlen(hexChecksum) + 1); // Allocate sufficient memory
    sprintf(result, "File uploaded successfully. Checksum: %s", hexChecksum);


    return result;

}

int main() {
    char *test_data[] = {"Test data 1", "Test data 2", "Test data 3", "Test data 4", "Test data 5"};
    char *file_names[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};

    for (int i = 0; i < 5; i++) {
        FILE *inputStream = fmemopen(test_data[i], strlen(test_data[i]), "r"); // Open in-memory stream
        char *result = uploadFile(inputStream, file_names[i]);
        printf("%s\n", result);
        free(result); // Free the allocated memory
        fclose(inputStream);
    }

    return 0;
}