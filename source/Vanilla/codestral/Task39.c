#include <stdio.h>
#include <stdlib.h>

void displayFileContents(char* filename) {
    char command[100];
    sprintf(command, "type %s", filename);
    system(command);
}

int main() {
    char filename[100];
    printf("Enter the filename: ");
    fgets(filename, sizeof(filename), stdin);
    // Remove newline character from input
    filename[strcspn(filename, "\n")] = 0;
    displayFileContents(filename);
    return 0;
}