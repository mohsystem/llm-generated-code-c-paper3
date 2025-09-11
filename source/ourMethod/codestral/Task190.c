#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 100

void transpose_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char lines[MAX_WORDS][MAX_LENGTH];
    int i = 0;
    while (fgets(lines[i], MAX_LENGTH, file)) {
        lines[i][strcspn(lines[i], "\n")] = 0;
        i++;
    }
    fclose(file);

    int words = 0;
    char *token = strtok(lines[0], " ");
    while (token != NULL) {
        words++;
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < words; j++) {
        for (int k = 0; k < i; k++) {
            token = strtok(lines[k], " ");
            for (int l = 0; l < j; l++) {
                token = strtok(NULL, " ");
            }
            printf("%s ", token);
        }
        printf("\n");
    }
}

int main() {
    transpose_file("file.txt");
    return 0;
}