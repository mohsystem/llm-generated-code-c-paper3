#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Base64 encoding table
char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function to encode data to Base64
char *base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);

    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        unsigned char char_array_3[3] = {0};
        unsigned char char_array_4[4] = {0};

        for (int k = 0; k < 3; k++) {
            if (i < input_length) {
                char_array_3[k] = data[i++];
            }
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (int k = 0; k < 4; k++) {
            encoded_data[j++] = base64_chars[char_array_4[k]];
        }
    }

    // Add padding if necessary
    for (int i = 0; i < (3 - (input_length % 3)) % 3; i++) {
        encoded_data[output_length - 1 - i] = '=';
    }

    encoded_data[output_length] = '\0';
    return encoded_data;
}



// Function to generate a secure random token
char *generateToken() {
    unsigned char tokenBytes[32];
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < 32; i++) {
        tokenBytes[i] = rand() % 256; // Generate random bytes
    }

    char *encodedToken = base64_encode(tokenBytes, sizeof(tokenBytes));


     // URL safe modifications
    for (size_t i = 0; encodedToken[i] != '\0'; i++) {
        if (encodedToken[i] == '+') {
            encodedToken[i] = '-';
        } else if (encodedToken[i] == '/') {
            encodedToken[i] = '_';
        }
    }
    //Remove padding
    encodedToken[strcspn(encodedToken, "=")] = 0;
    return encodedToken;
}

int main() {
    printf("Test case 1: %s\n", generateToken());
    printf("Test case 2: %s\n", generateToken());
    printf("Test case 3: %s\n", generateToken());
    printf("Test case 4: %s\n", generateToken());
    printf("Test case 5: %s\n", generateToken());

    return 0;
}