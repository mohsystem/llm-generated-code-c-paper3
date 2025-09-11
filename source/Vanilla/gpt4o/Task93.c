#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char key[256];
    char value[256];
} Record;

int compareRecords(const void *a, const void *b) {
    return strcmp(((Record *)a)->key, ((Record *)b)->key);
}

void readAndSortFile(const char *filename) {
    Record records[100];
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (file) {
        char line[512];
        while (fgets(line, sizeof(line), file)) {
            char *delimiter = strchr(line, ':');
            if (delimiter) {
                *delimiter = '\0';
                strcpy(records[count].key, line);
                strcpy(records[count].value, delimiter + 1);
                count++;
            }
        }
        fclose(file);

        qsort(records, count, sizeof(Record), compareRecords);

        printf("Sorted records for %s:\n", filename);
        for (int i = 0; i < count; i++) {
            printf("%s: %s", records[i].key, records[i].value);
        }
    }
}

int main() {
    const char *filenames[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};

    for (int i = 0; i < 5; i++) {
        readAndSortFile(filenames[i]);
    }
    return 0;
}