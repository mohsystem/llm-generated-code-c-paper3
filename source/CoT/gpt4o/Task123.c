#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

typedef struct Session {
    char sessionId[37];
    char userId[50];
    struct Session* next;
} Session;

typedef struct {
    Session* head;
} SessionManager;

void initSessionManager(SessionManager* manager) {
    manager->head = NULL;
}

char* createSession(SessionManager* manager, const char* userId) {
    Session* newSession = (Session*)malloc(sizeof(Session));
    if (!newSession) {
        return NULL;
    }

    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, newSession->sessionId);
    strncpy(newSession->userId, userId, sizeof(newSession->userId) - 1);
    newSession->userId[sizeof(newSession->userId) - 1] = '\0';

    newSession->next = manager->head;
    manager->head = newSession;

    return newSession->sessionId;
}

char* getUserId(SessionManager* manager, const char* sessionId) {
    Session* current = manager->head;
    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            return current->userId;
        }
        current = current->next;
    }
    return NULL;
}

int removeSession(SessionManager* manager, const char* sessionId) {
    Session** current = &manager->head;
    while (*current != NULL) {
        if (strcmp((*current)->sessionId, sessionId) == 0) {
            Session* toRemove = *current;
            *current = (*current)->next;
            free(toRemove);
            return 1;
        }
        current = &(*current)->next;
    }
    return 0;
}

int isValidSession(SessionManager* manager, const char* sessionId) {
    Session* current = manager->head;
    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    SessionManager manager;
    initSessionManager(&manager);
    
    // Test cases
    char* session1 = createSession(&manager, "user1");
    char* session2 = createSession(&manager, "user2");
    char* session3 = createSession(&manager, "user3");
    char* session4 = createSession(&manager, "user4");
    char* session5 = createSession(&manager, "user5");

    printf("%s\n", getUserId(&manager, session1)); // Should print "user1"
    printf("%d\n", isValidSession(&manager, session2)); // Should print "1"
    printf("%d\n", removeSession(&manager, session3)); // Should print "1"
    printf("%d\n", isValidSession(&manager, session3)); // Should print "0"
    printf("%s\n", getUserId(&manager, session5)); // Should print "user5"

    return 0;
}