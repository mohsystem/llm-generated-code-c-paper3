#include <stdio.h>

int modPow(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
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

int encrypt(int message, int e, int n) {
    return modPow(message, e, n);
}

int decrypt(int encrypted, int d, int n) {
    return modPow(encrypted, d, n);
}

int main() {
    int p = 61;  // First prime number
    int q = 53;  // Second prime number
    int n = p * q;  // Modulus
    int phi = (p - 1) * (q - 1);  // Euler's totient function
    int e = 17;  // Public exponent
    int d = modInverse(e, phi);  // Private exponent

    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);

    // Test cases
    int messages[] = {12, 24, 36, 48, 60};
    for (int i = 0; i < 5; ++i) {
        int message = messages[i];
        int encrypted = encrypt(message, e, n);
        int decrypted = decrypt(encrypted, d, n);
        printf("Message: %d, Encrypted: %d, Decrypted: %d\n", message, encrypted, decrypted);
    }

    return 0;
}