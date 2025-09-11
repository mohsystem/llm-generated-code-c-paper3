#include <stdio.h>
#include <string.h>
#include <ctype.h>

void manipulateObject(const char *data, char *result) {
    strcpy(result, "Manipulated: ");
    char *ptr = result + strlen(result);
    while (*data) {
        *ptr++ = toupper(*data++);
    }
    *ptr = '\0';
}

int main() {
    // Test cases
    const char *testCases[] = {"test", "c", "rpc", "example", "code"};
    char result[100];
    for (int i = 0; i < 5; ++i) {
        manipulateObject(testCases[i], result);
        printf("%s\n", result);
    }
    return 0;
}