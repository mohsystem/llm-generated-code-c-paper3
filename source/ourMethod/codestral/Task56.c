#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char *base64_encode(const unsigned char *input, int length) {
   BIO *bmem, *b64;
   BUF_MEM *bptr;

   b64 = BIO_new(BIO_f_base64());
   bmem = BIO_new(BIO_s_mem());
   b64 = BIO_push(b64, bmem);
   BIO_write(b64, input, length);
   BIO_flush(b64);
   BIO_get_mem_ptr(b64, &bptr);

   char *buff = (char *)malloc(bptr->length);
   memcpy(buff, bptr->data, bptr->length-1);
   buff[bptr->length-1] = 0;

   BIO_free_all(b64);

   return buff;
}

char *generate_token() {
    unsigned char *randomBytes = malloc(24);
    RAND_bytes(randomBytes, 24);
    char *token = base64_encode(randomBytes, 24);
    free(randomBytes);
    return token;
}

int main() {
    char *token = generate_token();
    printf("%s\n", token);
    free(token);
    return 0;
}