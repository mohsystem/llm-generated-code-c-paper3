#include <stdio.h>
#include <stdbool.h>

bool uploadFile(const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (!file) {
        return false;
    }
    
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *fileContent = (char *)malloc(fileSize);
    if (fileContent) {
        fread(fileContent, 1, fileSize, file);
        // Process the file content as needed
        free(fileContent);
    }
    
    fclose(file);
    return fileContent != NULL;
}

int main() {
    printf("%d\n", uploadFile("test1.txt")); // Adjust path as needed
    printf("%d\n", uploadFile("test2.txt"));
    printf("%d\n", uploadFile("test3.txt"));
    printf("%d\n", uploadFile("test4.txt"));
    printf("%d\n", uploadFile("test5.txt"));
    return 0;
}