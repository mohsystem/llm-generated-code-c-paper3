#include<stdio.h>
#include<stdlib.h>

int main() {
    int num;
    char buffer[256];
    printf("Enter a number: ");
    fgets(buffer, 256, stdin);
    if(sscanf(buffer, "%d", &num) != 1) {
        printf("Error: Invalid input. Please enter a number.\n");
        return 1;
    }
    printf("You entered: %d\n", num);
    // Perform other operations here
    return 0;
}