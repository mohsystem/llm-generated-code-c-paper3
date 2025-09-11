#include <stdio.h>
#include <uuid/uuid.h>

char* generateSessionID() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char *uuid_str = (char *)malloc(37);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}

int main() {
    printf("%s\n", generateSessionID());
    printf("%s\n", generateSessionID());
    printf("%s\n", generateSessionID());
    printf("%s\n", generateSessionID());
    printf("%s\n", generateSessionID());
    return 0;
}