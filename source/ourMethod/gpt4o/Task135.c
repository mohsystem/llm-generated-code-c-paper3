#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

typedef struct {
    char sessionId[37];
    char csrfToken[37];
} Session;

Session userSessions[10];
int sessionCount = 0;

void generateUUID(char* uuidStr) {
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuidStr);
}

char* login(const char* username) {
    if (sessionCount >= 10) return NULL; // Max sessions reached
    generateUUID(userSessions[sessionCount].sessionId);
    generateUUID(userSessions[sessionCount].csrfToken);
    return userSessions[sessionCount++].sessionId;
}

char* getCsrfToken(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(userSessions[i].sessionId, sessionId) == 0) {
            return userSessions[i].csrfToken;
        }
    }
    return NULL;
}

int validateRequest(const char* sessionId, const char* csrfToken) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(userSessions[i].sessionId, sessionId) == 0 && strcmp(userSessions[i].csrfToken, csrfToken) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char* session1 = login("user1");
    char* token1 = getCsrfToken(session1);
    printf("%d\n", validateRequest(session1, token1));  // 1 (true)

    char* session2 = login("user2");
    char* token2 = getCsrfToken(session2);
    printf("%d\n", validateRequest(session2, token2));  // 1 (true)

    // Invalid CSRF token
    printf("%d\n", validateRequest(session1, "invalidToken"));  // 0 (false)

    // Reusing token for another session
    printf("%d\n", validateRequest(session2, token1));  // 0 (false)

    // Invalid session ID
    printf("%d\n", validateRequest("invalidSession", token1));  // 0 (false)

    return 0;
}