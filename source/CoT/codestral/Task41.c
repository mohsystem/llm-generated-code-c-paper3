#include <stdio.h>
#include <ctype.h>
#include <string.h>

void process_string(const char* input, char* output) {
    // Assuming some basic processing of the string for the purpose of this example
    for (int i = 0; input[i]; i++) {
        output[i] = tolower(input[i]);
    }
    output[strlen(input)] = '\0';
}

int main() {
    // Test cases
    char output[6];
    process_string("TEST1", output);
    printf("%s\n", output);
    process_string("TEST2", output);
    printf("%s\n", output);
    process_string("TEST3", output);
    printf("%s\n", output);
    process_string("TEST4", output);
    printf("%s\n", output);
    process_string("TEST5", output);
    printf("%s\n", output);
    return 0;
}