#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

void handle_input(const char *input, char *output) {
    char buffer[BUFFER_SIZE + 1];
    memset(buffer, '\0', sizeof(buffer));

    for (int i = 0; i < BUFFER_SIZE && input[i] != '\0'; ++i) {
        buffer[i] = input[i];
    }

    strcpy(output, buffer);
}

int main() {
    char output[BUFFER_SIZE + 1];

    handle_input("Hello", output);
    printf("%s\n", output);

    handle_input("World!", output);
    printf("%s\n", output);

    handle_input("1234567890", output);
    printf("%s\n", output);

    handle_input("More than ten characters", output);
    printf("%s\n", output);

    handle_input("", output);
    printf("%s\n", output);

    return 0;
}