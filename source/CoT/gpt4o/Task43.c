// C code for managing user sessions securely
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Session {
    char sessionId[37];
    char userId[50];
} Session;

typedef struct Task43 {
    Session sessions[100];
    int count;
} Task43;

void init(Task43 *app) {
    app->count = 0;
    srand(time(NULL));
}

char *createSession(Task43 *app, const char *userId) {
    char *sessionId = (char *)malloc(37 * sizeof(char));
    snprintf(sessionId, 37, "%d", rand());
    strcpy(app->sessions[app->count].sessionId, sessionId);
    strcpy(app->sessions[app->count].userId, userId);
    app->count++;
    return sessionId;
}

int isValidSession(Task43 *app, const char *sessionId) {
    for (int i = 0; i < app->count; i++) {
        if (strcmp(app->sessions[i].sessionId, sessionId) == 0) {
            return 1;
        }
    }
    return 0;
}

void terminateSession(Task43 *app, const char *sessionId) {
    for (int i = 0; i < app->count; i++) {
        if (strcmp(app->sessions[i].sessionId, sessionId) == 0) {
            for (int j = i; j < app->count - 1; j++) {
                app->sessions[j] = app->sessions[j + 1];
            }
            app->count--;
            break;
        }
    }
}

int main() {
    Task43 app;
    init(&app);

    char *session1 = createSession(&app, "user1");
    char *session2 = createSession(&app, "user2");

    printf("Session1 valid: %d\n", isValidSession(&app, session1));
    printf("Session2 valid: %d\n", isValidSession(&app, session2));

    terminateSession(&app, session1);

    printf("Session1 valid after termination: %d\n", isValidSession(&app, session1));
    printf("Session2 valid after termination: %d\n", isValidSession(&app, session2));

    char *session3 = createSession(&app, "user3");

    printf("Session3 valid: %d\n", isValidSession(&app, session3));

    free(session1);
    free(session2);
    free(session3);

    return 0;
}