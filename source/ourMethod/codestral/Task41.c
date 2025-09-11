#include <stdio.h>
#include <string.h>

void processString(const char *input) {
    // No buffer overflow risk as we're using a function (printf) that can handle any size of input
    // without buffer overflow and we're not manually managing memory for the string
    printf("Processed string: %s\n", input);
}

int main() {
    processString("Test case 1");
    processString("Test case 2 with longer input");
    // Add more test cases as needed
    return 0;
}