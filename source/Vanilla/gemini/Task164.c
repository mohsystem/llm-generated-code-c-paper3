#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort
int compare_names(const void *a, const void *b) {
    char *name1 = *(char **)a;
    char *name2 = *(char **)b;

    char *lastName1 = strrchr(name1, ' ') + 1;
    char *lastName2 = strrchr(name2, ' ') + 1;

    int len1 = strlen(lastName1);
    int len2 = strlen(lastName2);

    if (len1 != len2) {
        return len1 - len2;
    } else {
        return strcmp(lastName1, lastName2);
    }
}


char **lastNameLensort(char **names, int size) {
    qsort(names, size, sizeof(char *), compare_names);
    return names;
}

int main() {
    char *test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    lastNameLensort(test1, size1);
    for (int i = 0; i < size1; i++) {
        printf("%s ", test1[i]);
    }
    printf("\n");


    char *test2[] = {"Kate Winslet", "Leonardo DiCaprio", "Tom Hanks", "Meryl Streep"};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    lastNameLensort(test2, size2);
    for (int i = 0; i < size2; i++) {
        printf("%s ", test2[i]);
    }
    printf("\n");

    char *test3[] = {"Brad Pitt", "Angelina Jolie", "George Clooney", "Julia Roberts"};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    lastNameLensort(test3, size3);
    for (int i = 0; i < size3; i++) {
        printf("%s ", test3[i]);
    }
    printf("\n");

    char *test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    lastNameLensort(test4, size4);
    for (int i = 0; i < size4; i++) {
        printf("%s ", test4[i]);
    }
    printf("\n");

       char *test5[] = {"Single Name"};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    lastNameLensort(test5, size5);
    for (int i = 0; i < size5; i++) {
        printf("%s ", test5[i]);
    }
    printf("\n");


    return 0;
}