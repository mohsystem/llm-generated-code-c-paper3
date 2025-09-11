#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct Session {
    char userId[50];
    time_t lastActive;
    struct Session* next;
} Session;

typedef struct {
    Session* head;
    int sessionTimeout;
} SessionManager;

SessionManager* createSessionManager() {
    SessionManager* sm = (SessionManager*)malloc(sizeof(SessionManager));
    sm->head = NULL;
    sm->sessionTimeout = 300; // 5 minutes in seconds
    return sm;
}

void createSession(SessionManager* sm, const char* userId) {
    Session* newSession = (Session*)malloc(sizeof(Session));
    strcpy(newSession->userId, userId);
    newSession->lastActive = time(NULL);
    newSession->next = sm->head;
    sm->head = newSession;
}

int isSessionActive(SessionManager* sm, const char* userId) {
    Session* current = sm->head;
    while (current != NULL) {
        if (strcmp(current->userId, userId) == 0) {
            return (time(NULL) - current->lastActive < sm->sessionTimeout);
        }
        current = current->next;
    }
    return 0;
}

void refreshSession(SessionManager* sm, const char* userId) {
    Session* current = sm->head;
    while (current != NULL) {
        if (strcmp(current->userId, userId) == 0) {
            current->lastActive = time(NULL);
            break;
        }
        current = current->next;
    }
}

void endSession(SessionManager* sm, const char* userId) {
    Session** current = &sm->head;
    while (*current != NULL) {
        if (strcmp((*current)->userId, userId) == 0) {
            Session* temp = *current;
            *current = (*current)->next;
            free(temp);
            break;
        }
        current = &(*current)->next;
    }
}

int main() {
    SessionManager* sm = createSessionManager();

    // Test cases
    createSession(sm, "user1");
    printf("%d\n", isSessionActive(sm, "user1")); // 1
    endSession(sm, "user1");
    printf("%d\n", isSessionActive(sm, "user1")); // 0

    createSession(sm, "user2");
    printf("%d\n", isSessionActive(sm, "user2")); // 1
    sleep(310);
    printf("%d\n", isSessionActive(sm, "user2")); // 0

    createSession(sm, "user3");
    refreshSession(sm, "user3");
    printf("%d\n", isSessionActive(sm, "user3")); // 1

    // Cleanup
    while (sm->head != NULL) {
        endSession(sm, sm->head->userId);
    }
    free(sm);

    return 0;
}