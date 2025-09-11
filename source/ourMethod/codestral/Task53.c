// C doesn't have built-in support for associative containers (like a HashMap or Dictionary)
// or a standard way to handle strings, so a full implementation is quite complex.
// Therefore, I'm providing a simplified version of the session manager that only works with integers.

#include <stdio.h>
#include <stdlib.h>

#define MAX_SESSIONS 100

typedef struct {
    int data;
} SessionData;

typedef struct {
    int userId;
    SessionData data;
} Session;

Session sessions[MAX_SESSIONS];
int sessionCount = 0;

void createSession(int userId, SessionData data) {
    if (sessionCount < MAX_SESSIONS) {
        sessions[sessionCount].userId = userId;
        sessions[sessionCount].data = data;
        sessionCount++;
    }
}

SessionData getSession(int userId) {
    for (int i = 0; i < sessionCount; i++) {
        if (sessions[i].userId == userId) {
            return sessions[i].data;
        }
    }
    // Return an empty session data if the user ID is not found
    return (SessionData){0};
}

void endSession(int userId) {
    for (int i = 0; i < sessionCount; i++) {
        if (sessions[i].userId == userId) {
            // Shift all sessions after the one to be removed to the left
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            break;
        }
    }
}

int main() {
    SessionData data1 = {1};
    SessionData data2 = {2};

    createSession(1, data1);
    createSession(2, data2);

    printf("%d\n", getSession(1).data);
    printf("%d\n", getSession(2).data);

    endSession(1);
    printf("%d\n", getSession(1).data); // Should print 0

    return 0;
}