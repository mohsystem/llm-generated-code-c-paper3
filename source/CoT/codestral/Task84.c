#include <stdio.h>
#include <uuid/uuid.h>

void generateSessionId(char *str) {
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, str);
}

int main() {
    char str[37];
    generateSessionId(str);
    printf("%s\n", str);
    generateSessionId(str);
    printf("%s\n", str);
    generateSessionId(str);
    printf("%s\n", str);
    generateSessionId(str);
    printf("%s\n", str);
    generateSessionId(str);
    printf("%s\n", str);
    return 0;
}