
// Note: Thread-safe banking implementation in C would be quite complex due to lack of built-in 
// synchronization primitives and object-oriented features. Below is a simplified version using
// POSIX threads and mutex locks. This is not recommended for production use.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100
#define MAX_ID_LENGTH 20

typedef struct {
    char account_id[MAX_ID_LENGTH];
    double balance;
    bool is_active;
    pthread_mutex_t lock;
} BankAccount;

typedef struct {
    BankAccount accounts[MAX_ACCOUNTS];
    int count;
    pthread_mutex_t global_lock;
} Bank;

Bank bank;

void init_bank() {
    bank.count = 0;
    pthread_mutex_init(&bank.global_lock, NULL);
}

bool open_account(const char* account_id, double initial_balance) {
    if (!account_id || strlen(account_id) >= MAX_ID_LENGTH || initial_balance < 0) {
        return false;
    }

    pthread_mutex_lock(&bank.global_lock);
    
    if (bank.count >= MAX_ACCOUNTS) {
        pthread_mutex_unlock(&bank.global_lock);
        return false;
    }

    for (int i = 0; i < bank.count; i++) {
        if (strcmp(bank.accounts[i].account_id, account_id) == 0) {
            pthread_mutex_unlock(&bank.global_lock);
            return false;
        }
    }

    BankAccount* account = &bank.accounts[bank.count];
    strncpy(account->account_id, account_id, MAX_ID_LENGTH - 1);
    account->account_id[MAX_ID_LENGTH - 1] = '\\0';
    account->balance = initial_balance;
    account->is_active = true;
    pthread_mutex_init(&account->lock, NULL);
    bank.count++;

    pthread_mutex_unlock(&bank.global_lock);
    return true;
}

BankAccount* find_account(const char* account_id) {
    for (int i = 0; i < bank.count; i++) {
        if (strcmp(bank.accounts[i].account_id, account_id) == 0) {
            return &bank.accounts[i];
        }
    }
    return NULL;
}

bool deposit(BankAccount* account, double amount) {
    if (!account || amount <= 0) {
        return false;
    }

    pthread_mutex_lock(&account->lock);
    
    if (!account->is_active) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }

    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
    return true;
}

bool withdraw(BankAccount* account, double amount) {
    if (!account || amount <= 0) {
        return false;
    }

    pthread_mutex_lock(&account->lock);
    
    if (!account->is_active || account->balance < amount) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }

    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
    return true;
}

bool close_account(BankAccount* account) {
    if (!account) {
        return false;
    }

    pthread_mutex_lock(&account->lock);
    
    if (!account->is_active) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }

    account->is_active = false;
    pthread_mutex_unlock(&account->lock);
    return true;
}

double get_balance(BankAccount* account) {
    if (!account) {
        return -1;
    }

    pthread_mutex_lock(&account->lock);
    
    if (!account->is_active) {
        pthread_mutex_unlock(&account->lock);
        return -1;
    }

    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

int main() {
    init_bank();

    // Test case 1: Open account
    printf("Test 1: %d\\n", open_account("ACC1", 1000.0));  // 1

    // Test case 2: Deposit
    BankAccount* acc1 = find_account("ACC1");
    printf("Test 2: %d\\n", deposit(acc1, 500.0));  // 1
    printf("Balance: %.2f\\n", get_balance(acc1));   // 1500.0

    // Test case 3: Withdraw
    printf("Test 3: %d\\n", withdraw(acc1, 200.0)); // 1
    printf("Balance: %.2f\\n", get_balance(acc1));   // 1300.0

    // Test case 4: Close account
    printf("Test 4: %d\\n", close_account(acc1));   // 1

    // Test case 5: Operation on closed account
    printf("Test 5: %d\\n", deposit(acc1, 100.0));  // 0

    return 0;
}
