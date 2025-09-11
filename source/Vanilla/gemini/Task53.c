#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

// Simplified session management (not thread-safe)
typedef struct {
    char sessionId[37];
    char username[256]; // Adjust size as needed
} Session;

Session sessions[100]; // Adjust size as needed
int sessionCount = 0;


char* createSession(const char* username) {
    if (sessionCount >= 100) {
        return NULL; // Session limit reached
    }

    uuid_t uuid;
    uuid_generate(uuid);
    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);

    strcpy(sessions[sessionCount].sessionId, uuid_str);
    strcpy(sessions[sessionCount].username, username);

    sessionCount++;
    return sessions[sessionCount - 1].sessionId;
}

char* getUsername(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            return sessions[i].username;
        }
    }
    return NULL;
}

void invalidateSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            // Shift remaining sessions to fill the gap
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            return;
        }
    }
}


int main() {
    char* sessionId1 = createSession("user1");
    char* sessionId2 = createSession("user2");
    char* sessionId3 = createSession("user3");


    printf("%s\n", getUsername(sessionId1)); // Output: user1
    printf("%s\n", getUsername(sessionId2)); // Output: user2
    printf("%s\n", getUsername(sessionId3)); // Output: user3

    invalidateSession(sessionId2);

    printf("%s\n", getUsername(sessionId2)); // Output: (null)
    printf("%s\n", getUsername(sessionId1)); // Output: user1

    return 0;
}