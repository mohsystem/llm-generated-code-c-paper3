#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void generate_key_pair(mpz_t n, mpz_t e, mpz_t d, unsigned long int bit_length) {
    gmp_randstate_t state;
    mpz_t p, q, phi;

    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());

    mpz_init(p);
    mpz_init(q);
    mpz_init(phi);
    mpz_urandomb(p, state, bit_length / 2);
    mpz_urandomb(q, state, bit_length / 2);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    mpz_mul(n, p, q);

    mpz_t p_minus_1, q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi, p_minus_1, q_minus_1);

    mpz_set_ui(e, 65537);
    mpz_invert(d, e, phi);

    mpz_clears(p, q, phi, p_minus_1, q_minus_1, NULL);
}

void encrypt(mpz_t ciphertext, const mpz_t plaintext, const mpz_t e, const mpz_t n) {
    mpz_powm(ciphertext, plaintext, e, n);
}

void decrypt(mpz_t plaintext, const mpz_t ciphertext, const mpz_t d, const mpz_t n) {
    mpz_powm(plaintext, ciphertext, d, n);
}

int main() {
    mpz_t n, e, d;
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);

    generate_key_pair(n, e, d, 1024);

    unsigned long int messages[5] = {123, 456, 789, 101112, 131415};
    for (int i = 0; i < 5; i++) {
        mpz_t plaintext, ciphertext, decrypted;
        mpz_init_set_ui(plaintext, messages[i]);
        mpz_init(ciphertext);
        mpz_init(decrypted);

        encrypt(ciphertext, plaintext, e, n);
        decrypt(decrypted, ciphertext, d, n);

        gmp_printf("Message: %Zd\n", plaintext);
        gmp_printf("Encrypted: %Zd\n", ciphertext);
        gmp_printf("Decrypted: %Zd\n\n", decrypted);

        mpz_clears(plaintext, ciphertext, decrypted, NULL);
    }

    mpz_clears(n, e, d, NULL);
    return 0;
}