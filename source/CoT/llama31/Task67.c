// Note: This example is highly simplified and does not include actual database interaction.
// In C, you would typically use a library like MySQL's C API or another database library.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[100];
    char name[100];
    char email[100];
} Customer;

Customer getCustomerInformation(const char* customerUsername) {
    // Simulated database retrieval for demonstration purposes only.
    Customer customer;
    strcpy(customer.username, customerUsername);
    strcpy(customer.name, "John Doe");
    strcpy(customer.email, "john.doe@example.com");
    return customer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./task67 <customerusername>\n");
        return 1;
    }
    const char* customerUsername = argv[1];
    Customer customer = getCustomerInformation(customerUsername);
    printf("Customer Information:\n");
    printf("Username: %s\n", customer.username);
    printf("Name: %s\n", customer.name);
    printf("Email: %s\n", customer.email);
    return 0;
}