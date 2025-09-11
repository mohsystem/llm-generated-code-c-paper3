#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int main() {
    char result[MAX_LEN] = "";
    char input[MAX_LEN];

    printf("Enter strings to concatenate (enter 'end' to stop):\n");

    while (1) {
        fgets(input, MAX_LEN, stdin);
        input[strcspn(input, "\n")] = 0;  // remove trailing newline
        if (strcmp(input, "end") == 0) {
            break;
        }
        strcat(result, input);
    }

    printf("Concatenated string: %s\n", result);

    return 0;
}