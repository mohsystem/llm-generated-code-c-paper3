#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSVC(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening CSV file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",\n");
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, ",\n");
        }
        printf("\n");
    }
    fclose(file);
}

int main() {
    const char* testCases[] = {
        "path/to/test1.csv",
        "path/to/test2.csv",
        "path/to/test3.csv",
        "path/to/test4.csv",
        "path/to/test5.csv"
    };

    for (int i = 0; i < 5; ++i) {
        parseCSVC(testCases[i]);
    }

    return 0;
}