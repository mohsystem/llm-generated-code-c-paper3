#include <stdio.h>
#include <string.h>

// Similar to C++, a full C implementation requires a web server library 
// (e.g., libmicrohttpd) to handle requests and responses with headers.

// This is a simplified example demonstrating the core concept.
void handle_request(const char *method, const char *path) {
    printf("CORS enabled response\n");

    // In a real server implementation, add these headers to the HTTP response:
    // Access-Control-Allow-Origin: *
    // Access-Control-Allow-Methods: GET, POST, PUT, DELETE
    // Access-Control-Allow-Headers: Content-Type, Authorization
}


int main() {
     // Example usage (simulated requests)
    handle_request("GET", "/api/data");

    // Test cases are similar to the C++ example and require a web server library
    // for true implementation

    return 0;
}