#include <stdio.h>
#include <string.h>

// This is a simplified example. In a real application, use a web framework.
void handle_request(const char *origin) {
    const char *allowed_origins[] = {"https://allowed-origin.com", "http://localhost:8080"};
    int num_allowed_origins = sizeof(allowed_origins) / sizeof(allowed_origins[0]);
    int allowed = 0;

    for (int i = 0; i < num_allowed_origins; i++) {
        if (strcmp(origin, allowed_origins[i]) == 0) {
            allowed = 1;
            break;
        }
    }

    if (allowed) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Access-Control-Allow-Origin: %s\r\n", origin);
        printf("Access-Control-Allow-Methods: GET, POST, PUT, DELETE\r\n");
        printf("Access-Control-Allow-Headers: Content-Type, Authorization\r\n");
        printf("Access-Control-Allow-Credentials: true\r\n");
        printf("Content-Type: application/json\r\n\r\n");
        printf("{\"message\": \"CORS enabled response\"}");
    } else {
        printf("HTTP/1.1 403 Forbidden\r\n");
        printf("Content-Type: application/json\r\n\r\n");
        printf("{\"message\": \"CORS not enabled for this origin\"}");
    }

    printf("\n"); // Extra newline for clarity in output
}

int main() {
    printf("This C example simulates HTTP responses. Use a web framework for real applications.\n");
    printf("Test Cases (Simulate requests with different origins):\n");

    const char *test_origins[] = {
        "https://allowed-origin.com",
        "http://localhost:8080",
        "https://malicious-site.com",
        "" // Simulate null origin
    };

    const char *expected_results[] = {
        "Expected success",
        "Expected success",
        "Expected 403",
        "Expect no CORS headers (simulate null origin)"
    };

    int num_tests = sizeof(test_origins) / sizeof(test_origins[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("Origin: %s (%s)\n", test_origins[i], expected_results[i]);
        handle_request(test_origins[i]);
        printf("\n");
    }

    return 0;
}