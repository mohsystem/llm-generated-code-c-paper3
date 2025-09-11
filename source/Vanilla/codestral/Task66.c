// This is a basic outline and does not include validation or error handling.
#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    fgets(command, 100, stdin);
    system(command);
    return 0;
}