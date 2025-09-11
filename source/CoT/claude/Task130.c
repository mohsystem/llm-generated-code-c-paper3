
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ORIGINS 2
#define MAX_URL_LENGTH 100

struct Task130 {
    char allowed_origins[MAX_ORIGINS][MAX_URL_LENGTH];
};

bool isValidOrigin(struct Task130* cors, const char* origin) {
    if (origin == NULL) return false;
    
    // Check against allowed origins
    for (int i = 0; i < MAX_ORIGINS; i++) {
        if (strcmp(cors->allowed_origins[i], origin) == 0) {
            return true;
        }
    }
    return false;
}

void initCors(struct Task130* cors) {
    strcpy(cors->allowed_origins[0], "https://trusted-domain.com");
    strcpy(cors->allowed_origins[1], "https://another-trusted.com");
}

void setCorsHeaders(struct Task130* cors, const char* origin, char* response) {
    if (isValidOrigin(cors, origin)) {
        sprintf(response + strlen(response), 
                "Access-Control-Allow-Origin: %s\\n"
                "Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS\\n"
                "Access-Control-Allow-Headers: Content-Type,Authorization\\n"
                "Access-Control-Allow-Credentials: true\\n"
                "Access-Control-Max-Age: 3600\\n",
                origin);
    }
}

int main() {
    struct Task130 cors;
    initCors(&cors);
    
    // Test case 1: Valid origin
    printf("Test 1: %d\\n", isValidOrigin(&cors, "https://trusted-domain.com"));
    
    // Test case 2: Invalid origin
    printf("Test 2: %d\\n", isValidOrigin(&cors, "https://malicious-site.com"));
    
    // Test case 3: Null origin
    printf("Test 3: %d\\n", isValidOrigin(&cors, NULL));
    
    // Test case 4: Empty origin
    printf("Test 4: %d\\n", isValidOrigin(&cors, ""));
    
    // Test case 5: Another valid origin
    printf("Test 5: %d\\n", isValidOrigin(&cors, "https://another-trusted.com"));
    
    return 0;
}
