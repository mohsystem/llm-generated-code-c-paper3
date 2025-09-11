// C does not have built-in support for creating web applications.
// You would typically use a library or framework like libcurl, libmicrohttpd, or cgi.
// This is a simplified example and does not include session storage or termination.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0) {
        // Here you can create a session for the user.
    }
    return 0;
}