#include <stdio.h>
#include <crypt.h>
#include <string.h>

void hashPassword(const char* password, const char* salt, char* hashedPassword) {
    strcpy(hashedPassword, crypt(password, salt));
}

int main() {
    char password[] = "myPassword";
    char salt[] = "$6$mySalt";
    char hashedPassword[100];
    hashPassword(password, salt, hashedPassword);
    printf("%s\n", hashedPassword);
    return 0;
}