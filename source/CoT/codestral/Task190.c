#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1024
#define MAX_WORDS_PER_LINE 1024

void transposeFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    char* lines[MAX_LINES];
    char* words[MAX_LINES][MAX_WORDS_PER_LINE];
    int lineCount = 0, wordCount = 0;

    while (fgets(lines[lineCount] = (char*)malloc(MAX_LINE_LENGTH), MAX_LINE_LENGTH, file)) {
        lines[lineCount][strlen(lines[lineCount]) - 1] = '\0';
        wordCount = 0;
        char* word = strtok(lines[lineCount], " ");
        while (word != NULL) {
            words[lineCount][wordCount++] = word;
            word = strtok(NULL, " ");
        }
        lineCount++;
    }
    fclose(file);

    for (int i = 0; i < wordCount; i++) {
        for (int j = 0; j < lineCount; j++) {
            printf("%s ", words[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
}

int main() {
    transposeFile("file.txt");
    return 0;
}