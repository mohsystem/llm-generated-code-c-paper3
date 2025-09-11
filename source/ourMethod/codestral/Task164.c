#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    const char** name1 = (const char**)a;
    const char** name2 = (const char**)b;

    const char* lastName1 = strrchr(*name1, ' ');
    const char* lastName2 = strrchr(*name2, ' ');

    size_t lengthComparison = strlen(lastName1) - strlen(lastName2);
    if (lengthComparison != 0) {
        return lengthComparison;
    } else {
        return strcmp(lastName1, lastName2);
    }
}

void lastNameLensort(char* names[], size_t size) {
    qsort(names, size, sizeof(char*), compare);
}

int main() {
    char* names[] = {
        "Jennifer Figueroa",
        "Heather Mcgee",
        "Amanda Schwartz",
        "Nicole Yoder",
        "Melissa Hoffman"
    };
    size_t size = sizeof(names) / sizeof(names[0]);

    lastNameLensort(names, size);

    for (size_t i = 0; i < size; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}