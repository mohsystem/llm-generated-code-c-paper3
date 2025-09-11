#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "File does not exist or cannot be opened.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./Task65 <filename>\n");
        return 1;
    }

    read_file(argv[1]);

    // Test cases
    const char* testFiles[] = {"test1.txt", "test2.txt", "invalid_file", "non_existent_file", "directory"};
    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\n", testFiles[i]);
        read_file(testFiles[i]);
        printf("\n");
    }

    return 0;
}