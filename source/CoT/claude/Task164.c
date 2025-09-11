
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 100

char* getLastName(const char* fullName) {
    const char* lastName = strrchr(fullName, ' ');
    return (lastName != NULL) ? (char*)(lastName + 1) : (char*)fullName;
}

int compareNames(const void* a, const void* b) {
    const char* nameA = *(const char**)a;
    const char* nameB = *(const char**)b;
    
    const char* lastNameA = getLastName(nameA);
    const char* lastNameB = getLastName(nameB);
    
    int lenA = strlen(lastNameA);
    int lenB = strlen(lastNameB);
    
    if(lenA != lenB) return lenA - lenB;
    return strcmp(lastNameA, lastNameB);
}

void lastNameLensort(char** names, int size) {
    qsort(names, size, sizeof(char*), compareNames);
}

int main() {
    // Test case 1
    char* test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", 
                     "Nicole Yoder", "Melissa Hoffman"};
    int size1 = sizeof(test1)/sizeof(test1[0]);
    lastNameLensort(test1, size1);
    for(int i = 0; i < size1; i++) printf("%s, ", test1[i]);
    printf("\\n");
    
    // Test case 2
    char* test2[] = {"John Doe", "Jane Smith", "Bob Lee", "Alice Wong"};
    int size2 = sizeof(test2)/sizeof(test2[0]);
    lastNameLensort(test2, size2);
    for(int i = 0; i < size2; i++) printf("%s, ", test2[i]);
    printf("\\n");
    
    // Test case 3
    char* test3[] = {"James Bond", "Mary Gold", "Peter Bond", "Susan Park"};
    int size3 = sizeof(test3)/sizeof(test3[0]);
    lastNameLensort(test3, size3);
    for(int i = 0; i < size3; i++) printf("%s, ", test3[i]);
    printf("\\n");
    
    // Test case 4
    char* test4[] = {"Tom Cruz", "Tim Allen", "Ana Bell", "Bob Chen"};
    int size4 = sizeof(test4)/sizeof(test4[0]);
    lastNameLensort(test4, size4);
    for(int i = 0; i < size4; i++) printf("%s, ", test4[i]);
    printf("\\n");
    
    // Test case 5
    char* test5[] = {"Sarah Connor", "John Smith", "Mary Wilson", 
                     "David Brown", "Lisa Green"};
    int size5 = sizeof(test5)/sizeof(test5[0]);
    lastNameLensort(test5, size5);
    for(int i = 0; i < size5; i++) printf("%s, ", test5[i]);
    printf("\\n");
    
    return 0;
}
