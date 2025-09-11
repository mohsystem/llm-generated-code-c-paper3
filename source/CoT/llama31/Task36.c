#include <stdio.h>
#include <stdlib.h>

void readAndPrintFile(const char* fileName) {
    FILE* filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        printf("File does not exist or cannot be opened.\n");
        return;
    }

    char character;
    while ((character = fgetc(filePtr)) != EOF) {
        printf("%c", character);
    }

    fclose(filePtr);
}

int main() {
    char fileName[100];
    printf("Enter the name of the file: ");
    scanf("%99s", fileName); // Prevent buffer overflow
    readAndPrintFile(fileName);
    return 0;
}