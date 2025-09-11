#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

long long generate_prime() {
    return rand() % 10000 + 10000; 
}

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

void rsa_encrypt_decrypt(char *message) {
    long long p = generate_prime();
    long long q = generate_prime();
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 3;
    while (gcd(e, phi) != 1) {
        e += 2;
    }
    long long d = mod_inverse(e, phi);

    long long *encrypted = (long long *)malloc(strlen(message) * sizeof(long long));
    char *decrypted = (char *)malloc((strlen(message) + 1) * sizeof(char));

    printf("Original: %s\n", message);
    printf("Encrypted: ");
    for (size_t i = 0; i < strlen(message); i++) {
        long long m = (long long)message[i];
        encrypted[i] = (long long)pow(m, e) % n;
        printf("%lld ", encrypted[i]);
    }
    printf("\n");

    printf("Decrypted: ");
    for (size_t i = 0; i < strlen(message); i++) {
        decrypted[i] = (char)(pow(encrypted[i], d) % n);
    }
    decrypted[strlen(message)] = '\0';
    printf("%s\n", decrypted);

    free(encrypted);
    free(decrypted);
}

int main() {
    srand(time(NULL));

    char *testMessages[] = {
        "Test message 1",
        "Test message 2",
        "Test message 3",
        "Test message 4",
        "Test message 5"
    };

    for (int i = 0; i < 5; i++) {
        rsa_encrypt_decrypt(testMessages[i]);
        printf("\n");
    }

    return 0;
}