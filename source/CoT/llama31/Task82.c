#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPasswordWithSalt(const char* password, const char* salt, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (char*)(password), strlen(password));
    SHA256_Update(&sha256, (char*)(salt), strlen(salt));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char password[] = "farm1990M0O";
    char salt[] = "f1nd1ngn3m0";
    char hashString[SHA256_DIGEST_LENGTH * 2 + 1];
    hashPasswordWithSalt(password, salt, hashString);
    printf("Hash of password with salt: %s\n", hashString);

    // Test cases
    strcpy(hashString, "");
    hashPasswordWithSalt("password123", "salt123", hashString);
    printf("Hash of 'password123' with 'salt123': %s\n", hashString);

    strcpy(hashString, "");
    hashPasswordWithSalt("testpassword", "testsalt", hashString);
    printf("Hash of 'testpassword' with 'testsalt': %s\n", hashString);

    strcpy(hashString, "");
    hashPasswordWithSalt("userpassword", "usersalt", hashString);
    printf("Hash of 'userpassword' with 'usersalt': %s\n", hashString);

    strcpy(hashString, "");
    hashPasswordWithSalt("adminpassword", "adminsalt", hashString);
    printf("Hash of 'adminpassword' with 'adminsalt': %s\n", hashString);

    strcpy(hashString, "");
    hashPasswordWithSalt("guestpassword", "guestsalt", hashString);
    printf("Hash of 'guestpassword' with 'guestsalt': %s\n", hashString);

    return 0;
}