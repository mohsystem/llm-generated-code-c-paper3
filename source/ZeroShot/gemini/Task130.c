#include <stdio.h>
#include <string.h>

// Note: This C example demonstrates the CORS logic. 
//  A full web server implementation is beyond the scope of this example.
//  You would need to use a web framework/library to integrate this into a real server.


//  Simplified representation of handling a request and checking the origin header.
void handle_request(const char* origin) {
    if (origin != NULL && (strcmp(origin, "https://allowed-origin.com") == 0 || strcmp(origin, "http://localhost:8080") == 0)) {

        printf("Access-Control-Allow-Origin: %s\n", origin);
        printf("Access-Control-Allow-Methods: GET, POST, OPTIONS\n");
        printf("Access-Control-Allow-Headers: Content-Type, Authorization\n");
        printf("Access-Control-Max-Age: 3600\n\n");
        printf("{\"message\": \"API response\"}");


    } else {
        printf("HTTP/1.1 403 Forbidden\n\n");
        printf("{\"error\": \"CORS not allowed\"}");
    }

    printf("\n");
}


int main() {
    // Test cases (Illustrative - requires a web server setup)
    const char* origins[] = {
        "https://allowed-origin.com",
        "https://disallowed-origin.com",
        "http://localhost:8080",
        NULL // No origin
    };
    int numOrigins = sizeof(origins) / sizeof(origins[0]);

    for (int i = 0; i < numOrigins; i++) {
        printf("Test Case: Origin = %s\n", origins[i] ? origins[i] : "NULL");
        handle_request(origins[i]);
        printf("\n");
    }


    return 0;

}