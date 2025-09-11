#include <stdio.h>
#include <stdlib.h>

void redirect(int choice) {
    switch (choice) {
        case 1:
            printf("Redirecting to Page 1\n");
            // Code to redirect to Page 1
            break;
        case 2:
            printf("Redirecting to Page 2\n");
            // Code to redirect to Page 2
            break;
        case 3:
            printf("Redirecting to Page 3\n");
            // Code to redirect to Page 3
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

int main() {
    int choice;
    printf("Enter your choice (1, 2, 3): ");
    scanf("%d", &choice);
    redirect(choice);
    return 0;
}