#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define DELIMITER "="

int compare(const void * a, const void * b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    char **data = malloc(sizeof(char *) * MAX_LEN);
    int count = 0;
    char line[MAX_LEN];

    while (fgets(line, MAX_LEN, file)) {
        char *key = strtok(line, DELIMITER);
        char *value = strtok(NULL, DELIMITER);

        if (key != NULL && value != NULL) {
            data[count] = malloc(sizeof(char) * MAX_LEN);
            snprintf(data[count], MAX_LEN, "%s=%s", key, value);
            count++;
        }
    }

    fclose(file);

    qsort(data, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        printf("%s\n", data[i]);
        free(data[i]);
    }

    free(data);

    return 0;
}