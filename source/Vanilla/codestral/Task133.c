#include<stdio.h>
#include<string.h>

void resetPassword(char* currentPassword, char* newPassword, char* confirmNewPassword) {
    if (strcmp(newPassword, confirmNewPassword) == 0) {
        // Implement code to reset password here
        printf("Password reset successful.\n");
    } else {
        printf("New passwords do not match.\n");
    }
}

int main() {
    char currentPassword[] = "oldPass";
    char newPassword[] = "newPass";
    char confirmNewPassword[] = "newPass";

    resetPassword(currentPassword, newPassword, confirmNewPassword);

    char wrongPassword[] = "wrongPass";
    resetPassword(currentPassword, newPassword, wrongPassword);

    return 0;
}