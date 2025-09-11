#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* uploadFile(const char* filePath, const char* destinationDir) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        return "File not found or is not a file.";
    }
    
    char* destinationPath = malloc(256);
    sprintf(destinationPath, "%s/%s", destinationDir, strrchr(filePath, '/') + 1);

    FILE* destinationFile = fopen(destinationPath, "w");
    if (!destinationFile) {
        fclose(file);
        free(destinationPath);
        return "Failed to open destination file.";
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes, destinationFile);
    }

    fclose(file);
    fclose(destinationFile);
    sprintf(destinationPath, "File uploaded successfully: %s", destinationPath);
    return destinationPath;
}

int main() {
    const char* testCases[] = {
        "test1.txt", 
        "test2.txt", 
        "test3.txt", 
        "test4.txt", 
        "test5.txt"
    };
    const char* destinationDir = "server/uploads";
    
    for (int i = 0; i < 5; i++) {
        char* message = uploadFile(testCases[i], destinationDir);
        printf("%s\n", message);
        free(message);
    }
    
    return 0;
}