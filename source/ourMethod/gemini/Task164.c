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


void lastNameLensort(char *names[], int count) {
    qsort(names, count, sizeof(char *), compare_names);
}

int main() {
    char *testCase1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    int count1 = sizeof(testCase1) / sizeof(testCase1[0]);
    lastNameLensort(testCase1, count1);
    for (int i = 0; i < count1; i++) {
        printf("%s ", testCase1[i]);
    }
    printf("\n");

     char *testCase2[] = {"Kate Hudson", "Emma Stone", "Jennifer Aniston"};
    int count2 = sizeof(testCase2) / sizeof(testCase2[0]);
    lastNameLensort(testCase2, count2);
    for (int i = 0; i < count2; i++) {
        printf("%s ", testCase2[i]);
    }
    printf("\n");

    char *testCase3[] = {"Sandra Bullock", "Julia Roberts", "Nicole Kidman"};
    int count3 = sizeof(testCase3) / sizeof(testCase3[0]);
    lastNameLensort(testCase3, count3);
    for (int i = 0; i < count3; i++) {
        printf("%s ", testCase3[i]);
    }
    printf("\n");

    char *testCase4[] = {"Scarlett Johansson", "Elizabeth Olsen", "Brie Larson"};
    int count4 = sizeof(testCase4) / sizeof(testCase4[0]);
    lastNameLensort(testCase4, count4);
    for (int i = 0; i < count4; i++) {
        printf("%s ", testCase4[i]);
    }
    printf("\n");

    char *testCase5[] = {"Angelina Jolie", "Jennifer Lawrence", "Meryl Streep"};
    int count5 = sizeof(testCase5) / sizeof(testCase5[0]);
    lastNameLensort(testCase5, count5);
    for (int i = 0; i < count5; i++) {
        printf("%s ", testCase5[i]);
    }
    printf("\n");


    return 0;
}