#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <uuid/uuid.h>

typedef struct {
    char sessionId[37];
    char userId[20];
    time_t creationTime;
    time_t expirationTime;
} Session;

void generateUUID(char* uuid) {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, uuid);
}

void createSession(Session* session, const char* userId, int expirationTime) {
    generateUUID(session->sessionId);
    strcpy(session->userId, userId);
    session->creationTime = time(NULL);
    session->expirationTime = session->creationTime + expirationTime;
}

int isSessionExpired(const Session* session) {
    return time(NULL) > session->expirationTime;
}

int main() {
    Session sessions[2];

    // Test cases
    createSession(&sessions[0], "user1", 3600); // 1 hour
    createSession(&sessions[1], "user2", 1800); // 30 minutes

    printf("Session ID 1: %s\n", sessions[0].sessionId);
    printf("Session ID 2: %s\n", sessions[1].sessionId);

    printf("Is Session 1 active? %s\n", isSessionExpired(&sessions[0]) ? "No" : "Yes");
    printf("Is Session 2 active? %s\n", isSessionExpired(&sessions[1]) ? "No" : "Yes");

    return 0;
}