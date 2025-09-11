// Implementation for C would be similar to C++, requiring a BigInteger library.
// This simplified example uses long long, which is not suitable for real RSA.
// For robust implementation, use a BigInteger library (e.g., libgmp).

// (Simplified RSA using long long - NOT secure for real-world use)

#include <stdio.h>

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}


int main() {
    // (Simplified example - replace with proper key generation and BigInteger)
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d = 2753;

    long long messages[] = {12345, 67890, 13579, 24680, 123456789}; // Smaller messages

    for (int i = 0; i < 5; i++) {
        long long message = messages[i];
        long long ciphertext = power(message, e, n);
        long long decryptedMessage = power(ciphertext, d, n);
        printf("Message: %lld\n", message);
        printf("Ciphertext: %lld\n", ciphertext);
        printf("Decrypted: %lld\n", decryptedMessage);
        printf("-----\n");
    }

    return 0;
}