#include <stdio.h>
#include <stdlib.h>

void displayFileContents(const char* filename) {
    // Use system function to execute the system command
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    int result = system(command);

    // Check the result
    if (result != 0) {
        fprintf(stderr, "Error occurred while reading the file.\n");
    }
}

int main() {
    displayFileContents("filename.txt");
    return 0;
}