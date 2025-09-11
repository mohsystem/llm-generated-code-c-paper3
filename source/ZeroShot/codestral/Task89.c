#include <stdio.h>
#include <string.h>

int comparePassword(char *userPassword) {
    FILE *file = fopen("password.txt", "r");
    char storedPassword[100];
    fgets(storedPassword, 100, file);
    fclose(file);

    int len1 = strlen(userPassword);
    int len2 = strlen(storedPassword);

    if(len1 != len2) {
        return 0;
    }

    for(int i = 0; i < len1; i++) {
        if(userPassword[i] != storedPassword[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    printf("%d\n", comparePassword("password1"));
    printf("%d\n", comparePassword("wrongpassword"));
    printf("%d\n", comparePassword("passwor"));
    printf("%d\n", comparePassword("password123"));
    printf("%d\n", comparePassword("password1"));
    return 0;
}