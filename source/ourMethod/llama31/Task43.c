#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

void createSession(char* sessionId) {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    char uuid[37];
    uuid_unparse(bin_uuid, uuid);
    strcpy(sessionId, uuid);
}

void setSecureCookie(const char* sessionId) {
    printf("Set-Cookie: session_id=%s; HttpOnly; Secure; SameSite=Strict\r\n", sessionId);
}

void terminateSession() {
    printf("Set-Cookie: session_id=; Max-Age=0\r\n");
}