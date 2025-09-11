#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char key[256];
    char value[256];
} Record;

int compareRecords(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return strcmp(recordA->key, recordB->key);
}

void readAndSortFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Record records[1000];
    int count = 0;
    char line[512];

    while (fgets(line, sizeof(line), file)) {
        char *pos = strchr(line, '=');
        if (pos) {
            *pos = '\0';
            strncpy(records[count].key, line, sizeof(records[count].key) - 1);
            records[count].key[sizeof(records[count].key) - 1] = '\0';
            strncpy(records[count].value, pos + 1, sizeof(records[count].value) - 1);
            records[count].value[sizeof(records[count].value) - 1] = '\0';
            count++;
        }
    }
    fclose(file);

    qsort(records, count, sizeof(Record), compareRecords);

    printf("Sorted records from %s:\n", filename);
    for (int i = 0; i < count; i++) {
        printf("%s = %s", records[i].key, records[i].value);
    }
}

int main() {
    const char *testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        readAndSortFile(testFiles[i]);
    }
    return 0;
}