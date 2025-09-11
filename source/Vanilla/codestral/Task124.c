#include <stdio.h>
#include <string.h>

#define ENCRYPTION_KEY 0x5

void encrypt(const char* data, char* encryptedData) {
    size_t length = strlen(data);
    for (size_t i = 0; i < length; i++) {
        encryptedData[i] = data[i] ^ ENCRYPTION_KEY;
    }
    encryptedData[length] = '\0';
}

int main() {
    const char* creditCardNumber = "1234567890123456";
    char encryptedCreditCardNumber[17];
    encrypt(creditCardNumber, encryptedCreditCardNumber);
    printf("Encrypted Credit Card Number: %s\n", encryptedCreditCardNumber);
    return 0;
}