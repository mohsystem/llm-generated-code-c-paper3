#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generateSessionId() {
    char *sessionId = malloc(33 * sizeof(char)); // 32 hex characters + null terminator
    if (sessionId == NULL) {
        return NULL; // Handle memory allocation failure
    }

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < 32; i++) {
        int randomValue = rand() % 16;
        if (randomValue < 10) {
            sessionId[i] = '0' + randomValue;
        } else {
            sessionId[i] = 'a' + (randomValue - 10);
        }
    }
    sessionId[32] = '\0'; // Null-terminate the string

    return sessionId;
}


int main() {
    for (int i = 0; i < 5; i++){
      char* id = generateSessionId();
      if (id != NULL) {
          printf("%s\n", id);
          free(id); // Free the allocated memory
      } else {
          fprintf(stderr, "Memory allocation failed!\n");
      }
    }
    return 0;
}