#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFileContents(const char* filename) {
    // Validate the filename to prevent path traversal attacks
    if (strstr(filename, "../") != NULL || strstr(filename, "..\\") != NULL ||
        filename[0] == '/' || filename[0] == '\\') {
        printf("Invalid filename. Path traversal attempt detected.\n");
        return;
    }

    // Open the file and read its contents
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    char filename[1024];
    printf("Enter the filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    displayFileContents(filename);

    return 0;
}