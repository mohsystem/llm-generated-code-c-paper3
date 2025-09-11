#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    char* accountId;
    double balance;
    bool isOpen;
    pthread_mutex_t lock;
} Account;

Account create_account(char* accountId, double initialBalance) {
    Account account;
    account.accountId = accountId;
    account.balance = initialBalance;
    account.isOpen = true;
    pthread_mutex_init(&account.lock, NULL);
    return account;
}

bool account_is_open(Account* account) {
    return account->isOpen;
}

void close_account(Account* account) {
    pthread_mutex_lock(&account->lock);
    account->isOpen = false;
    pthread_mutex_unlock(&account->lock);
}

double get_balance(Account* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        // In C, handling exceptions like in C++ isn't directly possible. 
        // Here, we print an error message and return a special value to indicate an issue.
        fprintf(stderr, "Error: Account is closed\n");
        return -1.0; // Indicate an error
    }
    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}


void deposit(Account* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        fprintf(stderr, "Error: Account is closed\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    if (amount <= 0) {
        fprintf(stderr, "Error: Deposit amount must be positive\n");
         pthread_mutex_unlock(&account->lock);
        return;
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
}

void withdraw(Account* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
         fprintf(stderr, "Error: Account is closed\n");
         pthread_mutex_unlock(&account->lock);
         return;
    }
    if (amount <= 0) {
        fprintf(stderr, "Error: Withdrawal amount must be positive\n");
        pthread_mutex_unlock(&account->lock);
        return;
    }
    if (account->balance < amount) {
       fprintf(stderr, "Error: Insufficient funds\n");
       pthread_mutex_unlock(&account->lock);
       return;
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
}



int main() {
    Account account1 = create_account("123", 1000.00);

    // Test case 1: Deposit
    deposit(&account1, 500.00);
    printf("Balance after deposit: %.2f\n", get_balance(&account1));

    // Test case 2: Withdrawal
    withdraw(&account1, 200.00);
    printf("Balance after withdrawal: %.2f\n", get_balance(&account1));

    // Test case 3: Close account
    close_account(&account1);
    printf("Account closed: %d\n", !account_is_open(&account1));

    // Test case 4: Attempt deposit on closed account
    deposit(&account1, 100.00); // Expect error message

    // Test case 5: Attempt withdrawal on closed account
    withdraw(&account1, 50.00); // Expect error message

    // Destroy the mutex (important for cleanup)
    pthread_mutex_destroy(&account1.lock); 

    return 0;
}