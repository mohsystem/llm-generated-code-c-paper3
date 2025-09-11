#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

int modPow(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if ((exponent & 1) == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

void encrypt(char* message, int e, int n, char* encrypted) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        int cText = modPow(message[i], e, n);
        sprintf(encrypted + strlen(encrypted), "%d ", cText);
    }
}

void decrypt(char* encrypted, int d, int n, char* decrypted) {
    char* token = strtok(encrypted, " ");
    while (token != NULL) {
        int cText = atoi(token);
        char c = (char)modPow(cText, d, n);
        strcat(decrypted, &c);
        token = strtok(NULL, " ");
    }
}

int main() {
    int testCases[] = {17, 19, 61, 53, 59};
    for (int i = 0; i < 5; i++) {
        int p = testCases[i];
        int q = testCases[(i + 1) % 5];
        int n = p * q;
        int phi = (p - 1) * (q - 1);
        int e = 2;
        while (gcd(e, phi) != 1) {
            e++;
        }
        int d = modInverse(e, phi);

        char message[] = "Hello, RSA!";
        char encrypted[1024] = {0};
        char decrypted[1024] = {0};

        encrypt(message, e, n, encrypted);
        decrypt(encrypted, d, n, decrypted);

        printf("Original Message: %s\n", message);
        printf("Encrypted Message: %s\n", encrypted);
        printf("Decrypted Message: %s\n\n", decrypted);
    }
    return 0;
}