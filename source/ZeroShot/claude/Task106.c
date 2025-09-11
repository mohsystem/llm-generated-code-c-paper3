
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Simple RSA implementation with limited functionality due to C constraints
typedef struct {
    long long n;
    long long d;
    long long e;
} Task106;

int isPrime(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

long long generatePrime(int min, int max) {
    long long num;
    do {
        num = rand() % (max - min + 1) + min;
    } while (!isPrime(num));
    return num;
}

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    
    if (x < 0) x += m0;
    return x;
}

void generateKeys(Task106* rsa) {
    long long p = generatePrime(100, 500);
    long long q = generatePrime(100, 500);
    
    rsa->n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    rsa->e = 65537;  // Common value for e
    rsa->d = modInverse(rsa->e, phi);
}

long long encrypt(Task106* rsa, long long message) {
    long long c = 1;
    for(int i = 0; i < rsa->e; i++) {
        c = (c * message) % rsa->n;
    }
    return c;
}

long long decrypt(Task106* rsa, long long ciphertext) {
    long long m = 1;
    for(int i = 0; i < rsa->d; i++) {
        m = (m * ciphertext) % rsa->n;
    }
    return m;
}

int main() {
    srand(time(0));
    Task106 rsa;
    generateKeys(&rsa);
    
    // Test case 1
    long long msg1 = 12345;
    long long encrypted1 = encrypt(&rsa, msg1);
    long long decrypted1 = decrypt(&rsa, encrypted1);
    printf("Test 1: %lld\\n", decrypted1);
    
    // Test case 2
    long long msg2 = 67890;
    long long encrypted2 = encrypt(&rsa, msg2);
    long long decrypted2 = decrypt(&rsa, encrypted2);
    printf("Test 2: %lld\\n", decrypted2);
    
    // Test case 3
    long long msg3 = 11111;
    long long encrypted3 = encrypt(&rsa, msg3);
    long long decrypted3 = decrypt(&rsa, encrypted3);
    printf("Test 3: %lld\\n", decrypted3);
    
    // Test case 4
    long long msg4 = 22222;
    long long encrypted4 = encrypt(&rsa, msg4);
    long long decrypted4 = decrypt(&rsa, encrypted4);
    printf("Test 4: %lld\\n", decrypted4);
    
    // Test case 5
    long long msg5 = 33333;
    long long encrypted5 = encrypt(&rsa, msg5);
    long long decrypted5 = decrypt(&rsa, encrypted5);
    printf("Test 5: %lld\\n", decrypted5);
    
    return 0;
}
