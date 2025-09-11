#include <stdio.h>
#include <stdlib.h>

void generateSSHKey(const char* keyName) {
    char command[1024];
    sprintf(command, "ssh-keygen -t rsa -b 2048 -f %s -N ''", keyName);
    system(command);
    printf("Private key saved to %s\n", keyName);
    printf("Public key saved to %s.pub\n", keyName);
}

int main() {
    generateSSHKey("id_rsa");
    return 0;
}