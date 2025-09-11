#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char **strA = (const char **)a;
    const char **strB = (const char **)b;
    char *lastNameA = strrchr(*strA, ' ');
    char *lastNameB = strrchr(*strB, ' ');
    int lenA = strlen(lastNameA);
    int lenB = strlen(lastNameB);
    if (lenA == lenB) {
        return strcmp(lastNameA, lastNameB);
    }
    return lenA - lenB;
}

void lastNameLensort(char *names[], int n) {
    qsort(names, n, sizeof(char *), compare);
}

int main() {
    char *names[] = {
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