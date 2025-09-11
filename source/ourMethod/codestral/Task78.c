// C does not have built-in support for cryptography, so you need to use a library like OpenSSL.
// This is a simplified example and does not include error handling.
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bn, NULL);

    FILE *fp = fopen("private.pem", "wb");
    PEM_write_RSAPrivateKey(fp, rsa, NULL, NULL, 0, NULL, NULL);
    fclose(fp);

    RSA_free(rsa);
    BN_free(bn);
    return 0;
}