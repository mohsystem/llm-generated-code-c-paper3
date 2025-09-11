#include <stdio.h>
#include <stdlib.h>

void displayFileContents(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    system(command);
}

int main() {
    displayFileContents("file1.txt");
    displayFileContents("file2.txt");
    displayFileContents("file3.txt");
    displayFileContents("file4.txt");
    displayFileContents("file5.txt");
    return 0;
}