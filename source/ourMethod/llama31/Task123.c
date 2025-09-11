#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <uuid/uuid.h>

typedef struct Session {
    char username[100];
    time_t creationTime;
} Session;

typedef struct SessionNode {
    char sessionId[37];
    Session session;
    struct SessionNode* next;
} SessionNode;

SessionNode* head = NULL;

void addSession(SessionNode** head, const char* sessionId, const char* username) {
    SessionNode* newNode = (SessionNode*) malloc(sizeof(SessionNode));
    strcpy(newNode->sessionId, sessionId);
    strcpy(newNode->session.username, username);
    newNode->session.creationTime = time(NULL);
    newNode->next = *head;
    *head = newNode;
}

Session* getSession(SessionNode* head, const char* sessionId) {
    SessionNode* current = head;
    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            return &current->session;
        }
        current = current->next;
    }
    return NULL;
}

void invalidateSession(SessionNode** head, const char* sessionId) {
    SessionNode* current = *head;
    SessionNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->sessionId, sessionId) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    uuid_t bin_uuid;
    char uuid[37];

    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, uuid);
    addSession(&head, uuid, "user1");

    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, uuid);
    addSession(&head, uuid, "user2");

    Session* session1 = getSession(head, uuid);
    if (session1) {
        printf("User: %s, Created: %ld\n", session1->username, session1->creationTime);
    }

    invalidateSession(&head, uuid);
    printf("Session %s invalidated\n", uuid);

    // Test cases
    Session* session = getSession(head, uuid);
    if (session) {
        printf("Session %s is not null\n", uuid);
    } else {
        printf("Session %s is null\n", uuid);
    }

    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, uuid);
    session = getSession(head, uuid);
    if (session) {
        printf("User: %s\n", session->username);  // Should be user2
    }

    return 0;
}