#include <stdio.h>
#include <string.h>

// Function to create the phone number string
char* createPhoneNumber(int numbers[10]) {
    char* phoneNumber = malloc(sizeof(char) * 15);  // Allocate memory for the string
    if (phoneNumber == NULL) {
        return NULL; // Handle memory allocation failure
    }
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int testCases[5][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {0, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 1, 1, 2, 2, 2, 3, 3, 3, 4},
        {5, 5, 5, 6, 6, 6, 7, 7, 7, 8},
        {9, 0, 0, 1, 1, 1, 2, 2, 2, 3}
    };

    for (int i = 0; i < 5; i++) {
        char *phoneNumber = createPhoneNumber(testCases[i]);
        if (phoneNumber != NULL) {
            printf("%s\n", phoneNumber);
            free(phoneNumber); // Free the allocated memory
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}