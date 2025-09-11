#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    printf("Enter a command: ");
    fgets(command, sizeof(command), stdin);
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "An error occurred.\n");
    }
    return 0;
}