#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int multiplicative_inverse(int e, int phi) {
    int d = 0;
    int x1 = 0, x2 = 1, y1 = 1, temp_phi = phi;

    if (phi == 1)
        return 0;

    while (e > 0) {
        int temp1 = temp_phi / e;
        int temp2 = temp_phi - temp1 * e;
        temp_phi = e;
        e = temp2;

        int x = x2 - temp1 * x1;
        int y = d - temp1 * y1;

        x2 = x1;
        x1 = x;
        d = y1;
        y1 = y;
    }

    if (temp_phi == 1)
        return d + phi;
}

void rsa(int p, int q, int* e, int* n, int* d) {
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    *e = 3;
    *d = multiplicative_inverse(*e, phi);
}

void encrypt(int e, int n, char* plain_text, int* cipher_text) {
    for (; *plain_text; ++plain_text)
        *cipher_text++ = pow(*plain_text, e) % n;
}

void decrypt(int d, int n, int* cipher_text, char* plain_text) {
    for (; *cipher_text; ++cipher_text)
        *plain_text++ = pow(*cipher_text, d) % n;
}

int main() {
    int public_key[2], private_key[2];
    rsa(11, 13, &public_key[0], &public_key[1], &private_key[0], &private_key[1]);
    char msg[] = "HELLO";
    int encrypted_msg[5];
    char decrypted_msg[5];
    encrypt(public_key[0], public_key[1], msg, encrypted_msg);
    decrypt(private_key[0], private_key[1], encrypted_msg, decrypted_msg);
    printf("Original: %s Encrypted: ", msg);
    for (int i = 0; i < 5; ++i)
        printf("%d ", encrypted_msg[i]);
    printf("Decrypted: %s\n", decrypted_msg);
    return 0;
}