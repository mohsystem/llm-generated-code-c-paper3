#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValue;

int compare(const void* a, const void* b) {
    KeyValue* kv1 = (KeyValue*)a;
    KeyValue* kv2 = (KeyValue*)b;
    return strcmp(kv1->key, kv2->key);
}

void sortKeyValueFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error reading file: %s\n", fileName);
        return;
    }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    rewind(file);

    KeyValue* keyValueList = malloc(count * sizeof(KeyValue));
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';
            keyValueList[i].key = strdup(line);
            keyValueList[i].value = strdup(equals + 1);
            i++;
        }
    }
    fclose(file);

    qsort(keyValueList, count, sizeof(KeyValue), compare);

    printf("Sorted Key-Value Pairs for %s:\n", fileName);
    for (i = 0; i < count; i++) {
        printf("%s=%s", keyValueList[i].key, keyValueList[i].value);
    }

    // Free allocated memory
    for (i = 0; i < count; i++) {
        free(keyValueList[i].key);
        free(keyValueList[i].value);
    }
    free(keyValueList);
}

int main() {
    const char* testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        sortKeyValueFile(testFiles[i]);
    }
    return 0;
}