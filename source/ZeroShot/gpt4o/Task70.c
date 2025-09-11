#include <stdio.h>
#include <stdlib.h>

void readFile(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide a file path as an argument.\n");
        return 1;
    }
    readFile(argv[1]);
    return 0;
}