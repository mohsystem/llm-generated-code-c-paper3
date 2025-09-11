#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold a name and its last name length
typedef struct {
    char name[100];
    int lastNameLen;
} Name;

// Compare function for qsort
int compare(const void* a, const void* b) {
    Name* n1 = (Name*)a;
    Name* n2 = (Name*)b;

    if (n1->lastNameLen == n2->lastNameLen) {
        return strcmp(n1->name + strlen(n1->name) - n1->lastNameLen, n2->name + strlen(n2->name) - n2->lastNameLen);
    } else {
        return n1->lastNameLen - n2->lastNameLen;
    }
}

void lastNameLenSort(char names[][100], int n) {
    Name* nameArray = (Name*)malloc(n * sizeof(Name));

    for (int i = 0; i < n; i++) {
        strcpy(nameArray[i].name, names[i]);
        nameArray[i].lastNameLen = strlen(names[i]) - strrchr(names[i], ' ') - 1;
    }

    qsort(nameArray, n, sizeof(Name), compare);

    for (int i = 0; i < n; i++) {
        strcpy(names[i], nameArray[i].name);
    }

    free(nameArray);
}

int main() {
    char names[][100] = {
        "Jennifer Figueroa",
        "Heather Mcgee",
        "Amanda Schwartz",
        "Nicole Yoder",
        "Melissa Hoffman"
    };
    int n = sizeof(names) / sizeof(names[0]);

    lastNameLenSort(names, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}