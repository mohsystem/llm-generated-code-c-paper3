#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PAIRS 1024

typedef struct {
    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];
} KeyValuePair;

int compareKeyValue(const void* a, const void* b) {
    KeyValuePair* pairA = (KeyValuePair*)a;
    KeyValuePair* pairB = (KeyValuePair*)b;
    return strcmp(pairA->key, pairB->key);
}

void sortKeyValueFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "File not found: %s\n", fileName);
        return;
    }

    KeyValuePair keyValuePairs[MAX_PAIRS];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* equalsPos = strchr(line, '=');
        if (equalsPos) {
            *equalsPos = '\0';
            strcpy(keyValuePairs[count].key, line);
            strcpy(keyValuePairs[count].value, equalsPos + 1);
            count++;
            if (count >= MAX_PAIRS) break;
        }
    }
    fclose(file);

    // Sort key-value pairs
    qsort(keyValuePairs, count, sizeof(KeyValuePair), compareKeyValue);

    // Print sorted key-value pairs
    for (int i = 0; i < count; i++) {
        printf("%s=%s", keyValuePairs[i].key, keyValuePairs[i].value);
    }
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        sortKeyValueFile(testFiles[i]);
    }
    return 0;
}