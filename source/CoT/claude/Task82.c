
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define BASE64_SIZE(x) ((((x) + 2) / 3) * 4 + 1)

static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void generate_salt(unsigned char *salt) {
    RAND_bytes(salt, SALT_SIZE);
}

char *base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_length = BASE64_SIZE(input_length);
    char *encoded_data = malloc(output_length);
    if (encoded_data == NULL) return NULL;

    size_t i, j;
    int pad = input_length % 3;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    size_t pos = 0;
    for (i = 0; i < input_length - pad; i += 3) {
        char_array_3[0] = data[i];
        char_array_3[1] = data[i + 1];
        char_array_3[2] = data[i + 2];

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < 4; j++)
            encoded_data[pos++] = base64_chars[char_array_4[j]];
    }

    if (pad > 0) {
        for (i = 0; i < pad; i++)
            char_array_3[i] = data[input_length - pad + i];
        for (i = pad; i < 3; i++)
            char_array_3[i] = 0;

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (i = 0; i < pad + 1; i++)
            encoded_data[pos++] = base64_chars[char_array_4[i]];
        for (i = pad + 1; i < 4; i++)
            encoded_data[pos++] = '=';
    }

    encoded_data[pos] = 0;
    return encoded_data;
}

char *hash_password(const char *password, const unsigned char *salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    return base64_encode(hash, SHA256_DIGEST_LENGTH);
}

int main() {
    const char *passwords[] = {
        "password123",
        "SecureP@ssw0rd",
        "MyP@ssw0rd123!",
        "C0mpl3x1ty",
        "S@lt3dH@sh"
    };
    
    for(int i = 0; i < 5; i++) {
        unsigned char salt[SALT_SIZE];
        generate_salt(salt);
        
        char *hashed_password = hash_password(passwords[i], salt);
        char *encoded_salt = base64_encode(salt, SALT_SIZE);
        
        printf("Password: %s\\n", passwords[i]);
        printf("Salt: %s\\n", encoded_salt);
        printf("Hashed: %s\\n\\n", hashed_password);
        
        free(hashed_password);
        free(encoded_salt);
    }
    
    return 0;
}
