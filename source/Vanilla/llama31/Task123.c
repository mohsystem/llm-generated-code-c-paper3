#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char sessionId[37];
    char userId[20];
    time_t createTime;
    time_t lastAccessTime;
} Session;

void generateUUID(char* uuid) {
    FILE* fp = popen("uuidgen", "r");
    if (fp == NULL) {
        printf("Failed to generate UUID\n");
        exit(1);
    }
    fgets(uuid, 37, fp);
    pclose(fp);
    uuid[strcspn(uuid, "\n")] = 0; // Remove newline character
}

Session* createSession(const char* userId) {
    Session* session = malloc(sizeof(Session));
    generateUUID(session->sessionId);
    strcpy(session->userId, userId);
    session->createTime = time(NULL);
    session->lastAccessTime = session->createTime;
    return session;
}

void updateLastAccessTime(Session* session) {
    session->lastAccessTime = time(NULL);
}

int isExpired(Session* session, int timeout) {
    return difftime(time(NULL), session->lastAccessTime) > timeout;
}

void printSession(Session* session) {
    printf("Session ID: %s\n", session->sessionId);
    printf("Is Expired? %d\n", isExpired(session, 10));
}

int main() {
    // Test cases
    Session* session1 = createSession("user1");
    printSession(session1);
    updateLastAccessTime(session1);
    printSession(session1);

    Session* session2 = createSession("user2");
    printSession(session2);
    sleep(11); // Sleep for 11 seconds
    printSession(session2);

    Session* session3 = createSession("user3");
    printSession(session3);
    updateLastAccessTime(session3);
    printSession(session3);

    Session* session4 = createSession("user4");
    printSession(session4);
    sleep(5); // Sleep for 5 seconds
    printSession(session4);

    Session* session5 = createSession("user5");
    printSession(session5);
    sleep(15); // Sleep for 15 seconds
    printSession(session5);

    free(session1);
    free(session2);
    free(session3);
    free(session4);
    free(session5);

    return 0;
}