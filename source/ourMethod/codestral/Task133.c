#include <stdio.h>
#include <string.h>

char password[50] = "oldPassword";

void resetPassword(char* oldPassword, char* newPassword, char* confirmNewPassword) {
    if (strcmp(newPassword, confirmNewPassword) != 0) {
        printf("New password and confirmation password do not match.\n");
        return;
    }
    if (strcmp(password, oldPassword) != 0) {
        printf("Old password is incorrect.\n");
        return;
    }
    if (strcmp(newPassword, oldPassword) == 0) {
        printf("New password cannot be the same as old password.\n");
        return;
    }
    strcpy(password, newPassword);
    printf("Password reset successful.\n");
}

int main() {
    char oldPassword[50], newPassword[50], confirmNewPassword[50];
    printf("Enter old password: ");
    fgets(oldPassword, 50, stdin);
    oldPassword[strcspn(oldPassword, "\n")] = 0;
    printf("Enter new password: ");
    fgets(newPassword, 50, stdin);
    newPassword[strcspn(newPassword, "\n")] = 0;
    printf("Confirm new password: ");
    fgets(confirmNewPassword, 50, stdin);
    confirmNewPassword[strcspn(confirmNewPassword, "\n")] = 0;
    resetPassword(oldPassword, newPassword, confirmNewPassword);
    return 0;
}