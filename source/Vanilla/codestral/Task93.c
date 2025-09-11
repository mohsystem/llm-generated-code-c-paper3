#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementing a Map in C is more complex than in the other languages.
// This is a simplified version that only works with string keys and values.
// It does not handle collisions and does not free the memory it allocates.

typedef struct {
    char* key;
    char* value;
} Entry;

Entry* readAndSortFile(const char* file, int* size) {
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Unable to open file");
        exit(1);
    }

    Entry* entries = malloc(sizeof(Entry) * 100); // Allocate space for 100 entries
    int count = 0;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char* key = strtok(line, "=");
        char* value = strtok(NULL, "\n");

        entries[count].key = strdup(key);
        entries[count].value = strdup(value);
        count++;
    }

    fclose(fp);

    // Sort the entries by key
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(entries[i].key, entries[j].key) > 0) {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    *size = count;
    return entries;
}

int main() {
    const char* file = "path_to_your_file";
    int size;
    Entry* sortedEntries = readAndSortFile(file, &size);

    for (int i = 0; i < size; i++) {
        printf("%s=%s\n", sortedEntries[i].key, sortedEntries[i].value);
    }

    return 0;
}