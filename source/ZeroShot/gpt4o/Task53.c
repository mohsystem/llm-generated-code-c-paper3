#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char sessionId[37];
    char userId[100];
} Session;

typedef struct {
    Session sessions[100];
    int count;
} SessionStore;

void generateSessionId(char *sessionId) {
    const char *chars = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        sessionId[i] = chars[rand() % 16];
    }
    sessionId[32] = '\0';
}

void initSessionStore(SessionStore *store) {
    store->count = 0;
    srand((unsigned int) time(NULL));
}

char* createSession(SessionStore *store, const char *userId) {
    if (store->count < 100) {
        generateSessionId(store->sessions[store->count].sessionId);
        strcpy(store->sessions[store->count].userId, userId);
        return store->sessions[store->count++].sessionId;
    }
    return NULL;
}

char* getUserId(SessionStore *store, const char *sessionId) {
    for (int i = 0; i < store->count; i++) {
        if (strcmp(store->sessions[i].sessionId, sessionId) == 0) {
            return store->sessions[i].userId;
        }
    }
    return NULL;
}

int destroySession(SessionStore *store, const char *sessionId) {
    for (int i = 0; i < store->count; i++) {
        if (strcmp(store->sessions[i].sessionId, sessionId) == 0) {
            for (int j = i; j < store->count - 1; j++) {
                store->sessions[j] = store->sessions[j + 1];
            }
            store->count--;
            return 1;
        }
    }
    return 0;
}

int main() {
    SessionStore store;
    initSessionStore(&store);

    // Test Case 1
    char* session1 = createSession(&store, "user1");
    printf("%s\n", getUserId(&store, session1));

    // Test Case 2
    char* session2 = createSession(&store, "user2");
    printf("%s\n", getUserId(&store, session2));

    // Test Case 3
    printf("%s\n", getUserId(&store, "invalid_session"));

    // Test Case 4
    destroySession(&store, session1);
    printf("%s\n", getUserId(&store, session1));

    // Test Case 5
    printf("%d\n", destroySession(&store, session2));

    return 0;
}