#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

void bufferInput(const char *input, char *buffered) {
    if (strlen(input) > BUFFER_SIZE) {
        strncpy(buffered, input, BUFFER_SIZE);
        buffered[BUFFER_SIZE] = '\0';
    } else {
        strcpy(buffered, input);
    }
}

void testBuffer() {
    const char *testCases[] = {"short", "this is too long", "exactlyten", "1234567890", "overload!!!"};
    char buffered[BUFFER_SIZE + 1];

    for (int i = 0; i < 5; ++i) {
        bufferInput(testCases[i], buffered);
        printf("Input: %s => Buffered: %s\n", testCases[i], buffered);
    }
}

int main() {
    testBuffer();
    return 0;
}