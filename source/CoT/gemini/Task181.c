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

bool account_is_open(Account *account) {
    return account->isOpen;
}

void account_close(Account *account) {
    pthread_mutex_lock(&account->lock);
    account->isOpen = false;
    pthread_mutex_unlock(&account->lock);
}

double account_get_balance(Account *account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        // In C, throwing exceptions is less common; handle the error appropriately.
        fprintf(stderr, "Error: Account is closed.\n");
        return -1.0; // Or another suitable error indicator
    }
    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

void account_deposit(Account *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Error: Account is closed.\n");
        return;
    }
    if (amount <= 0) {
        pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Error: Deposit amount must be positive.\n");
        return;
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
}

void account_withdraw(Account *account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
         pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Error: Account is closed.\n");
        return;
    }
    if (amount <= 0) {
         pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Error: Withdrawal amount must be positive.\n");
        return;
    }
    if (account->balance < amount) {
         pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Error: Insufficient funds.\n");
        return;
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
}


int main() {
    Account account1;
    account_init(&account1, 12345);

    account_deposit(&account1, 100.00);
    printf("Balance after deposit: %.2f\n", account_get_balance(&account1));

    account_withdraw(&account1, 50.00);
    printf("Balance after withdrawal: %.2f\n", account_get_balance(&account1));

    account_close(&account1);

    account_deposit(&account1, 25.00); // This will print the error message.


    Account account2;
    account_init(&account2, 67890);
    account_deposit(&account2, 500.00);
    printf("Balance of account2: %.2f\n", account_get_balance(&account2));


    account_withdraw(&account2, 600.00);


    account_withdraw(&account2, 200.00);
    printf("Balance after withdrawal: %.2f\n", account_get_balance(&account2));
    return 0;
}