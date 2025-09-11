
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createPhoneNumber(const int arr[10]) {
    // Input validation
    if (arr == NULL) {
        return NULL;
    }
    
    // Validate each digit
    for (int i = 0; i < 10; i++) {
        if (arr[i] < 0 || arr[i] > 9) {
            return NULL;
        }
    }
    
    // Allocate memory for result string
    char* result = (char*)malloc(15 * sizeof(char)); // 14 chars + null terminator
    if (result == NULL) {
        return NULL;
    }
    
    // Create phone number string
    sprintf(result, "(%d%d%d) %d%d%d-%d%d%d%d", 
            arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], 
            arr[6], arr[7], arr[8], arr[9]);
            
    return result;
}

int main() {
    int test1[] = {1,2,3,4,5,6,7,8,9,0};
    int test2[] = {0,0,0,0,0,0,0,0,0,0};
    int test3[] = {9,9,9,9,9,9,9,9,9,9};
    int test4[] = {1,1,1,2,2,2,3,3,3,3};
    int test5[] = {0,1,2,3,4,5,6,7,8,9};
    
    char* result1 = createPhoneNumber(test1);
    char* result2 = createPhoneNumber(test2);
    char* result3 = createPhoneNumber(test3);
    char* result4 = createPhoneNumber(test4);
    char* result5 = createPhoneNumber(test5);
    
    if (result1) printf("%s\\n", result1); // Should print "(123) 456-7890"
    if (result2) printf("%s\\n", result2); // Should print "(000) 000-0000"
    if (result3) printf("%s\\n", result3); // Should print "(999) 999-9999"
    if (result4) printf("%s\\n", result4); // Should print "(111) 222-3333"
    if (result5) printf("%s\\n", result5); // Should print "(012) 345-6789"
    
    // Free allocated memory
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    
    return 0;
}
