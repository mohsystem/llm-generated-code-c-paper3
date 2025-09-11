#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* userInput = getenv("QUERY_STRING");
    if (userInput != NULL) {
        // Simple escaping for demonstration; in real applications, use a proper library
        char* escapedInput = (char*)malloc(strlen(userInput) * 2 + 1);
        char* ptr = escapedInput;
        for (char* c = userInput; *c; ++c) {
            if (*c == '<') *ptr++ = '&', *ptr++ = 'l', *ptr++ = 't', *ptr++ = ';';
            else if (*c == '>') *ptr++ = '&', *ptr++ = 'g', *ptr++ = 't', *ptr++ = ';';
            else if (*c == '&') *ptr++ = '&', *ptr++ = 'a', *ptr++ = 'm', *ptr++ = 'p', *ptr++ = ';';
            else if (*c == '"') *ptr++ = '&', *ptr++ = 'q', *ptr++ = 'u', *ptr++ = 'o', *ptr++ = 't', *ptr++ = ';';
            else if (*c == '\'') *ptr++ = '&#', *ptr++ = 'x', *ptr++ = '2', *ptr++ = '7', *ptr++ = ';';
            else *ptr++ = *c;
        }
        *ptr = '\0';

        printf("Content-type: text/html\r\n\r\n");
        printf("<html><body>User Input: %s</body></html>", escapedInput);
        free(escapedInput);
    } else {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><body>User Input: </body></html>");
    }

    return 0;
}