#include <stdio.h>
#include <string.h>

// Define a safe string copy function to prevent potential buffer overflows
void safe_strcpy(char* dest, const char* src, size_t dest_size) {
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0'; // Ensure null-termination
}


char* createPhoneNumber(int numbers[10]) {
    // Validate input
    for (int i = 0; i < 10; i++) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            return NULL; // Indicate invalid input
        }
    }
    
    char* phoneNumber = (char*)malloc(15 * sizeof(char));  // Allocate memory for the phone number string + null terminator
    if (phoneNumber == NULL) {
        return NULL; // Handle memory allocation failure
    }


    snprintf(phoneNumber, 15, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int test2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int test4[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test5[] = {5, 5, 5, 1, 2, 3, 4, 5, 6, 7};

    char* result;

    result = createPhoneNumber(test1);
    if (result) { printf("%s\n", result); free(result);}

    result = createPhoneNumber(test2);
    if (result) { printf("%s\n", result); free(result);}

    result = createPhoneNumber(test3);
    if (result) { printf("%s\n", result); free(result);}

    result = createPhoneNumber(test4);
    if (result) { printf("%s\n", result); free(result);}
    
    result = createPhoneNumber(test5);
    if (result) { printf("%s\n", result); free(result);}


    return 0;
}