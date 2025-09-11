#include<stdio.h>
#include<string.h>

int main() {
    int size;
    printf("Enter the size of the buffer: ");
    scanf("%d", &size);
    getchar(); // consume newline left-over

    char input[size + 1];
    printf("Enter the string: ");
    fgets(input, size + 1, stdin);

    if (strlen(input) > size) {
        input[size] = '\0';
    }

    printf("The string in the buffer is: %s", input);

    return 0;
}