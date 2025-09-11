
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    long long n;
    long long e;
    long long d;
} RSA;

int isPrime(long long num) {
    if (num < 2) return 0;
    for (long long i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

long long generatePrime(long long min_val, long long max_val) {
    long long prime = rand() % (max_val - min_val + 1) + min_val;
    while (!isPrime(prime)) {
        prime = rand() % (max_val - min_val + 1) + min_val;
    }
    return prime;
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

void generateKeys(RSA* rsa) {
    long long p = generatePrime(100, 1000);
    long long q = generatePrime(100, 1000);
    
    rsa->n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    rsa->e = 2;
    while (rsa->e < phi) {
        if (gcd(rsa->e, phi) == 1) break;
        rsa->e++;
    }
    
    rsa->d = modInverse(rsa->e, phi);
}

long long encrypt(RSA* rsa, long long message) {
    long long result = 1;
    for (long long i = 0; i < rsa->e; i++) {
        result = (result * message) % rsa->n;
    }
    return result;
}

long long decrypt(RSA* rsa, long long encrypted) {
    long long result = 1;
    for (long long i = 0; i < rsa->d; i++) {
        result = (result * encrypted) % rsa->n;
    }
    return result;
}

int main() {
    srand(time(0));
    RSA rsa;
    generateKeys(&rsa);
    
    // Test case 1
    long long msg1 = 123;
    long long encrypted1 = encrypt(&rsa, msg1);
    printf("Test 1: %d\\n", msg1 == decrypt(&rsa, encrypted1));
    
    // Test case 2
    long long msg2 = 456;
    long long encrypted2 = encrypt(&rsa, msg2);
    printf("Test 2: %d\\n", msg2 == decrypt(&rsa, encrypted2));
    
    // Test case 3
    long long msg3 = 789;
    long long encrypted3 = encrypt(&rsa, msg3);
    printf("Test 3: %d\\n", msg3 == decrypt(&rsa, encrypted3));
    
    // Test case 4
    long long msg4 = 321;
    long long encrypted4 = encrypt(&rsa, msg4);
    printf("Test 4: %d\\n", msg4 == decrypt(&rsa, encrypted4));
    
    // Test case 5
    long long msg5 = 654;
    long long encrypted5 = encrypt(&rsa, msg5);
    printf("Test 5: %d\\n", msg5 == decrypt(&rsa, encrypted5));
    
    return 0;
}
