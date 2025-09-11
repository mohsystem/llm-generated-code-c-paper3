#include <stdio.h>
#include <string.h>

int main() {
    const char *resources[] = {"Resource 1", "Resource 2", "Resource 3"};
    int index, n = sizeof(resources) / sizeof(resources[0]);
    printf("Enter a number to access a resource: ");
    scanf("%d", &index);
    if(index >= 0 && index < n) {
        printf("You accessed: %s\n", resources[index]);
    } else {
        printf("Invalid input. No resource found.\n");
    }
    return 0;
}