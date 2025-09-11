// Comment:  C implementation requires more advanced security libraries that are not readily available in standard C. OpenSSL is commonly used, but including it here would make the code significantly more complex.  For a basic demonstration without robust security, consider a simpler encryption method, but be aware of its limitations.

//  A basic (insecure for real-world use) example using XOR encryption is shown below for illustrative purposes only. Do not use this for sensitive data in a real application.

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt_decrypt(char *data, char *key) {
    int key_len = strlen(key);
    int data_len = strlen(data);
    for (int i = 0; i < data_len; i++) {
        data[i] = data[i] ^ key[i % key_len];
    }
}

int main() {
    char data[] = "Sensitive Data";
    char key[] = "MyKey";

    encrypt_decrypt(data, key); // Encrypt
    printf("Encrypted: %s\n", data);

    encrypt_decrypt(data, key); // Decrypt
    printf("Decrypted: %s\n", data);

    return 0;
}
*/