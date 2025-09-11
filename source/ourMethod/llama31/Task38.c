#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    // Get the content length and read the input
    char contentLengthStr[10];
    scanf("%s", contentLengthStr);
    int contentLength = atoi(contentLengthStr);
    char* input = malloc(contentLength + 1);
    scanf("%s", input);
    input[contentLength] = '\0';

    // Parse the input (simplified example)
    char* usernameStart = strstr(input, "username=");
    char* messageStart = strstr(input, "message=");
    if (usernameStart && messageStart) {
        usernameStart += 9; // Skip "username="
        messageStart += 8; // Skip "message="
        char* usernameEnd = strstr(usernameStart, "&");
        char* messageEnd = strstr(messageStart, "&");
        if (usernameEnd && messageEnd) {
            *usernameEnd = '\0';
            *messageEnd = '\0';

            // Sanitize input to prevent XSS
            char* username = usernameStart;
            for (char* p = username; *p; ++p) {
                if (*p == '<') *p = '&';
                else if (*p == '>') *p = '>';
            }
            char* message = messageStart;
            for (char* p = message; *p; ++p) {
                if (*p == '<') *p = '&';
                else if (*p == '>') *p = '>';
            }

            // Output the HTML
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h2>Username: %s</h2>", username);
            printf("<h2>Message: %s</h2>", message);
            printf("</body></html>");
        }
    }

    free(input);
    return 0;
}