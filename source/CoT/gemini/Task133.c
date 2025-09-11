#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Note:  This C example uses a less secure random number generation method
// compared to the Java, Python, and C++ examples. For production use,
// a more robust random number generator should be used.

char* resetPassword(const char* username) {
    // Generate a random token (less secure than other examples)
    srand(time(NULL)); // Seed the random number generator

    char token[33]; // 32 characters + null terminator
    for (int i = 0; i < 32; i++) {
        token[i] = 'a' + (rand() % 26); // Generate random lowercase letters
    }
    token[32] = '\0';


    // In a real application, store the token securely (e.g., database)
    // associated with the username and send it to the user via email.
    printf("Reset token for %s: %s\n", username, token);

    char* returned_token = (char*)malloc(strlen(token) + 1); // Allocate memory
    if (returned_token == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); // Handle memory allocation error
    }
    strcpy(returned_token, token); // Copy the token to the allocated memory
    return returned_token; // Return the dynamically allocated token
}


int main() {
    char* token;

    printf("Test 1:\n");
    token = resetPassword("user123");
    free(token); // Free the allocated memory

    printf("\nTest 2:\n");
    token = resetPassword("testuser");
    free(token);

    printf("\nTest 3:\n");
    token = resetPassword("anotherUser");
    free(token);

    printf("\nTest 4:\n");
    token = resetPassword("special_char@user");
    free(token);

    printf("\nTest 5:\n");
    token = resetPassword("12345");
    free(token);



    return 0;
}