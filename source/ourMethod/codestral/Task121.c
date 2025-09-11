#include <stdio.h>

void uploadFile(FILE* fileStream, const char* filePath) {
    FILE* outFile = fopen(filePath, "wb");
    int ch;
    while ((ch = fgetc(fileStream)) != EOF) {
        fputc(ch, outFile);
    }
    fclose(outFile);
}

// Test case
int main() {
    FILE* fileStream = fopen("test.txt", "rb");
    uploadFile(fileStream, "test_copy.txt");
    fclose(fileStream);
    return 0;
}