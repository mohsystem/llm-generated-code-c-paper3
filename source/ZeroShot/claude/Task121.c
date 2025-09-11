
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <errno.h>

#define MAX_PATH 1024
#define BUFFER_SIZE 4096
#define MAX_FILE_SIZE 10485760  // 10MB

// Function to calculate SHA-256 hash of a file
static void calculateFileHash(const char* filename, unsigned char* hash) {
    FILE* file = fopen(filename, "rb");
    if (!file) return;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, file)) != 0) {
        SHA256_Update(&sha256, buffer, bytes);
    }
    
    SHA256_Final(hash, &sha256);
    fclose(file);
}

// Function to create directory if it doesn't exist\nstatic int createDirectory(const char* path) {\n    #ifdef _WIN32\n        return _mkdir(path);\n    #else\n        return mkdir(path, 0777);\n    #endif\n}\n\n// Function to get file size\nstatic long getFileSize(const char* filename) {\n    struct stat st;\n    if (stat(filename, &st) == 0)\n        return st.st_size;\n    return -1;\n}\n\n// Main upload function\nchar* uploadFile(const char* sourcePath, const char* destinationDir) {\n    static char result[MAX_PATH * 2];\n    \n    // Validate input parameters\n    if (!sourcePath || !destinationDir) {\n        snprintf(result, sizeof(result), "Error uploading file: Invalid parameters");\n        return result;\n    }\n\n    // Check if source file exists\n    FILE* sourceFile = fopen(sourcePath, "rb");\n    if (!sourceFile) {\n        snprintf(result, sizeof(result), "Error uploading file: Source file does not exist");\n        return result;\n    }\n    fclose(sourceFile);\n\n    // Check file size\n    long fileSize = getFileSize(sourcePath);\n    if (fileSize > MAX_FILE_SIZE) {\n        snprintf(result, sizeof(result), "Error uploading file: File size exceeds 10MB limit");\n        return result;\n    }\n\n    // Create destination directory\n    createDirectory(destinationDir);\n\n    // Generate unique filename\n    char filename[MAX_PATH];\n    char extension[32] = "";\n    const char* lastDot = strrchr(sourcePath, '.');
    if (lastDot) {
        strncpy(extension, lastDot, sizeof(extension) - 1);
    }
    
    time_t timestamp = time(NULL);
    snprintf(filename, sizeof(filename), "%s/file_%ld%s", 
             destinationDir, timestamp, extension);

    // Copy file
    FILE* source = fopen(sourcePath, "rb");
    FILE* dest = fopen(filename, "wb");
    
    if (!source || !dest) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        snprintf(result, sizeof(result), "Error uploading file: Cannot open files");
        return result;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            fclose(source);
            fclose(dest);
            remove(filename);
            snprintf(result, sizeof(result), "Error uploading file: Write error");
            return result;
        }
    }

    fclose(source);
    fclose(dest);

    // Verify file integrity
    unsigned char sourceHash[SHA256_DIGEST_LENGTH];
    unsigned char destHash[SHA256_DIGEST_LENGTH];
    
    calculateFileHash(sourcePath, sourceHash);
    calculateFileHash(filename, destHash);

    if (memcmp(sourceHash, destHash, SHA256_DIGEST_LENGTH) != 0) {
        remove(filename);
        snprintf(result, sizeof(result), "Error uploading file: Integrity check failed");
        return result;
    }

    snprintf(result, sizeof(result), "File uploaded successfully to: %s", filename);
    return result;
}

int main() {
    // Test cases
    printf("Test Case 1: Upload text file\\n");
    printf("%s\\n", uploadFile("test.txt", "./uploads"));

    printf("\\nTest Case 2: Upload non-existent file\\n");
    printf("%s\\n", uploadFile("nonexistent.txt", "./uploads"));

    printf("\\nTest Case 3: Upload with null paths\\n");
    printf("%s\\n", uploadFile(NULL, NULL));

    printf("\\nTest Case 4: Upload image file\\n");
    printf("%s\\n", uploadFile("test.jpg", "./uploads"));

    printf("\\nTest Case 5: Upload to invalid directory\\n");
    printf("%s\\n", uploadFile("test.txt", "/invalid/path"));

    return 0;
}
