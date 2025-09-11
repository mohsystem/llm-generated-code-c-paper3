#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidFileName(const char *fileName) {
    for (int i = 0; fileName[i] != '\0'; i++) {
        if (!(fileName[i] == '-' || fileName[i] == '_' || fileName[i] == '.' || 
              (fileName[i] >= '0' && fileName[i] <= '9') || 
              (fileName[i] >= 'A' && fileName[i] <= 'Z') || 
              (fileName[i] >= 'a' && fileName[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}

char* retrieveFile(const char* fileName) {
    static char content[1024];
    if (!isValidFileName(fileName)) {
        return "Invalid file name.";
    }
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "server_directory/%s", fileName);
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return "File not found.";
    }
    fread(content, 1, sizeof(content) - 1, file);
    fclose(file);
    return content;
}

int main() {
    printf("%s\n", retrieveFile("testfile1.txt")); // Example Test Case 1
    printf("%s\n", retrieveFile("testfile2.txt")); // Example Test Case 2
    printf("%s\n", retrieveFile("../testfile3.txt")); // Example Test Case 3 (Invalid)
    printf("%s\n", retrieveFile("valid-file_name.txt")); // Example Test Case 4
    printf("%s\n", retrieveFile("testfile5.exe")); // Example Test Case 5
    return 0;
}