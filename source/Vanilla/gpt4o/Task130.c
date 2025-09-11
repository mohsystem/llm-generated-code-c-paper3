#include <stdio.h>
#include <string.h>

void handleRequest(char* response) {
    strcpy(response, "CORS enabled response");
}

int main() {
    char response[50];

    // Test cases
    handleRequest(response);
    printf("%s\n", response); // Test case 1

    handleRequest(response);
    printf("%s\n", response); // Test case 2

    handleRequest(response);
    printf("%s\n", response); // Test case 3

    handleRequest(response);
    printf("%s\n", response); // Test case 4

    handleRequest(response);
    printf("%s\n", response); // Test case 5

    return 0;
}