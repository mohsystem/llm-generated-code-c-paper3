#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *action = getenv("QUERY_STRING");

    if (action != NULL && strcmp(action, "action=create") == 0) {
        // Simulate session creation
        printf("Content-type: text/html\r\n\r\n");
        printf("Session created");
    } else if (action != NULL && strcmp(action, "action=terminate") == 0) {
        // Simulate session termination
        printf("Content-type: text/html\r\n\r\n");
        printf("Session terminated");
    }

    return 0;
}