#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 1000

bool sessions[MAX_USERS];

void startSession(int userId) {
    sessions[userId] = true;
}

void endSession(int userId) {
    sessions[userId] = false;
}

bool isSessionActive(int userId) {
    return sessions[userId];
}

int main() {
    startSession(1);
    startSession(2);
    printf("%d\n", isSessionActive(1));  // 1 (true)
    endSession(1);
    printf("%d\n", isSessionActive(1));  // 0 (false)
    return 0;
}