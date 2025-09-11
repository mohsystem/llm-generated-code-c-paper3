#include <stdio.h>
#include <string.h>

#define ADMIN_PASSWORD "AdminPassword123"

int isValidPassword(const char* password) {
    return strcmp(ADMIN_PASSWORD, password) == 0;
}

int main() {
    char inputPassword[100];
    printf("Enter the admin password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;

    if (isValidPassword(inputPassword)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }

    return 0;
}