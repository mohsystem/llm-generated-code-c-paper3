#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Session {
    int userId;
    char* username;
} Session;

typedef struct SessionList {
    Session* sessions;
    int size;
} SessionList;

void createSession(SessionList* list, int userId, const char* username) {
    for (int i = 0; i < list->size; i++) {
        if (list->sessions[i].userId == userId) {
            free(list->sessions[i].username);
            list->sessions[i].username = strdup(username);
            return;
        }
    }

    list->sessions = realloc(list->sessions, (list->size + 1) * sizeof(Session));
    list->sessions[list->size].userId = userId;
    list->sessions[list->size].username = strdup(username);
    list->size++;
}

char* getSession(SessionList* list, int userId) {
    for (int i = 0; i < list->size; i++) {
        if (list->sessions[i].userId == userId) {
            return list->sessions[i].username;
        }
    }
    return NULL;
}

void invalidateSession(SessionList* list, int userId) {
    for (int i = 0; i < list->size; i++) {
        if (list->sessions[i].userId == userId) {
            free(list->sessions[i].username);
            // Shift elements to fill the gap
            for (int j = i; j < list->size - 1; j++) {
                list->sessions[j] = list->sessions[j + 1];
            }
            list->size--;
            list->sessions = realloc(list->sessions, list->size * sizeof(Session));
            return;
        }
    }
}

int main() {
    SessionList list;
    list.sessions = NULL;
    list.size = 0;

    // Test cases
    createSession(&list, 1, "user1");
    printf("Username: %s\n", getSession(&list, 1));  // Output: Username: user1
    createSession(&list, 2, "user2");
    printf("Username: %s\n", getSession(&list, 2));  // Output: Username: user2
    invalidateSession(&list, 1);
    printf("Username: %s\n", getSession(&list, 1));  // Output: Username: (null)
    printf("Username: %s\n", getSession(&list, 2));  // Output: Username: user2
    invalidateSession(&list, 2);
    printf("Username: %s\n", getSession(&list, 2));  // Output: Username: (null)

    // Free allocated memory
    for (int i = 0; i < list.size; i++) {
        free(list.sessions[i].username);
    }
    free(list.sessions);

    return 0;
}