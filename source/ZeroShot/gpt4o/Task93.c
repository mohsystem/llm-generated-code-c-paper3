#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} Record;

int compareRecords(const void *a, const void *b) {
    return strcmp(((Record *)a)->key, ((Record *)b)->key);
}

void readAndSortFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) return;

    Record records[100];
    int count = 0;
    char line[512];

    while (fgets(line, sizeof(line), file) && count < 100) {
        char *pos = strchr(line, '=');
        if (pos) {
            *pos = '\0';
            strcpy(records[count].key, line);
            strcpy(records[count].value, pos + 1);
            records[count].value[strcspn(records[count].value, "\n")] = 0;  // remove newline
            count++;
        }
    }
    fclose(file);

    qsort(records, count, sizeof(Record), compareRecords);

    for (int i = 0; i < count; i++) {
        printf("%s=%s\n", records[i].key, records[i].value);
    }
}

int main() {
    readAndSortFile("test.txt");
    return 0;
}