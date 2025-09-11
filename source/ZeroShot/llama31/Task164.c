#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold name and its last name length
typedef struct {
    char name[100];
    int lastNameLen;
} Name;

// Comparison function for qsort
int compare(const void* a, const void* b) {
    Name* na = (Name*)a;
    Name* nb = (Name*)b;
    if (na->lastNameLen == nb->lastNameLen) {
        return strcmp(na->name + strlen(na->name) - na->lastNameLen, nb->name + strlen(nb->name) - nb->lastNameLen);
    } else {
        return na->lastNameLen - nb->lastNameLen;
    }
}

void lastNameLenSort(char** names, int n) {
    Name* sortedNames = (Name*)malloc(n * sizeof(Name));
    for (int i = 0; i < n; i++) {
        strcpy(sortedNames[i].name, names[i]);
        sortedNames[i].lastNameLen = strlen(strrchr(names[i], ' ') + 1);
    }
    qsort(sortedNames, n, sizeof(Name), compare);
    for (int i = 0; i < n; i++) {
        printf("%s\n", sortedNames[i].name);
    }
    free(sortedNames);
}

int main() {
    char* names[] = {
        "Jennifer Figueroa",
        "Heather Mcgee",
        "Amanda Schwartz",
        "Nicole Yoder",
        "Melissa Hoffman"
    };
    int n = sizeof(names) / sizeof(names[0]);
    lastNameLenSort(names, n);
    return 0;
}