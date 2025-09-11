#include <stdio.h>

void redirectPage(int choice) {
    if (choice == 1) {
        printf("Redirecting to page 1\n");
    } else if (choice == 2) {
        printf("Redirecting to page 2\n");
    } else if (choice == 3) {
        printf("Redirecting to page 3\n");
    } else {
        printf("Invalid choice. Redirecting to default page.\n");
    }
}

int main() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    redirectPage(choice);
    return 0;
}