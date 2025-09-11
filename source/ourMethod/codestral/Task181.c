#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    int id;
    double balance;
    bool is_open;
    pthread_mutex_t lock;
} BankAccount;

void bank_account_init(BankAccount *account, int id) {
    account->id = id;
    account->balance = 0;
    account->is_open = true;
    pthread_mutex_init(&account->lock, NULL);
}

void deposit(BankAccount *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->is_open) {
        fprintf(stderr, "Account is closed.\n");
        exit(EXIT_FAILURE);
    }
    if (amount <= 0) {
        fprintf(stderr, "Deposit amount must be positive.\n");
        exit(EXIT_FAILURE);
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
}

void withdraw(BankAccount *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->is_open) {
        fprintf(stderr, "Account is closed.\n");
        exit(EXIT_FAILURE);
    }
    if (amount <= 0) {
        fprintf(stderr, "Withdrawal amount must be positive.\n");
        exit(EXIT_FAILURE);
    }
    if (amount > account->balance) {
        fprintf(stderr, "Insufficient balance.\n");
        exit(EXIT_FAILURE);
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
}

void close_account(BankAccount *account) {
    pthread_mutex_lock(&account->lock);
    account->is_open = false;
    pthread_mutex_unlock(&account->lock);
}

double get_balance(BankAccount *account) {
    pthread_mutex_lock(&account->lock);
    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

int main() {
    BankAccount account1;
    bank_account_init(&account1, 1);
    deposit(&account1, 100);
    withdraw(&account1, 50);
    printf("Balance: %.2f\n", get_balance(&account1));
    close_account(&account1);
    deposit(&account1, 100);
    return 0;
}