#include <stdio.h>
#include <stdlib.h>

void testCases();

const char* readAndWriteFile(const char* inputFile, const char* tempFile) {
    FILE *inFile = fopen(inputFile, "rb");
    FILE *outFile = fopen(tempFile, "wb");
    if (inFile == NULL || outFile == NULL) {
        if (inFile) fclose(inFile);
        if (outFile) fclose(outFile);
        return "An error occurred: File cannot be opened.";
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outFile);
    }

    fclose(inFile);
    fclose(outFile);
    return "File processed successfully.";
}

int main() {
    testCases();
    return 0;
}

void testCases() {
    // Assuming the files exist for testing
    printf("%s\n", readAndWriteFile("input1.txt", "temp1.txt"));
    printf("%s\n", readAndWriteFile("input2.txt", "temp2.txt"));
    printf("%s\n", readAndWriteFile("input3.txt", "temp3.txt"));
    printf("%s\n", readAndWriteFile("input4.txt", "temp4.txt"));
    printf("%s\n", readAndWriteFile("input5.txt", "temp5.txt"));
}