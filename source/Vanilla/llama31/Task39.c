#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFileContents(const char* filename) {
    char command[256];
    sprintf(command, "cat %s", filename);
    system(command);
}

int main() {
    // Test cases
    const char* filenames[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        displayFileContents(filenames[i]);
    }
    return 0;
}