#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Custom comparison function for qsort
int compare(const void* a, const void* b) {
    char** nameA = (char**)a;
    char** nameB = (char**)b;

    size_t aSpace = strrchr(*nameA, ' ') - *nameA;
    size_t bSpace = strrchr(*nameB, ' ') - *nameB;
    size_t aLastNameLength = strlen(*nameA) - aSpace - 1;
    size_t bLastNameLength = strlen(*nameB) - bSpace - 1;

    if (aLastNameLength == bLastNameLength) {
        return strcmp(*nameA + aSpace + 1, *nameB + bSpace + 1);
    } else {
        return (int)aLastNameLength - (int)bLastNameLength;
    }
}

void lastNameLensort(char** names, int n) {
    qsort(names, n, sizeof(char*), compare);
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
    lastNameLensort(names, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}