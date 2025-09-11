// This example is highly simplified and not fully functional.
// In practice, you would use a library like libmicrohttpd.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Simulating a simple HTTP server response
    char* response = "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/plain\r\n"
                     "Access-Control-Allow-Origin: *\r\n"
                     "Access-Control-Allow-Headers: *\r\n"
                     "Access-Control-Allow-Methods: *\r\n"
                     "\r\n"
                     "Hello, World";

    printf("%s", response);
    return 0;
}