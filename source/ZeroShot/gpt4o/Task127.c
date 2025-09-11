#include <stdio.h>
#include <stdlib.h>

void handleFileOperation(const char *inputFilePath, const char *outputFilePath) {
    FILE *infile = fopen(inputFilePath, "r");
    FILE *outfile = fopen(outputFilePath, "w");

    if (infile == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", inputFilePath);
        return;
    }
    if (outfile == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", outputFilePath);
        fclose(infile);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        fputs(buffer, outfile);
    }

    fclose(infile);
    fclose(outfile);
}

int main() {
    // Test cases
    handleFileOperation("test1.txt", "output1.txt");
    handleFileOperation("test2.txt", "output2.txt");
    handleFileOperation("nonexistent.txt", "output3.txt");
    handleFileOperation("test4.txt", "output4.txt");
    handleFileOperation("test5.txt", "output5.txt");
    return 0;
}