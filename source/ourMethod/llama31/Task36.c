#include <stdio.h>
#include <stdlib.h>

void read_file(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File does not exist or cannot be read.\n");
        return;
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
    fclose(file);
}

int main() {
    char fileName[256];
    printf("Enter the name of the file: ");
    scanf("%255s", fileName); // Limit input to prevent buffer overflow

    read_file(fileName);
    return 0;
}