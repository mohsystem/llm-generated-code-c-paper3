#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* key;
    char* value;
} KeyValue;

// Function to compare two KeyValue structures for sorting
int compare(const void* a, const void* b) {
    KeyValue* pairA = (KeyValue*)a;
    KeyValue* pairB = (KeyValue*)b;
    return strcmp(pairA->key, pairB->key);
}

void readAndSortFile(const char* inputFileName, const char* outputFileName) {
    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening input file: %s\n", inputFileName);
        return;
    }

    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fprintf(stderr, "Error opening output file: %s\n", outputFileName);
        fclose(inputFile);
        return;
    }

    char line[1024];
    List* keyValuePairs = NULL;

    while (fgets(line, sizeof(line), inputFile)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        char* equalsPos = strchr(line, '=');
        if (equalsPos) {
            *equalsPos = '\0'; // Null terminate the key part
            char* key = strdup(line);
            char* value = strdup(equalsPos + 1);

            KeyValue* pair = malloc(sizeof(KeyValue));
            pair->key = key;
            pair->value = value;

            // Add to list
            keyValuePairs = addToList(keyValuePairs, pair);
        } else {
            printf("Ignoring invalid line: %s\n", line);
        }
    }

    fclose(inputFile);

    // Sort the list
    qsort(keyValuePairs, countList(keyValuePairs), sizeof(KeyValue*), compare);

    // Write sorted list to output file
    while (keyValuePairs) {
        KeyValue* pair = keyValuePairs->data;
        fprintf(outputFile, "%s=%s\n", pair->key, pair->value);
        keyValuePairs = keyValuePairs->next;
    }

    fclose(outputFile);
}

// Simple linked list implementation for C
typedef struct List {
    KeyValue* data;
    struct List* next;
} List;

List* addToList(List* list, KeyValue* data) {
    List* newNode = malloc(sizeof(List));
    newNode->data = data;
    newNode->next = list;
    return newNode;
}

int countList(List* list) {
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

int main() {
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";
    readAndSortFile(inputFileName, outputFileName);
    return 0;
}