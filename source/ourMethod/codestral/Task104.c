#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];
    printf("Enter a string: \n");
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline
        printf("You entered: %s\n", buffer);
    } else {
        printf("No input was provided.\n");
    }
    return 0;
}