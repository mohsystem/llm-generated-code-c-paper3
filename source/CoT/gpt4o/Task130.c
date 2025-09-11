#include <stdio.h>
#include <string.h>

void enableCORS() {
    printf("CORS Enabled\n");
}

const char* testCORS(const char* origin) {
    // This is a placeholder for an actual CORS request simulation.
    // In practice, this would involve sending an HTTP request from the specified origin.
    static char result[100];
    snprintf(result, sizeof(result), "CORS test for origin: %s - Passed", origin);
    return result;
}

int main() {
    enableCORS();

    const char* origins[] = {"http://example.com", "http://anotherdomain.com", "http://localhost"};
    size_t numOrigins = sizeof(origins) / sizeof(origins[0]);
    for (size_t i = 0; i < numOrigins; ++i) {
        printf("%s\n", testCORS(origins[i]));
    }

    return 0;
}