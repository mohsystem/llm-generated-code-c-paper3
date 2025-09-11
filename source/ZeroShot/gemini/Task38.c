#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Basic CGI implementation in C

void escapeHtml(char* text) { // Escapes HTML characters in place
    char* p = text;
    char* buffer = malloc(strlen(text) * 6 + 1); // Allocate enough space
    char* bufptr = buffer;

    if (!buffer) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while (*p) {
        switch (*p) {
            case '&':  strcpy(bufptr, "&amp;");  bufptr += 5; break;
            case '<':  strcpy(bufptr, "&lt;");   bufptr += 4; break;
            case '>':  strcpy(bufptr, "&gt;");   bufptr += 4; break;
            case '"':  strcpy(bufptr, "&quot;"); bufptr += 6; break;
            case '\'': strcpy(bufptr, "&#x27;"); bufptr += 6; break;
            default:   *bufptr++ = *p;
        }
        p++;
    }
    *bufptr = '\0';
    strcpy(text, buffer); // Copy back to the original string
    free(buffer);
}


int main() {
    char* queryString = getenv("QUERY_STRING");
    char userInput[1024] = ""; // Make sure this is large enough

    if (queryString) {
        char* inputStart = strstr(queryString, "userInput=");
        if (inputStart) {
            strcpy(userInput, inputStart + 9);
            char* ampersand = strchr(userInput, '&'); // Handle other parameters
            if (ampersand) {
                *ampersand = '\0';
            }
        }
    }

    printf("Content-type: text/html\r\n\r\n");
    printf("<html><head><title>User Input Display</title></head><body>");

    if (strlen(userInput) > 0) {
        escapeHtml(userInput);  // Escape the input
        printf("<p>You entered: %s</p>", userInput);
    }


    printf("<form method=\"get\">");
    printf("<input type=\"text\" name=\"userInput\">");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form></body></html>");


        // Test cases (would typically be handled by a web server with CGI)
    // Example for a simple test:
    // Set QUERY_STRING environment variable (e.g., export QUERY_STRING="userInput=Hello")
    // then run the compiled program.


    return 0;
}