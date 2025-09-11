#include <stdio.h>
#include <time.h>

typedef struct {
    char userId[100];
    char sessionId[100];
    time_t startTime;
} Session;

Session createSession(const char* userId, const char* sessionId) {
    Session session;
    strcpy(session.userId, userId);
    strcpy(session.sessionId, sessionId);
    session.startTime = time(NULL);
    return session;
}

int isValid(const Session* session) {
    // Simple validation: session is valid for 30 minutes
    return difftime(time(NULL), session->startTime) < 30 * 60;
}

int main() {
    // Test cases
    Session session1 = createSession("user1", "session1");
    Session session2 = createSession("user2", "session2");

    printf("Is session1 valid? %s\n", isValid(&session1) ? "Yes" : "No");
    printf("Is session2 valid? %s\n", isValid(&session2) ? "Yes" : "No");

    sleep(31);  // Wait for more than 30 seconds

    printf("Is session1 valid after 30 seconds? %s\n", isValid(&session1) ? "Yes" : "No");
    printf("Is session2 valid after 30 seconds? %s\n", isValid(&session2) ? "Yes" : "No");

    return 0;
}