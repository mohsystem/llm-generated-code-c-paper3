#include <stdio.h>
#include <string.h>

void lastNameLensort(char names[][100], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            char *lastName1 = strrchr(names[i], ' ') + 1;
            char *lastName2 = strrchr(names[j], ' ') + 1;
            if (strlen(lastName1) > strlen(lastName2) || (strlen(lastName1) == strlen(lastName2) && strcmp(lastName1, lastName2) > 0)) {
                char temp[100];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
}

void printNames(char names[][100], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", names[i]);
    }
}

int main() {
    char test1[][100] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    char test2[][100] = {"Anna Smith", "Bob Brown", "Charlie Davis", "Daniel Evans", "Eva Adams"};
    char test3[][100] = {"Xander Cage", "Bobby Drake", "Aaron Taylor", "Nina Simone", "Olivia Benson"};
    char test4[][100] = {"John Doe", "Jane Roe", "Max Payne", "Clark Kent", "Bruce Wayne"};
    char test5[][100] = {"Michael Jordan", "LeBron James", "Kobe Bryant", "Larry Bird", "Magic Johnson"};

    printf("Test1:\n");
    lastNameLensort(test1, 5);
    printNames(test1, 5);
    
    printf("\nTest2:\n");
    lastNameLensort(test2, 5);
    printNames(test2, 5);

    printf("\nTest3:\n");
    lastNameLensort(test3, 5);
    printNames(test3, 5);

    printf("\nTest4:\n");
    lastNameLensort(test4, 5);
    printNames(test4, 5);

    printf("\nTest5:\n");
    lastNameLensort(test5, 5);
    printNames(test5, 5);

    return 0;
}