#include <stdio.h>
#include <pthread.h>

typedef struct {
    double balance;
    int isOpen;
    pthread_mutex_t lock;
} BankAccount;

void initBankAccount(BankAccount* account) {
    account->balance = 0.0;
    account->isOpen = 1;
    pthread_mutex_init(&account->lock, NULL);
}

void openAccount(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        printf("Account is already open.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    account->isOpen = 1;
    printf("Account opened successfully.\n");
    pthread_mutex_unlock(&account->lock);
}

void closeAccount(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        printf("Account is already closed.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    account->isOpen = 0;
    printf("Account closed successfully.\n");
    pthread_mutex_unlock(&account->lock);
}

void deposit(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        printf("Account is closed. Cannot deposit.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    account->balance += amount;
    printf("Deposited: %f\n", amount);
    printf("Balance after deposit: %f\n", account->balance);
    pthread_mutex_unlock(&account->lock);
}

void withdraw(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        printf("Account is closed. Cannot withdraw.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrawn: %f\n", amount);
        printf("Balance after withdrawal: %f\n", account->balance);
    } else {
        printf("Insufficient funds. Withdrawal cancelled.\n");
    }
    pthread_mutex_unlock(&account->lock);
}

int main() {
    BankAccount account;
    initBankAccount(&account);

    // Test cases
    openAccount(&account);
    deposit(&account, 1000);
    withdraw(&account, 500);
    closeAccount(&account);
    withdraw(&account, 500);  // Should fail because account is closed
    openAccount(&account);  // Should fail because account is already closed

    return 0;
}