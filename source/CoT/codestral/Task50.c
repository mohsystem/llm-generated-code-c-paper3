#include <stdio.h>
#include <stdlib.h>

char* uploadFile(FILE* fileInputStream, const char* fileName) {
    FILE* fileOutputStream = fopen(fileName, "wb");
    if (fileOutputStream == NULL) {
        return "Error opening file.";
    }

    int character;
    while ((character = fgetc(fileInputStream)) != EOF) {
        fputc(character, fileOutputStream);
    }

    fclose(fileInputStream);
    fclose(fileOutputStream);

    return "File uploaded successfully.";
}

int main() {
    // Test case: Replace "test.txt" with the path to your test file
    FILE* testFile = fopen("test.txt", "rb");
    if (testFile == NULL) {
        printf("Error opening test file.");
        return 1;
    }
    printf("%s", uploadFile(testFile, "uploaded_test.txt"));
    return 0;
}