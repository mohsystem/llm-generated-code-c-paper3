#include <stdio.h>

void redirectUser(int choice) {
    switch (choice) {
        case 1:
            printf("Redirecting to Page 1\n");
            printf("You are now on Page 1\n");
            break;
        case 2:
            printf("Redirecting to Page 2\n");
            printf("You are now on Page 2\n");
            break;
        case 3:
            printf("Redirecting to Page 3\n");
            printf("You are now on Page 3\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

int main() {
    int choice;
    while (true) {
        printf("Enter your choice (1, 2, or 3):\n");
        if (scanf("%d", &choice) == 1) {
            redirectUser(choice);
            break;
        } else {
            printf("Invalid input. Please enter an integer.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
        }
    }
    return 0;
}