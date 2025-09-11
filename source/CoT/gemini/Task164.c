#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void lastNameLensort(char *names[], int n) {
    qsort(names, n, sizeof(char *), compare_names);
}


int main() {
    char *test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    lastNameLensort(test1, n1);
    for (int i = 0; i < n1; i++) {
        printf("%s ", test1[i]);
    }
    printf("\n");

    char *test2[] = {"Kate Winslet", "Leonardo DiCaprio"};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    lastNameLensort(test2, n2);
    for (int i = 0; i < n2; i++) {
        printf("%s ", test2[i]);
    }
    printf("\n");

        char *test3[] = {"Bruce Wayne", "Clark Kent", "Diana Prince"};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    lastNameLensort(test3, n3);
    for (int i = 0; i < n3; i++) {
        printf("%s ", test3[i]);
    }
    printf("\n");

        char *test4[] = {"Barack Obama", "Donald Trump", "Joe Biden"};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    lastNameLensort(test4, n4);
    for (int i = 0; i < n4; i++) {
        printf("%s ", test4[i]);
    }
    printf("\n");

        char *test5[] = {"Beyonce Knowles", "Jay-Z", "Solange Knowles"};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    lastNameLensort(test5, n5);
    for (int i = 0; i < n5; i++) {
        printf("%s ", test5[i]);
    }
    printf("\n");



    return 0;
}