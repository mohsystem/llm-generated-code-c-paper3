
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to get last name from full name
char* getLastName(const char* fullName) {
    const char* space = strrchr(fullName, ' ');
    if (space == NULL) return NULL;
    return (char*)(space + 1);
}

// Comparison function for qsort
int compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    
    char* lastName1 = getLastName(str1);
    char* lastName2 = getLastName(str2);
    
    if (lastName1 == NULL || lastName2 == NULL) return 0;
    
    size_t len1 = strlen(lastName1);
    size_t len2 = strlen(lastName2);
    
    if (len1 != len2) {
        return len1 - len2;
    }
    return strcmp(lastName1, lastName2);
}

char** lastNameLensort(char** names, int size) {
    if (names == NULL || size <= 0) {
        return NULL;
    }
    
    qsort(names, size, sizeof(char*), compare);
    return names;
}

int main() {
    // Test case 1
    char* test1[] = {"Jennifer Figueroa", "Heather Mcgee", "Amanda Schwartz", 
                     "Nicole Yoder", "Melissa Hoffman"};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    char** result1 = lastNameLensort(test1, size1);
    for (int i = 0; i < size1; i++) {
        printf("%s\\n", result1[i]);
    }
    printf("\\n");
    
    // Test case 2
    char* test2[] = {"John Doe", "Jane Smith", "Bob Lee"};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    char** result2 = lastNameLensort(test2, size2);
    for (int i = 0; i < size2; i++) {
        printf("%s\\n", result2[i]);
    }
    printf("\\n");
    
    // Test case 3
    char* test3[] = {"Alice Wong", "Peter Wong", "Mary Wong"};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    char** result3 = lastNameLensort(test3, size3);
    for (int i = 0; i < size3; i++) {
        printf("%s\\n", result3[i]);
    }
    printf("\\n");
    
    // Test case 4
    char* test4[] = {"James Wilson"};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    char** result4 = lastNameLensort(test4, size4);
    for (int i = 0; i < size4; i++) {
        printf("%s\\n", result4[i]);
    }
    printf("\\n");
    
    return 0;
}
