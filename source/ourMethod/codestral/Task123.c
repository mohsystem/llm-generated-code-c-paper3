#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

#define MAX_SESSIONS 100
#define UUID_STR_LEN 37

struct Session {
    char id[UUID_STR_LEN];
    char data[100];
};

struct SessionManager {
    struct Session sessions[MAX_SESSIONS];
    int count;
};

void createSession(struct SessionManager* manager) {
    if (manager->count < MAX_SESSIONS) {
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_unparse(uuid, manager->sessions[manager->count].id);
        manager->count++;
    } else {
        printf("Max sessions reached\n");
    }
}

char* getSession(struct SessionManager* manager, char* sessionId) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->sessions[i].id, sessionId) == 0) {
            return manager->sessions[i].data;
        }
    }
    return NULL;
}

void endSession(struct SessionManager* manager, char* sessionId) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->sessions[i].id, sessionId) == 0) {
            memmove(&manager->sessions[i], &manager->sessions[i + 1], sizeof(struct Session) * (manager->count - i - 1));
            manager->count--;
            break;
        }
    }
}

int main() {
    struct SessionManager manager;
    manager.count = 0;
    createSession(&manager);
    printf("Session created: %s\n", manager.sessions[0].id);
    printf("Session data: %s\n", getSession(&manager, manager.sessions[0].id));
    endSession(&manager, manager.sessions[0].id);
    printf("Session ended\n");
    return 0;
}