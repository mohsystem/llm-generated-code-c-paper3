#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} KeyValuePair;

int compare(const void *a, const void *b) {
    KeyValuePair *pair1 = (KeyValuePair *)a;
    KeyValuePair *pair2 = (KeyValuePair *)b;
    return strcmp(pair1->key, pair2->key);
}

void readAndSortFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    KeyValuePair pairs[256];
    int count = 0;
    char line[512];

    while (fgets(line, sizeof(line), file)) {
        char *pos = strchr(line, '=');
        if (pos) {
            *pos = '\0';
            strncpy(pairs[count].key, line, sizeof(pairs[count].key) - 1);
            strncpy(pairs[count].value, pos + 1, sizeof(pairs[count].value) - 1);
            pairs[count].key[sizeof(pairs[count].key) - 1] = '\0';
            pairs[count].value[sizeof(pairs[count].value) - 1] = '\0';
            count++;
        }
    }
    fclose(file);

    qsort(pairs, count, sizeof(KeyValuePair), compare);

    for (int i = 0; i < count; i++) {
        printf("%s=%s", pairs[i].key, pairs[i].value);
    }
}

int main() {
    const char *testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        printf("Contents of %s:\n", testFiles[i]);
        readAndSortFile(testFiles[i]);
        printf("\n");
    }
    return 0;
}