#include <stdio.h>
#include <stdlib.h>

void generateRSAKey() {
    system("ssh-keygen -t rsa -N '' -f ~/.ssh/id_rsa");
    printf("RSA key generated successfully.\n");
}

int main() {
    generateRSAKey();
    return 0;
}