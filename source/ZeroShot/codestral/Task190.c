#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 100

void transposeFile(const char* fileName) {
    char line[MAX_LINE_LENGTH];
    char* token;
    char* tokens[MAX_TOKENS];
    int numTokens = 0;
    int numLines = 0;

    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            numTokens = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                tokens[numTokens] = token;
                numTokens++;
                token = strtok(NULL, " ");
            }
            for (int i = 0; i < numTokens; i++) {
                if (i >= numLines) {
                    numLines++;
                }
                printf("%s ", tokens[i]);
                if (i == numTokens - 1) {
                    printf("\n");
                }
            }
        }
        fclose(file);
    }
}

int main() {
    transposeFile("file.txt");
    return 0;
}