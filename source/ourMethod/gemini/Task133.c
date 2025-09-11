#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a secure string copy function to prevent potential buffer overflows
void secure_strcpy(char* dest, const char* src, size_t dest_size) {
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0'; // Ensure null termination
}


char* resetPassword(const char* username, const char* email) {
    // Input validation
    if (!username || strlen(username) == 0 || !email || strlen(email) == 0) {
        char* error_message = (char*)malloc(sizeof(char) * 40);
        secure_strcpy(error_message, "Username and email cannot be empty.", 40);
        return error_message;
    }

    // Simulate user authentication (replace with actual authentication logic)
    if (!isValidUser(username, email)) {
        char* error_message = (char*)malloc(sizeof(char) * 30);
        secure_strcpy(error_message, "Invalid username or email.", 30);
        return error_message;
    }

    // Generate a new random password
    char* newPassword = generateRandomPassword();

    // Simulate updating the password in the database (replace with actual database update logic)
    if (!updatePassword(username, newPassword)) {
        char *error_message = (char *)malloc(sizeof(char) * 25);
        secure_strcpy(error_message, "Password reset failed.", 25);
        return error_message;
    }

    return newPassword;
}

int isValidUser(const char* username, const char* email) {
    // Placeholder for user authentication logic
    if (strcmp(username, "testuser") == 0 && strcmp(email, "test@example.com") == 0) {
        return 1;
    } else if (strcmp(username, "user123") == 0 && strcmp(email, "user123@mail.com") == 0) {
        return 1;
    } else if (strcmp(username, "JaneDoe") == 0 && strcmp(email, "jane.doe@domain.net") == 0) {
        return 1;
    } else if (strcmp(username, "support") == 0 && strcmp(email, "support@company.org") == 0) {
        return 1;
    } else if (strcmp(username, "admin") == 0 && strcmp(email, "admin@system.gov") == 0) {
        return 1;
    }

    return 0;
}

int updatePassword(const char* username, const char* newPassword) {
    // Placeholder for database update logic
    return 1;
}

char* generateRandomPassword() {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+";
    int passwordLength = 12;
    char* password = (char*)malloc(sizeof(char) * (passwordLength + 1)); 

    if (!password) {
        return NULL; // Handle memory allocation failure
    }

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < passwordLength; i++) {
        int index = rand() % (sizeof(characters) -1); // Correct modulo operation
        password[i] = characters[index];
    }
    password[passwordLength] = '\0'; // Null-terminate the string
    return password;
}

int main() {
    printf("Test case 1:\n");
    char *newPassword1 = resetPassword("testuser", "test@example.com");
    printf("%s\n", newPassword1);
    free(newPassword1);

    printf("Test case 2:\n");
    char *newPassword2 = resetPassword("", "");
    printf("%s\n", newPassword2);
    free(newPassword2);


    printf("Test case 3:\n");
    char *newPassword3 = resetPassword("user123", "user123@mail.com");
    printf("%s\n", newPassword3);
    free(newPassword3);

    printf("Test case 4:\n");
    char *newPassword4 = resetPassword("JaneDoe", "jane.doe@domain.net");
    printf("%s\n", newPassword4);
    free(newPassword4);

    printf("Test case 5:\n");
    char *newPassword5 = resetPassword("support", "support@company.org");
    printf("%s\n", newPassword5);
    free(newPassword5);


    return 0;
}