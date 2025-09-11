// task40.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updateUser(const char* username, const char* email, const char* csrfToken) {
    if (strcmp(csrfToken, "your_csrf_token_here") != 0) {
        printf("CSRF token mismatch\n");
        return;
    }
    // Update user logic here
    printf("Username: %s, Email: %s\n", username, email);
}

int main() {
    char username[100];
    char email[100];
    char csrfToken[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter CSRF token: ");
    fgets(csrfToken, sizeof(csrfToken), stdin);
    csrfToken[strcspn(csrfToken, "\n")] = 0;

    updateUser(username, email, csrfToken);

    return 0;
}