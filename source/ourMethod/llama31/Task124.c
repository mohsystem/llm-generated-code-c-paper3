#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    char creditCardNumber[20];
    char securityCode[4];
} SensitiveData;

void printData(const SensitiveData* data) {
    printf("Name: %s\n", data->name);
    printf("Credit Card Number: %s\n", maskCreditCardNumber(data->creditCardNumber));
    printf("Security Code: %s\n", maskSecurityCode(data->securityCode));
}

char* maskCreditCardNumber(const char* creditCardNumber) {
    static char masked[20];
    strcpy(masked, "XXXX-XXXX-XXXX-");
    strcat(masked, creditCardNumber + strlen(creditCardNumber) - 4);
    return masked;
}

char* maskSecurityCode(const char* securityCode) {
    static char masked[5];
    strcpy(masked, "XXX-");
    strcat(masked, securityCode + strlen(securityCode) - 1);
    return masked;
}

int main() {
    // Example usage
    SensitiveData data;
    strcpy(data.name, "John Doe");
    strcpy(data.creditCardNumber, "1234-5678-9012-3456");
    strcpy(data.securityCode, "123");
    printData(&data);
    return 0;
}