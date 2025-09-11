#include <stdio.h>
#include <string.h>

char* resetPassword(const char* currentPassword, const char* newPassword) {
    if (currentPassword == NULL || newPassword == NULL || strlen(currentPassword) == 0 || strlen(newPassword) == 0) {
        return "Error: Passwords cannot be empty.";
    }
    if (strlen(newPassword) < 8) {
        return "Error: New password must be at least 8 characters long.";
    }
    return "Password reset successful.";
}

int main() {
    printf("%s\n", resetPassword("oldPassword", "newPassword123"));
    printf("%s\n", resetPassword("short", "new"));
    printf("%s\n", resetPassword("", "new"));
    printf("%s\n", resetPassword("current", ""));
    printf("%s\n", resetPassword(NULL, "new"));

    return 0;
}