#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define STORED_PASSWORD_FILE "stored_password.txt"
#define SALT "a_random_salt"
#define MAX_PASSWORD_LENGTH 100


char* hash_password(const char* password) {
    char salted_password[200]; // Increased size to accommodate salt and password
    snprintf(salted_password, sizeof(salted_password), "%s%s", SALT, password); 

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);

    static char hex_str[SHA256_DIGEST_LENGTH * 2 + 1];  // Static to persist beyond function scope
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_str + i * 2, "%02x", hash[i]);
    }
    return hex_str;
}

bool compare_passwords(const char* entered_password) {
    FILE* file = fopen(STORED_PASSWORD_FILE, "r");
    if (file == NULL) {
        return false;
    }

    char stored_hashed_password[200];  // Increased size
    fgets(stored_hashed_password, sizeof(stored_hashed_password), file);

    // Remove trailing newline from fgets, if any
    stored_hashed_password[strcspn(stored_hashed_password, "\n")] = 0;

    fclose(file);

    char* entered_hashed_password = hash_password(entered_password);
    return strcmp(stored_hashed_password, entered_hashed_password) == 0;
}


int main() {
    const char* test_password = "password123";
    FILE *fp = fopen(STORED_PASSWORD_FILE, "w");
    if (fp != NULL) {
        fprintf(fp, "%s", hash_password(test_password));
        fclose(fp);
    } else {
        perror("Error opening file for writing");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        char entered_password[MAX_PASSWORD_LENGTH];
        printf("Enter your password: ");

        // Use fgets to prevent buffer overflow
        if(fgets(entered_password, sizeof(entered_password), stdin)){
          entered_password[strcspn(entered_password, "\n")] = 0; // remove trailing newline
        } else {
          fprintf(stderr,"Error reading password");
          return 1;
        }

        if (compare_passwords(entered_password)) {
            printf("Test case %d: Password matches.\n", i + 1);
        } else {
            printf("Test case %d: Password does not match.\n", i + 1);
        }
    }
    return 0;
}