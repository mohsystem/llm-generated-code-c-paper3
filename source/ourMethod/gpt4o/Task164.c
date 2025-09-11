#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    const char *lastNameA = strrchr(strA, ' ') + 1;
    const char *lastNameB = strrchr(strB, ' ') + 1;

    int lenDiff = strlen(lastNameA) - strlen(lastNameB);
    if (lenDiff != 0) {
        return lenDiff;
    }
    return strcmp(lastNameA, lastNameB);
}

void lastNameLensort(char *names[], int n) {
    qsort(names, n, sizeof(char *), compare);
}

int main() {
    char *test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    char *test2[] = {"John Doe", "Jane Smith", "Emily Davis", "Michael Johnson", "Chris Lee"};
    char *test3[] = {"Anna Bell", "Zoe White", "Olivia Green", "Liam Black", "Emma Gray"};
    char *test4[] = {"Catherine Zeta", "Paul Walker", "John Woo", "Morgan Freeman", "Samuel L Jackson"};
    char *test5[] = {"Alice Wonderland", "Bob Builder", "Charlie Brown", "Donald Duck", "Elon Musk"};

    int size1 = sizeof(test1) / sizeof(test1[0]);
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int size5 = sizeof(test5) / sizeof(test5[0]);

    lastNameLensort(test1, size1);
    lastNameLensort(test2, size2);
    lastNameLensort(test3, size3);
    lastNameLensort(test4, size4);
    lastNameLensort(test5, size5);

    for (int i = 0; i < size1; i++) printf("%s\n", test1[i]);
    for (int i = 0; i < size2; i++) printf("%s\n", test2[i]);
    for (int i = 0; i < size3; i++) printf("%s\n", test3[i]);
    for (int i = 0; i < size4; i++) printf("%s\n", test4[i]);
    for (int i = 0; i < size5; i++) printf("%s\n", test5[i]);

    return 0;
}