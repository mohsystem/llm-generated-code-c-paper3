
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* readFileFromArgument(const char* filename) {
    static char errorBuffer[512];
    
    if (filename == NULL || strlen(filename) == 0) {
        strcpy(errorBuffer, "Error: Filename is null or empty");
        return errorBuffer;
    }
    
    // Validate filename format
    if (strlen(filename) > 255) {
        strcpy(errorBuffer, "Error: Invalid filename format");
        return errorBuffer;
    }
    
    // Check if file exists
    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        snprintf(errorBuffer, sizeof(errorBuffer), "Error: File does not exist: %s", filename);
        return errorBuffer;
    }
    
    // Check if it's a regular file
    if (!S_ISREG(buffer.st_mode)) {
        snprintf(errorBuffer, sizeof(errorBuffer), "Error: Path is not a file: %s", filename);
        return errorBuffer;
    }

    // Try to open and read file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        snprintf(errorBuffer, sizeof(errorBuffer), "Error: File is not readable: %s", filename);
        return errorBuffer;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for content
    char* content = (char*)malloc(fileSize + 1);
    if (content == NULL) {
        fclose(file);
        strcpy(errorBuffer, "Error: Memory allocation failed");
        return errorBuffer;
    }

    // Read file content
    size_t bytesRead = fread(content, 1, fileSize, file);
    content[bytesRead] = '\0';
    fclose(file);

    return content;
}


int main() {
    printf("=== Test Case 1: Valid file ===\\n");
    FILE* file1 = fopen("test1.txt", "w");
    if (file1 != NULL) {
        fprintf(file1, "Hello World!\\nThis is a test file.");
        fclose(file1);
        char* result1 = readFileFromArgument("test1.txt");
        printf("%s\\n", result1);
        if (strncmp(result1, "Error:", 6) != 0) {
            free(result1);
        }
    }
    
    printf("\\n=== Test Case 2: Non-existent file ===\\n");
    char* result2 = readFileFromArgument("nonexistent.txt");
    printf("%s\\n", result2);
    
    printf("\\n=== Test Case 3: Null filename ===\\n");
    char* result3 = readFileFromArgument(NULL);
    printf("%s\\n", result3);
    
    printf("\\n=== Test Case 4: Empty filename ===\\n");
    char* result4 = readFileFromArgument("");
    printf("%s\\n", result4);
    
    printf("\\n=== Test Case 5: Another valid file ===\\n");
    FILE* file2 = fopen("test2.txt", "w");
    if (file2 != NULL) {
        fprintf(file2, "Line 1\\nLine 2\\nLine 3");
        fclose(file2);
        char* result5 = readFileFromArgument("test2.txt");
        printf("%s\\n", result5);
        if (strncmp(result5, "Error:", 6) != 0) {
            free(result5);
        }
    }
    
    // Cleanup
    remove("test1.txt");
    remove("test2.txt");
    
    return 0;
}
