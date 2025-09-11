#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return "File not found."; // Return a string indicating error
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* content = (char*)malloc(fileSize + 1); // Allocate memory for content
    if (content == NULL) {
        fclose(file);
        return "Memory allocation failed."; // Return a string indicating error
    }

    size_t bytesRead = fread(content, 1, fileSize, file);
    if (bytesRead != fileSize) {
        free(content); // Free allocated memory on error
        fclose(file);
        return "Error reading file."; // Return a string indicating error
    }

    content[fileSize] = '\0'; // Null-terminate the string
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a file path as a command-line argument.\n");
        return 1;
    }

    const char* filePath = argv[1];
    char* content = readFile(filePath);
    
    if (content != NULL && content[0] != '\0') { //Check for valid content before printing.
       printf("%s", content);
       if (content != "File not found." && content != "Memory allocation failed." && content != "Error reading file.") {
           free(content); // Free the dynamically allocated memory only if it was allocated for file content.
       }
    } else {
       fprintf(stderr, "%s\n", content); // Print error messages.
    }

    return 0;
}