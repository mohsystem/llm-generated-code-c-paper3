#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    printf("Enter a bash shell command: ");
    fgets(command, sizeof(command), stdin);
    system(command);
    return 0;
}