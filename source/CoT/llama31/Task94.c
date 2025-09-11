#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[100];
    char value[100];
} KeyValue;

int compare(const void* a, const void* b) {
    KeyValue* keyA = (KeyValue*)a;
    KeyValue* keyB = (KeyValue*)b;
    return strcmp(keyA->key, keyB->key);
}

void sortKeyValueFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    KeyValue keyValue;
    KeyValue* keyValueList = NULL;
    int listSize = 0;

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* equalsPos = strchr(line, '=');
        if (equalsPos) {
            *equalsPos = '\0';
            strcpy(keyValue.key, line);
            strcpy(keyValue.value, equalsPos + 1);
            keyValueList = realloc(keyValueList, (listSize + 1) * sizeof(KeyValue));
            if (!keyValueList) {
                fprintf(stderr, "Memory allocation failed\n");
                return;
            }
            keyValueList[listSize] = keyValue;
            listSize++;
        } else {
            printf("Skipping invalid line: %s", line);
        }
    }
    fclose(file);

    // Sort the list
    qsort(keyValueList, listSize, sizeof(KeyValue), compare);

    // Write the sorted list to a new file
    char outputFileName[200];
    sprintf(outputFileName, "sorted_%s", fileName);
    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fprintf(stderr, "Error opening output file: %s\n", outputFileName);
        return;
    }

    for (int i = 0; i < listSize; i++) {
        fprintf(outputFile, "%s=%s\n", keyValueList[i].key, keyValueList[i].value);
    }
    fclose(outputFile);

    free(keyValueList);
}

int main() {
    char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        sortKeyValueFile(testFiles[i]);
    }
    return 0;
}