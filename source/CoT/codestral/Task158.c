#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[100];
    printf("Enter data to use in an OS command: ");
    fgets(input, 100, stdin);
    char command[100];
    sprintf(command, "echo %s", input);
    system(command);
    return 0;
}