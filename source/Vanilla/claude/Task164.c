
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 100

char* getLastName(const char* fullName) {
    const char* space = strrchr(fullName, ' ');
    return space ? (char*)(space + 1) : (char*)fullName;
}

int compareNames(const void* a, const void* b) {
    const char* nameA = *(const char**)a;
    const char* nameB = *(const char**)b;
    
    const char* lastNameA = getLastName(nameA);
    const char* lastNameB = getLastName(nameB);
    
    int lenA = strlen(lastNameA);
    int lenB = strlen(lastNameB);
    
    if (lenA != lenB) {
        return lenA - lenB;
    }
    return strcmp(lastNameA, lastNameB);
}

void lastNameLensort(char** names, int size) {
    qsort(names, size, sizeof(char*), compareNames);
}

int main() {
    // Test Case 1
    char* test1[] = {
        "Jennifer Figueroa",
        "Heather Mcgee",
        "Amanda Schwartz",
        "Nicole Yoder",
        "Melissa Hoffman"
    };
    int size1 = 5;
    lastNameLensort(test1, size1);
    printf("Test 1 Result:\\n");
    for(int i = 0; i < size1; i++) {
        printf("%s\\n", test1[i]);
    }

    // Test Case 2
    char* test2[] = {
        "John Doe",
        "Jane Smith",
        "Bob Lee",
        "Alice Wang"
    };
    int size2 = 4;
    lastNameLensort(test2, size2);
    printf("\\nTest 2 Result:\\n");
    for(int i = 0; i < size2; i++) {
        printf("%s\\n", test2[i]);
    }

    // Test Case 3
    char* test3[] = {
        "Peter Parker",
        "Mary Jane",
        "Tony Stark"
    };
    int size3 = 3;
    lastNameLensort(test3, size3);
    printf("\\nTest 3 Result:\\n");
    for(int i = 0; i < size3; i++) {
        printf("%s\\n", test3[i]);
    }

    // Test Case 4
    char* test4[] = {
        "James Bond",
        "John Smith",
        "Jane Smith"
    };
    int size4 = 3;
    lastNameLensort(test4, size4);
    printf("\\nTest 4 Result:\\n");
    for(int i = 0; i < size4; i++) {
        printf("%s\\n", test4[i]);
    }

    // Test Case 5
    char* test5[] = {
        "Single Name"
    };
    int size5 = 1;
    lastNameLensort(test5, size5);
    printf("\\nTest 5 Result:\\n");
    for(int i = 0; i < size5; i++) {
        printf("%s\\n", test5[i]);
    }

    return 0;
}
