#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFileContents(const char* filename) {
    char command[256];
    sprintf(command, "cat %s", filename);
    system(command);
}

int main() {
    const char* testCases[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        displayFileContents(testCases[i]);
    }

    // Alternatively, to get the filename from the user
    // char filename[256];
    // printf("Enter the filename: ");
    // scanf("%255s", filename);
    // displayFileContents(filename);

    return 0;
}