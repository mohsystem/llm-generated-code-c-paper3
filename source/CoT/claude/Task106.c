
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

typedef struct {
    mpz_t n;
    mpz_t d;
    mpz_t e;
} RSA_KEY;

void init_rsa(RSA_KEY* key, int bits) {
    mpz_t p, q, phi;
    gmp_randstate_t state;
    
    mpz_inits(key->n, key->d, key->e, p, q, phi, NULL);
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    // Generate primes
    mpz_urandomb(p, state, bits/2);
    mpz_nextprime(p, p);
    mpz_urandomb(q, state, bits/2);
    mpz_nextprime(q, q);
    
    // Calculate n = p * q
    mpz_mul(key->n, p, q);
    
    // Calculate phi = (p-1)(q-1)
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    
    // Set e = 65537
    mpz_set_ui(key->e, 65537);
    
    // Calculate d
    mpz_invert(key->d, key->e, phi);
    
    mpz_clears(p, q, phi, NULL);
    gmp_randclear(state);
}

void clear_rsa(RSA_KEY* key) {
    mpz_clears(key->n, key->d, key->e, NULL);
}

void encrypt(const RSA_KEY* key, const unsigned char* msg, size_t len, mpz_t result) {
    mpz_t m;
    mpz_init(m);
    
    mpz_import(m, len, 1, 1, 0, 0, msg);
    mpz_powm(result, m, key->e, key->n);
    
    mpz_clear(m);
}

void decrypt(const RSA_KEY* key, const mpz_t cipher, unsigned char* result, size_t* len) {
    mpz_t m;
    mpz_init(m);
    
    mpz_powm(m, cipher, key->d, key->n);
    mpz_export(result, len, 1, 1, 0, 0, m);
    
    mpz_clear(m);
}

int main() {
    RSA_KEY key;
    init_rsa(&key, 2048);
    mpz_t cipher;
    mpz_init(cipher);
    unsigned char decrypted[1024];
    size_t dec_len;
    
    // Test case 1
    const char* msg1 = "Hello World";
    encrypt(&key, (unsigned char*)msg1, strlen(msg1), cipher);
    decrypt(&key, cipher, decrypted, &dec_len);
    decrypted[dec_len] = '\\0';
    printf("Test 1: %s\\n", decrypted);
    
    // Test case 2
    const char* msg2 = "RSA Encryption";
    encrypt(&key, (unsigned char*)msg2, strlen(msg2), cipher);
    decrypt(&key, cipher, decrypted, &dec_len);
    decrypted[dec_len] = '\\0';
    printf("Test 2: %s\\n", decrypted);
    
    // Test case 3
    const char* msg3 = "Cryptography";
    encrypt(&key, (unsigned char*)msg3, strlen(msg3), cipher);
    decrypt(&key, cipher, decrypted, &dec_len);
    decrypted[dec_len] = '\\0';
    printf("Test 3: %s\\n", decrypted);
    
    // Test case 4
    const char* msg4 = "Security";
    encrypt(&key, (unsigned char*)msg4, strlen(msg4), cipher);
    decrypt(&key, cipher, decrypted, &dec_len);
    decrypted[dec_len] = '\\0';
    printf("Test 4: %s\\n", decrypted);
    
    // Test case 5
    const char* msg5 = "Test Message";
    encrypt(&key, (unsigned char*)msg5, strlen(msg5), cipher);
    decrypt(&key, cipher, decrypted, &dec_len);
    decrypted[dec_len] = '\\0';
    printf("Test 5: %s\\n", decrypted);
    
    mpz_clear(cipher);
    clear_rsa(&key);
    return 0;
}
