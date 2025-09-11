#include <stdio.h>
#include <stdlib.h>

void processFile(const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        fprintf(stderr, "Input file not found: %s\n", inputFile);
        return;
    }

    FILE* output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Error writing to output file: %s\n", outputFile);
        fclose(input);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input)) {
        fputs(line, output);
    }

    fclose(input);
    fclose(output);
}

int main() {
    // Test cases
    const char* inputFiles[] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt"};
    const char* outputFiles[] = {"output1.txt", "output2.txt", "output3.txt", "output4.txt", "output5.txt"};

    for (int i = 0; i < 5; i++) {
        processFile(inputFiles[i], outputFiles[i]);
    }

    return 0;
}