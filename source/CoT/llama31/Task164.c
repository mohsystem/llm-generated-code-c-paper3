#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Custom comparator for qsort
int compare(const void* a, const void* b) {
    char* strA = *(char**)a;
    char* strB = *(char**)b;

    // Find the space in each string
    char* aSpace = strchr(strA, ' ');
    char* bSpace = strchr(strB, ' ');

    // Calculate the length of the last names
    int aLen = strlen(strA) - (aSpace - strA) - 1;
    int bLen = strlen(strB) - (bSpace - strB) - 1;

    // Compare lengths first, then alphabetically
    if (aLen == bLen) {
        return strcmp(aSpace + 1, bSpace + 1);
    } else {
        return aLen - bLen;
    }
}

void lastNameLenSort(char** names, int n) {
    // Step-by-step reasoning process
    // 1. Use qsort with the custom comparator

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

    lastNameLenSort(names, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}