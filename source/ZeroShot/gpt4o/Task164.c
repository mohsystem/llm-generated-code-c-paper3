#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char firstName[100];
    char lastName[100];
} Name;

int compareNames(const void *a, const void *b) {
    Name *nameA = (Name *)a;
    Name *nameB = (Name *)b;

    int lenA = strlen(nameA->lastName);
    int lenB = strlen(nameB->lastName);
    
    if (lenA != lenB) {
        return lenA - lenB;
    } else {
        return strcmp(nameA->lastName, nameB->lastName);
    }
}

void lastNameLensort(char names[][200], int count) {
    Name nameArray[count];
    
    for (int i = 0; i < count; i++) {
        sscanf(names[i], "%s %s", nameArray[i].firstName, nameArray[i].lastName);
    }
    
    qsort(nameArray, count, sizeof(Name), compareNames);
    
    for (int i = 0; i < count; i++) {
        printf("%s %s\n", nameArray[i].firstName, nameArray[i].lastName);
    }
}

int main() {
    char names1[][200] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", "Nicole Yoder", "Melissa Hoffman"};
    char names2[][200] = {"John Smith", "Alan Brown", "Robert Green", "Emily Stone", "Ava Carter"};
    char names3[][200] = {"Sarah Connor", "James Cameron", "Tom Cruise", "Chris Pine", "Emma Watson"};
    char names4[][200] = {"Morgan Freeman", "Matt Damon", "Jason Statham", "Brad Pitt", "Will Smith"};
    char names5[][200] = {"Leonardo DiCaprio", "Kate Winslet", "Keanu Reeves", "Sandra Bullock", "Natalie Portman"};
    
    lastNameLensort(names1, 5);
    printf("\n");
    lastNameLensort(names2, 5);
    printf("\n");
    lastNameLensort(names3, 5);
    printf("\n");
    lastNameLensort(names4, 5);
    printf("\n");
    lastNameLensort(names5, 5);
    printf("\n");

    return 0;
}