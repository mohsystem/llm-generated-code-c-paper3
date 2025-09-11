#include <stdio.h>
#include <uuid/uuid.h>

void generateToken(char *token) {
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, token);
}

int main() {
    char token[37];
    generateToken(token);
    printf("%s\n", token);
    return 0;
}