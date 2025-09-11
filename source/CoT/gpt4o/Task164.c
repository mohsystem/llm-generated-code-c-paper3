#include <stdio.h>
#include <string.h>

void lastNameLensort(char names[][50], int n) {
    char temp[50];
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            char *lastName1 = strchr(names[i], ' ') + 1;
            char *lastName2 = strchr(names[j], ' ') + 1;
            if (strlen(lastName1) > strlen(lastName2) || 
                (strlen(lastName1) == strlen(lastName2) && strcmp(lastName1, lastName2) > 0)) {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
}

void printNames(char names[][50], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }
}

int main() {
    char test1[][50] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    lastNameLensort(test1, n1);
    printNames(test1, n1);

    char test2[][50] = {"Alice B", "Bob C", "Charlie D"};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    lastNameLensort(test2, n2);
    printNames(test2, n2);

    char test3[][50] = {"Xander Y", "Yasmine Z", "Zane A"};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    lastNameLensort(test3, n3);
    printNames(test3, n3);

    char test4[][50] = {"Anna Banana", "Ben Apple", "Cathy Cherry"};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    lastNameLensort(test4, n4);
    printNames(test4, n4);

    char test5[][50] = {"Henry Ford", "Thomas Edison", "Nikola Tesla"};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    lastNameLensort(test5, n5);
    printNames(test5, n5);

    return 0;
}