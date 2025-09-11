#include <stdio.h>
#include <stdlib.h>

void displayFileContents(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    FILE *file = popen(command, "r");
    if (file == NULL) {
        fprintf(stderr, "Error occurred while trying to display the file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    int exitCode = pclose(file);
    if (exitCode != 0) {
        fprintf(stderr, "Error occurred while trying to display the file.\n");
    }
}

int main() {
    displayFileContents("example1.txt");
    displayFileContents("example2.txt");
    displayFileContents("example3.txt");
    displayFileContents("example4.txt");
    displayFileContents("example5.txt");
    return 0;
}