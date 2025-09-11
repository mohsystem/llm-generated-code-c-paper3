#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[100], newPassword[100], sudoPassword[100];

    printf("Enter the username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter the new password: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = 0; // Remove newline character

    // Prompt for sudo password if needed
    printf("Enter sudo password: ");
    fgets(sudoPassword, sizeof(sudoPassword), stdin);
    sudoPassword[strcspn(sudoPassword, "\n")] = 0; // Remove newline character

    // Construct the command to change the password with elevated privileges
    char command[200];
    sprintf(command, "sudo passwd %s", username);

    // Create a temporary file to store the password
    FILE* tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        fprintf(stderr, "Failed to open temporary file\n");
        return 1;
    }
    fprintf(tempFile, "%s\n%s\n%s\n", sudoPassword, newPassword, newPassword);
    fclose(tempFile);

    // Execute the command using the temporary file
    char fullCommand[250];
    sprintf(fullCommand, "%s < temp.txt", command);
    if (system(fullCommand) != 0) {
        fprintf(stderr, "Error changing password\n");
        return 1;
    }

    // Remove the temporary file
    remove("temp.txt");

    printf("Privileges dropped.\n");

    return 0;
}