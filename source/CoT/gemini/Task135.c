#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// NOTE: This C example uses a very simplified "session" mechanism. In a 
// real application, use a proper session management library or framework.
typedef struct {
    char token[33]; // Store the token as a string
} Session;

// Simulate session storage (extremely basic - do not use in production)
Session sessions[10]; // Fixed size array for demonstration

// Generates a random token
void generate_csrf_token(char *session_id, char *token_out) {
    int i;
    srand(time(NULL)); // Seed the random number generator
    for (i = 0; i < 32; i++) {
        token_out[i] = 'a' + (rand() % 26); // Generate random lowercase letters
    }
    token_out[32] = '\0'; // Null-terminate the string
    
    // "Store" the token in our simulated session
    for(i=0; i<10; i++){
      if(sessions[i].token[0] == '\0' ){ // Find an empty slot
        strcpy(sessions[i].token, token_out);
        break;
      }
    }
}


// Verifies the provided token against the stored token (very basic)
int verify_csrf_token(char *session_id, char *provided_token) {

    int i;
    for(i=0; i < 10; i++){
        if (strcmp(sessions[i].token, provided_token) == 0) {
             sessions[i].token[0] = '\0'; // Invalidate token (crucial)
            return 1; // Token is valid
        }
    }

    return 0; // Token is invalid or session not found
}


int main() {
    char session_id[10] = "12345";
    char token[33];
    char provided_token[33];


    // Test 1: Generate and verify
    generate_csrf_token(session_id, token);
    strcpy(provided_token, token); // Simulate receiving the token
    printf("Test 1: %d\n", verify_csrf_token(session_id, provided_token));  // Expected: 1

    // Test 2: Invalid token
    strcpy(provided_token, "invalid_token");
    printf("Test 2: %d\n", verify_csrf_token(session_id, provided_token));  // Expected: 0


    // Test 3: No token (session not found - simulated)
    char session_id_new[10] = "67890";
    strcpy(provided_token, "some_token");
    printf("Test 3: %d\n", verify_csrf_token(session_id_new, provided_token));  // Expected: 0


     // Test 4: Replay attack
    char session_id_replay[10] = "abcde";
    generate_csrf_token(session_id_replay, token);
    strcpy(provided_token, token);
    verify_csrf_token(session_id_replay, provided_token); // First valid use
    printf("Test 4: %d\n", verify_csrf_token(session_id_replay, provided_token)); // Second use (invalid) - Expected 0

    // Test 5: Session exists but has no token.
     char session_id_no_token[10] = "fghij";
    // We just don't generate a token for this session ID to simulate the scenario
    printf("Test 5: %d\n", verify_csrf_token(session_id_no_token, provided_token));  // Expected: 0


    return 0;
}