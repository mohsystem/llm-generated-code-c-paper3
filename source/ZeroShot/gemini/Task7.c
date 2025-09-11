#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simplified representation of client request creation (no actual network communication)
char* createLoginRequest(const char* username, const char* password) {
    char* request = (char*)malloc(strlen("LOGIN ") + strlen(username) + 1 + strlen(password) + 1);
    sprintf(request, "LOGIN %s %s", username, password);
    return request;
}


// Simplified server-side processing (no actual user database)
char* processRequest(const char* request) {

    char* requestCopy = strdup(request); // Create a copy to avoid modifying the original
    char* token = strtok(requestCopy, " ");

    if (token != NULL && strcmp(token, "LOGIN") == 0) {
        char* username = strtok(NULL, " ");
        char* password = strtok(NULL, " ");


         // Hardcoded user database for demonstration
        if (username != NULL && password != NULL) {
            if (strcmp(username, "user1") == 0 && strcmp(password, "password123") == 0) {
                free(requestCopy);
                return strdup("LOGIN_SUCCESS");
            } else if (strcmp(username, "user2") == 0 && strcmp(password, "securepass") == 0) {
                free(requestCopy);
                return strdup("LOGIN_SUCCESS");
            }
        }
    }
    free(requestCopy);
    return strdup("LOGIN_FAILED"); 
}

int main() {
    // Test cases
    char* request1 = createLoginRequest("user1", "password123");
    printf("%s\n", processRequest(request1)); // Expected: LOGIN_SUCCESS
    free(request1);

    char* request2 = createLoginRequest("user2", "wrongpassword");
    printf("%s\n", processRequest(request2)); // Expected: LOGIN_FAILED
    free(request2);


    char* request3 = createLoginRequest("user3", "password123");
    printf("%s\n", processRequest(request3)); // Expected: LOGIN_FAILED
    free(request3);

    char* request4 = createLoginRequest("user1", "");
    printf("%s\n", processRequest(request4)); // Expected: LOGIN_FAILED
    free(request4);

    printf("%s\n", processRequest("INVALID_REQUEST")); // Expected: LOGIN_FAILED

    return 0;
}