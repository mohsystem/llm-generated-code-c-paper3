#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    const char** sa = (const char**)a;
    const char** sb = (const char**)b;

    char lastNameA[100], lastNameB[100];
    sscanf(*sa, "%*s %s", lastNameA);
    sscanf(*sb, "%*s %s", lastNameB);

    int lengthComparison = strlen(lastNameA) - strlen(lastNameB);
    if (lengthComparison != 0) {
        return lengthComparison;
    } else {
        return strcmp(lastNameA, lastNameB);
    }
}

void lastNameLensort(char* names[], int size) {
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
    int size = sizeof(names) / sizeof(names[0]);

    lastNameLensort(names, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}