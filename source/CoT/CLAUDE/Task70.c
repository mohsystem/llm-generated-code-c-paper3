
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024)  // 10MB limit
#define BUFFER_SIZE 4096

char* readFileContent(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        char* error = (char*)malloc(100);
        strcpy(error, "Error: File path cannot be null or empty");
        return error;
    }
    
    // Check if file exists and get file size
    struct stat fileStat;
    if (stat(filePath, &fileStat) != 0) {
        char* error = (char*)malloc(256);
        snprintf(error, 256, "Error: File does not exist or cannot be accessed: %s", filePath);
        return error;
    }
    
    // Check if it's a regular file
    if (!S_ISREG(fileStat.st_mode)) {
        char* error = (char*)malloc(256);
        snprintf(error, 256, "Error: Path is not a regular file: %s", filePath);
        return error;
    }

    // Check file size to prevent memory exhaustion
    if (fileStat.st_size > MAX_FILE_SIZE) {
        char* error = (char*)malloc(100);
        strcpy(error, "Error: File size exceeds maximum allowed size (10MB)");
        return error;
    }

    // Open file for reading
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        char* error = (char*)malloc(256);
        snprintf(error, 256, "Error: Unable to open file: %s", filePath);
        return error;
    }

    // Allocate memory for file content
    char* content = (char*)malloc(fileStat.st_size + 1);
    if (content == NULL) {
        fclose(file);
        char* error = (char*)malloc(100);
        strcpy(error, "Error: Memory allocation failed");
        return error;
    }

    // Read file content
    size_t bytesRead = fread(content, 1, fileStat.st_size, file);
    content[bytesRead] = '\0';

    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\\n", argv[0]);
        printf("\\nRunning test cases...\\n\\n");
        
        // Test case 1: Valid file
        printf("Test 1 - Valid file:\\n");
        FILE* f1 = fopen("test1_temp.txt", "w");
        fprintf(f1, "Hello, World!");
        fclose(f1);
        char* result1 = readFileContent("test1_temp.txt");
        printf("%s\\n", result1);
        free(result1);
        remove("test1_temp.txt");
        
        // Test case 2: Non-existent file
        printf("\\nTest 2 - Non-existent file:\\n");
        char* result2 = readFileContent("/nonexistent/file.txt");
        printf("%s\\n", result2);
        free(result2);
        
        // Test case 3: Null path
        printf("\\nTest 3 - Null path:\\n");
        char* result3 = readFileContent(NULL);
        printf("%s\\n", result3);
        free(result3);
        
        // Test case 4: Empty path
        printf("\\nTest 4 - Empty path:\\n");
        char* result4 = readFileContent("");
        printf("%s\\n", result4);
        free(result4);
        
        // Test case 5: File with special characters
        printf("\\nTest 5 - File with special characters:\\n");
        FILE* f5 = fopen("test5_temp.txt", "w");
        fprintf(f5, "Content with special chars: @#$%%^&*()");
        fclose(f5);
        char* result5 = readFileContent("test5_temp.txt");
        printf("%s\\n", result5);
        free(result5);
        remove("test5_temp.txt");
        
    } else {
        const char* filePath = argv[1];
        char* content = readFileContent(filePath);
        printf("%s\\n", content);
        free(content);
    }
    
    return 0;
}
