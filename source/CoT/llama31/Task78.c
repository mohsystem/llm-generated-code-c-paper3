#include <stdio.h>
#include <stdlib.h>

void generateRSAKey(const char* privateKeyFile, const char* publicKeyFile) {
    char command[1024];
    sprintf(command, "ssh-keygen -t rsa -b 2048 -N \"\" -f %s", privateKeyFile);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to generate RSA key\n");
        exit(1);
    }
    printf("Private Key: %s\n", privateKeyFile);
    printf("Public Key: %s\n", publicKeyFile);
}

int main() {
    generateRSAKey("id_rsa", "id_rsa.pub");
    return 0;
}