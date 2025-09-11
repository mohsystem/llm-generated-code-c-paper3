#include <stdio.h>

void generateKeys(int p, int q, int e, int* keys) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = modInverse(e, phi);
    keys[0] = n;
    keys[1] = d;
}

int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

int encrypt(int* publicKey, int message) {
    int n = publicKey[0];
    int e = publicKey[1];
    return power(message, e, n);
}

int decrypt(int* privateKey, int ciphertext) {
    int n = privateKey[0];
    int d = privateKey[1];
    return power(ciphertext, d, n);
}

int power(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if ((exponent & 1) == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Test cases
    int testCases[] = {17, 19, 23, 29, 31};
    for (int i = 0; i < 5; i++) {
        int p = 61;
        int q = 53;
        int e = testCases[i];
        int keys[2];
        generateKeys(p, q, e, keys);
        int n = keys[0];
        int d = keys[1];
        int publicKey[] = {n, e};
        int privateKey[] = {n, d};

        int message = 12;
        int encrypted = encrypt(publicKey, message);
        int decrypted = decrypt(privateKey, encrypted);

        printf("Public Key: (%d, %d)\n", n, e);
        printf("Private Key: (%d, %d)\n", n, d);
        printf("Message: %d\n", message);
        printf("Encrypted: %d\n", encrypted);
        printf("Decrypted: %d\n\n", decrypted);
    }
    return 0;
}