#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* resetPassword(const char* username) {
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()";
    char* newPassword = (char*)malloc(9 * sizeof(char)); 
    srand(time(NULL));

    for (int i = 0; i < 8; i++) {
        newPassword[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    newPassword[8] = '\0'; 

    return newPassword;
}

int main() {
    char* password1 = resetPassword("user1");
    printf("%s\n", password1);
    free(password1);

    char* password2 = resetPassword("user2");
    printf("%s\n", password2);
    free(password2);

    char* password3 = resetPassword("user3");
    printf("%s\n", password3);
    free(password3);

    char* password4 = resetPassword("user4");
    printf("%s\n", password4);
    free(password4);

    char* password5 = resetPassword("user5");
    printf("%s\n", password5);
    free(password5);

    return 0;
}