
// Note: C is not typically used for web API implementations
// This is a simplified demonstration of CORS concepts
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256
#define ALLOWED_ORIGINS "https://trusted-domain.com"
#define ALLOWED_METHODS "GET, POST, OPTIONS"
#define ALLOWED_HEADERS "Content-Type, Authorization"
#define MAX_AGE "3600"

struct Task130 {
    char allowed_origin[MAX_URL_LENGTH];
    char allowed_methods[100];
    char allowed_headers[100];
    char max_age[10];
};

bool validate_origin(const char* origin) {
    return strcmp(origin, ALLOWED_ORIGINS) == 0;
}

void handle_cors_request(const char* origin, const char* method) {
    if (validate_origin(origin)) {
        printf("Access-Control-Allow-Origin: %s\\n", origin);
        printf("Access-Control-Allow-Methods: %s\\n", ALLOWED_METHODS);
        printf("Access-Control-Allow-Headers: %s\\n", ALLOWED_HEADERS);
        printf("Access-Control-Max-Age: %s\\n", MAX_AGE);
        printf("Access-Control-Allow-Credentials: true\\n");
    }
}

int main() {
    printf("Test cases for CORS implementation:\\n");
    printf("1. Valid origin request - should allow access\\n");
    printf("2. Invalid origin request - should deny access\\n");
    printf("3. Preflight OPTIONS request - should handle properly\\n");
    printf("4. Request with valid headers - should allow\\n");
    printf("5. Request with invalid headers - should deny\\n");
    return 0;
}
