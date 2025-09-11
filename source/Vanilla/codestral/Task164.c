#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    const char** strA = (const char**)a;
    const char** strB = (const char**)b;
    char lastNameA[50], lastNameB[50];
    sscanf(*strA, "%*s %s", lastNameA);
    sscanf(*strB, "%*s %s", lastNameB);
    if (strlen(lastNameA) != strlen(lastNameB)) {
        return strlen(lastNameA) - strlen(lastNameB);
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