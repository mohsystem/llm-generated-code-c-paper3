#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// ... (Same encryption function as in C++ example) ...

int main() {
    unsigned char key[32];
    RAND_bytes(key, 32);

    char *test_cases[] = {"Hello", "World", "Test", "Longer Test String", "Special Characters !@#$%^&*()"};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        char *test_case = test_cases[i];
        char *encrypted = (char *)malloc(strlen(test_case) * 2 + 1); // Allocate enough memory

        // Convert C string to std::string for encrypt function
        std::string cpp_test_case(test_case);
        std::string cpp_encrypted = encrypt(cpp_test_case, key);


        // Convert encrypted string back to C string
        strcpy(encrypted, cpp_encrypted.c_str());


        printf("Original: %s\n", test_case);
        printf("Encrypted: %s\n", encrypted);
        free(encrypted); // Free allocated memory
    }

    return 0;
}