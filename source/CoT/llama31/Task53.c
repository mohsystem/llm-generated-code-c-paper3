#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Session {
    char* sessionID;
    char* username;
    struct Session* next;
} Session;

Session* head = NULL;

void createUserSession(const char* username, const char* password) {
    Session* newSession = (Session*) malloc(sizeof(Session));
    newSession->sessionID = (char*) malloc(strlen("sessionID") + 10);
    sprintf(newSession->sessionID, "sessionID%d", (int)(head == NULL ? 1 : (int)(head->sessionID[9] - '0') + 1));
    newSession->username = (char*) malloc(strlen(username) + 1);
    strcpy(newSession->username, username);
    newSession->next = head;
    head = newSession;
    printf("User session created for %s with session ID: %s\n", username, newSession->sessionID);
}

void validateUserSession(const char* username, const char* sessionID) {
    Session* current = head;
    while (current != NULL) {
        if (strcmp(current->sessionID, sessionID) == 0 && strcmp(current->username, username) == 0) {
            printf("User session is valid for %s\n", username);
            return;
        }
        current = current->next;
    }
    printf("User session is invalid for %s\n", username);
}

void terminateUserSession(const char* username) {
    if (head == NULL) return;

    if (strcmp(head->username, username) == 0) {
        Session* temp = head;
        head = head->next;
        free(temp->sessionID);
        free(temp->username);
        free(temp);
        printf("User session terminated for %s\n", username);
        return;
    }

    Session* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->username, username) == 0) {
            Session* temp = current->next;
            current->next = current->next->next;
            free(temp->sessionID);
            free(temp->username);
            free(temp);
            printf("User session terminated for %s\n", username);
            return;
        }
        current = current->next;
    }
    printf("No active session found for %s\n", username);
}

int main() {
    // Test cases
    createUserSession("user1", "password1");
    createUserSession("user2", "password2");
    validateUserSession("user1", "sessionID1");
    terminateUserSession("user1");
    validateUserSession("user1", "sessionID1");

    return 0;
}