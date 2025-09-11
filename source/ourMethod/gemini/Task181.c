#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    int accountNumber;
    double balance;
    bool isOpen;
    pthread_mutex_t lock;
} Account;

void account_init(Account *account, int accountNumber) {
    account->accountNumber = accountNumber;
    account->balance = 0.0;
    account->isOpen = true;
    pthread_mutex_init(&account->lock, NULL);
}

void account_deposit(Account *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        fprintf(stderr, "Error: Account is closed.\n");
        pthread_mutex_unlock(&account->lock);
        return; 
    }
    if (amount <= 0) {
        fprintf(stderr, "Error: Deposit amount must be positive.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
}

double account_withdraw(Account *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        fprintf(stderr, "Error: Account is closed.\n");
        pthread_mutex_unlock(&account->lock);
        return 0.0;
    }
    if (amount <= 0) {
        fprintf(stderr, "Error: Withdrawal amount must be positive.\n");
        pthread_mutex_unlock(&account->lock);
        return 0.0;
    }
    if (account->balance < amount) {
        fprintf(stderr, "Error: Insufficient balance.\n");
        pthread_mutex_unlock(&account->lock);
        return 0.0;
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
    return amount;
}

double account_get_balance(Account *account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        fprintf(stderr, "Error: Account is closed.\n");
        pthread_mutex_unlock(&account->lock);
        return 0.0;
    }
    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

void account_close(Account *account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        fprintf(stderr, "Error: Account is already closed.\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    account->isOpen = false;
    pthread_mutex_unlock(&account->lock);
}


int main() {
    Account account1;
    account_init(&account1, 1);
    account_deposit(&account1, 100);
    printf("Balance: %f\n", account_get_balance(&account1));
    account_withdraw(&account1, 50);
    printf("Balance: %f\n", account_get_balance(&account1));

    Account account2;
    account_init(&account2, 2);
    account_deposit(&account2, 500.25);
    printf("Account Number: %d, Balance: %f\n", account2.accountNumber, account_get_balance(&account2));
    account_close(&account2);

    Account account3;
    account_init(&account3, 3);
    account_deposit(&account3, 1500);
    printf("Balance: %f\n", account_get_balance(&account3));


    Account account4;
    account_init(&account4, 4);
    account_deposit(&account4, 10000);
    printf("Balance: %f\n", account_get_balance(&account4));
    account_withdraw(&account4, 2000);
    printf("Balance: %f\n", account_get_balance(&account4));

    Account account5;
    account_init(&account5, 5);
    account_deposit(&account5, 2342.32);
    printf("Balance: %f\n", account_get_balance(&account5));
    account_close(&account5);

    return 0;
}