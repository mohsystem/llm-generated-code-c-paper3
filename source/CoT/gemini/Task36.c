#include <stdio.h>
#include <stdlib.h>

void printFileContents(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", filePath);
        return;
    }

    char line[256]; // Adjust buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // No need for extra newline since fgets includes it
    }

    fclose(file);
}

int main() {
    char filePath[256]; // Adjust buffer size as needed

    for (int i = 0; i < 5; i++) {
        printf("Enter the file path: ");
        if (scanf("%s", filePath) == 1) {  //Check if input was successfully read.
            printFileContents(filePath);
        } else {
             fprintf(stderr, "Error reading file path.\n");
             return 1; // Indicate an error
        }
    }

    return 0;
}