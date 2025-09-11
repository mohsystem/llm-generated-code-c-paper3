#include <stdio.h>
#include <string.h>

const char* resetPassword(const char* username, const char* oldPassword, const char* newPassword) {
    // This is a mock function; in a real scenario, it would interact with a database
    if (strcmp(oldPassword, "oldPass") == 0) {
        return "Password reset successful for user";
    } else {
        return "Password reset failed for user";
    }
}

int main() {
    printf("%s: %s\n", resetPassword("user1", "oldPass", "newPass1"), "user1");
    printf("%s: %s\n", resetPassword("user2", "wrongPass", "newPass2"), "user2");
    printf("%s: %s\n", resetPassword("user3", "oldPass", "newPass3"), "user3");
    printf("%s: %s\n", resetPassword("user4", "oldPass", "newPass4"), "user4");
    printf("%s: %s\n", resetPassword("user5", "wrongPass", "newPass5"), "user5");
    return 0;
}