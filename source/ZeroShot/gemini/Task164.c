#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_last_names(const void *a, const void *b) {
    char *name1 = *(char **)a;
    char *name2 = *(char **)b;

    char *last1 = strrchr(name1, ' ') + 1;
    char *last2 = strrchr(name2, ' ') + 1;

    int len1 = strlen(last1);
    int len2 = strlen(last2);

    if (len1 != len2) {
        return len1 - len2;
    } else {
        return strcmp(last1, last2);
    }
}

void lastNameLensort(char **names, int size) {
    qsort(names, size, sizeof(char *), compare_last_names);
}

int main() {
    char *test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    lastNameLensort(test1, size1);
    for (int i = 0; i < size1; i++) {
        printf("%s ", test1[i]);
    }
    printf("\n");

        char *test2[] = {"Kate Winslet", "Leonardo Dicaprio"};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    lastNameLensort(test2, size2);
    for (int i = 0; i < size2; i++) {
        printf("%s ", test2[i]);
    }
    printf("\n");

        char *test3[] = {"Wayne Rooney", "Cristiano Ronaldo"};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    lastNameLensort(test3, size3);
    for (int i = 0; i < size3; i++) {
        printf("%s ", test3[i]);
    }
    printf("\n");

        char *test4[] = {"Bruce Willis", "Bruce Lee"};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    lastNameLensort(test4, size4);
    for (int i = 0; i < size4; i++) {
        printf("%s ", test4[i]);
    }
    printf("\n");

    char *test5[] = {};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    lastNameLensort(test5, size5);
    for (int i = 0; i < size5; i++) {
        printf("%s ", test5[i]);
    }
    printf("\n");


    return 0;
}