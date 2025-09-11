#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SESSIONS 100

char* sessions[MAX_SESSIONS];
int session_count = 0;

char* login() {
    uuid_t uuid;
    uuid_generate(uuid);
    char* session_id = (char*)malloc(37);
    uuid_unparse(uuid, session_id);
    sessions[session_count++] = session_id;
    return session_id;
}

void logout(const char* session_id) {
    for (int i = 0; i < session_count; i++) {
        if (strcmp(sessions[i], session_id) == 0) {
            free(sessions[i]);
            sessions[i] = sessions[--session_count];
            break;
        }
    }
}

int main() {
    char* session_id1 = login();
    char* session_id2 = login();

    printf("Logged in sessions: %d\n", session_count);

    logout(session_id1);

    printf("Logged in sessions: %d\n", session_count);

    return 0;
}