#include <stdio.h>
#include <uuid/uuid.h>

void generate_session_id(char *str) {
    uuid_t id;
    uuid_generate_random(id);
    uuid_unparse(id, str);
}

int main() {
    char str[37];
    generate_session_id(str);
    printf("%s\n", str);
    generate_session_id(str);
    printf("%s\n", str);
    generate_session_id(str);
    printf("%s\n", str);
    generate_session_id(str);
    printf("%s\n", str);
    generate_session_id(str);
    printf("%s\n", str);
    return 0;
}