
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Note: This is a simplified implementation for educational purposes
// Real-world applications should use cryptographic libraries

typedef unsigned long long ull;

struct Task106 {
    ull n, d, e;
};

// Power with modulo
ull power_mod(ull base, ull exp, ull mod) {
    ull result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// GCD using Euclidean algorithm
ull gcd(ull a, ull b) {
    ull temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Miller-Rabin primality test
int is_prime(ull n, int k) {
    if (n <= 1 || n == 4) return 0;
    if (n <= 3) return 1;
    
    ull d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    
    for (int i = 0; i < k; i++) {
        ull a = 2 + rand() % (n - 3);
        ull x = power_mod(a, d, n);
        
        if (x == 1 || x == n - 1)
            continue;
            
        int is_composite = 1;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            
            if (x == 1) return 0;
            if (x == n - 1) {
                is_composite = 0;
                break;
            }
        }
        
        if (is_composite) return 0;
    }
    return 1;
}

// Generate a random prime number
ull generate_prime(int bits) {
    ull num;
    do {
        num = (1ULL << (bits - 1)) | rand();
    } while (!is_prime(num, 20));
    return num;
}

// Initialize RSA
void init_rsa(struct Task106* rsa) {
    // Generate p and q
    ull p = generate_prime(16); // Small numbers for demonstration
    ull q = generate_prime(16);
    while (p == q) {
        q = generate_prime(16);
    }
    
    rsa->n = p * q;
    ull phi = (p - 1) * (q - 1);
    
    // Choose e
    rsa->e = 65537; // Common value for e
    
    // Calculate d
    ull d = 1;
    while (((d * rsa->e) % phi) != 1)
        d++;
    rsa->d = d;
}

// Encrypt a message
ull encrypt(struct Task106* rsa, ull message) {
    if (message >= rsa->n) {
        fprintf(stderr, "Message too large for current key size\\n");
        return 0;
    }
    return power_mod(message, rsa->e, rsa->n);
}

// Decrypt a message
ull decrypt(struct Task106* rsa, ull encrypted_message) {
    return power_mod(encrypted_message, rsa->d, rsa->n);
}

int main() {
    srand(time(NULL));
    
    struct Task106 rsa;
    init_rsa(&rsa);
    
    // Test cases
    ull test_messages[] = {
        123,
        456,
        789,
        321,
        654
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Original: %llu\\n", test_messages[i]);
        ull encrypted = encrypt(&rsa, test_messages[i]);
        printf("Encrypted: %llu\\n", encrypted);
        ull decrypted = decrypt(&rsa, encrypted);
        printf("Decrypted: %llu\\n", decrypted);
        printf("Successful: %d\\n\\n", test_messages[i] == decrypted);
    }
    
    return 0;
}
