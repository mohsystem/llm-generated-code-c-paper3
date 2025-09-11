
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 100

// Helper function to get last name
void getLastName(const char* fullName, char* lastName) {
    const char* space = strrchr(fullName, ' ');
    if (space != NULL) {
        strcpy(lastName, space + 1);
    } else {
        strcpy(lastName, fullName);
    }
}

// Comparison function for qsort
int compare(const void* a, const void* b) {
    char lastNameA[MAX_NAME_LENGTH];
    char lastNameB[MAX_NAME_LENGTH];
    
    getLastName(*(const char**)a, lastNameA);
    getLastName(*(const char**)b, lastNameB);
    
    int lenDiff = strlen(lastNameA) - strlen(lastNameB);
    if (lenDiff != 0) {
        return lenDiff;
    }
    return strcmp(lastNameA, lastNameB);
}

void lastNameLensort(char** names, int size) {
    qsort(names, size, sizeof(char*), compare);
}

int main() {
    // Test case 1
    char* test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", 
                     "Nicole Yoder", "Melissa Hoffman"};
    int size1 = 5;
    lastNameLensort(test1, size1);
    printf("Test 1 result:\\n");
    for(int i = 0; i < size1; i++) {
        printf("%s\\n", test1[i]);
    }

    // Test case 2
    char* test2[] = {"John Doe", "Jane Smith", "Bob Lee"};
    int size2 = 3;
    lastNameLensort(test2, size2);
    printf("\\nTest 2 result:\\n");
    for(int i = 0; i < size2; i++) {
        printf("%s\\n", test2[i]);
    }

    // Test case 3
    char* test3[] = {"Alice Johnson", "Bob Wilson", "Carol Wilson"};
    int size3 = 3;
    lastNameLensort(test3, size3);
    printf("\\nTest 3 result:\\n");
    for(int i = 0; i < size3; i++) {
        printf("%s\\n", test3[i]);
    }

    // Test case 4
    char* test4[] = {"David Kim", "Paul Lee", "Mark Wu"};
    int size4 = 3;
    lastNameLensort(test4, size4);
    printf("\\nTest 4 result:\\n");
    for(int i = 0; i < size4; i++) {
        printf("%s\\n", test4[i]);
    }

    // Test case 5
    char* test5[] = {"Sarah Connor", "John Smith", "Mary Smith"};
    int size5 = 3;
    lastNameLensort(test5, size5);
    printf("\\nTest 5 result:\\n");
    for(int i = 0; i < size5; i++) {
        printf("%s\\n", test5[i]);
    }

    return 0;
}
