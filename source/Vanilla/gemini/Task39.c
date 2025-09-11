#include <stdio.h>
#include <stdlib.h>

void displayFileContents(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename); // or "type %s" on Windows


    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Error displaying file contents. Please make sure 'cat' (or 'type' on Windows) is available in your system's PATH.\n");
    }
}

int main() {
    displayFileContents("test1.txt");
    displayFileContents("test2.txt");
    displayFileContents("test3.txt");
    displayFileContents("test4.txt");
    displayFileContents("test5.txt");

    return 0;
}