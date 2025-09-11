#include <stdio.h>
#include <stdlib.h>

void display_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file"); // Use perror for better error messages
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

int main() {
    char filename[256]; // Limit filename length to prevent buffer overflow
    printf("Enter filename: ");

    if (fgets(filename, sizeof(filename), stdin) == NULL) {
         perror("Error reading filename");
        return 1;
    }

    // Remove the trailing newline from fgets
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    display_file_contents(filename);

    // Test cases (create dummy files for testing)
        display_file_contents("test1.txt");
        display_file_contents("test2.txt");
        display_file_contents("test3.txt");
        display_file_contents("test4.txt");
        display_file_contents("test5.txt");

    return 0;
}