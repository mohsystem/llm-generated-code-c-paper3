#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

typedef struct {
    mpz_t n;
    mpz_t e;
    mpz_t d;
} RSAKeys;

void generateKeys(RSAKeys* keys) {
    mpz_t p, q, phi;
    mpz_inits(p, q, phi, NULL);

    gmp_randstate_t randState;
    gmp_randinit_default(randState);
    gmp_randseed_ui(randState, time(NULL));

    mpz_urandomb(p, randState, 512);
    mpz_urandomb(q, randState, 512);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);
    
    mpz_mul(keys->n, p, q);
    
    mpz_t p1, q1;
    mpz_inits(p1, q1, NULL);
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    mpz_urandomm(keys->e, randState, phi);
    mpz_gcdext(keys->d, NULL, NULL, keys->e, phi);

    gmp_randclear(randState);
    mpz_clears(p, q, phi, p1, q1, NULL);
}

char* encrypt(const char* message, RSAKeys* keys) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    mpz_set_str(m, message, 10);
    mpz_powm(c, m, keys->e, keys->n);
    char* result = mpz_get_str(NULL, 10, c);
    mpz_clears(m, c, NULL);
    return result;
}

char* decrypt(const char* ciphertext, RSAKeys* keys) {
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    mpz_set_str(c, ciphertext, 10);
    mpz_powm(m, c, keys->d, keys->n);
    char* result = mpz_get_str(NULL, 10, m);
    mpz_clears(c, m, NULL);
    return result;
}

void test() {
    RSAKeys keys;
    mpz_inits(keys.n, keys.e, keys.d, NULL);
    generateKeys(&keys);

    const char* testMessages[] = {"Hello", "World", "RSA", "Encryption", "Test"};

    for (int i = 0; i < 5; ++i) {
        char* encrypted = encrypt(testMessages[i], &keys);
        char* decrypted = decrypt(encrypted, &keys);
        printf("Message: %s\n", testMessages[i]);
        printf("Encrypted: %s\n", encrypted);
        printf("Decrypted: %s\n", decrypted);
        free(encrypted);
        free(decrypted);
    }
    
    mpz_clears(keys.n, keys.e, keys.d, NULL);
}

int main() {
    test();
    return 0;
}