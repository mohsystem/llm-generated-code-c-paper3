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
} Task123;

void init(Task123* manager) {
    manager->head = NULL;
}

char* generateUUID() {
    uuid_t uuid;
    char* uuid_str = (char*)malloc(37);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}

char* createSession(Task123* manager, const char* userId) {
    Session* newSession = (Session*)malloc(sizeof(Session));
    strcpy(newSession->sessionId, generateUUID());
    strcpy(newSession->userId, userId);
    newSession->next = manager->head;
    manager->head = newSession;
    return newSession->sessionId;
}

char* getUserId(Task123* manager, const char* sessionId) {
    Session* current = manager->head;
    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            return current->userId;
        }
        current = current->next;
    }
    return NULL;
}

void removeSession(Task123* manager, const char* sessionId) {
    Session* current = manager->head;
    Session* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            if (previous == NULL) {
                manager->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int main() {
    Task123 sessionManager;
    init(&sessionManager);

    // Test cases
    char* session1 = createSession(&sessionManager, "user1");
    printf("%d\n", strcmp(getUserId(&sessionManager, session1), "user1") == 0);

    char* session2 = createSession(&sessionManager, "user2");
    printf("%d\n", strcmp(getUserId(&sessionManager, session2), "user2") == 0);

    removeSession(&sessionManager, session1);
    printf("%d\n", getUserId(&sessionManager, session1) == NULL);

    char* session3 = createSession(&sessionManager, "user3");
    printf("%d\n", strcmp(getUserId(&sessionManager, session3), "user3") == 0);

    removeSession(&sessionManager, session2);
    printf("%d\n", getUserId(&sessionManager, session2) == NULL);

    return 0;
}