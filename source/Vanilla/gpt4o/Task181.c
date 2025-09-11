#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct Account {
    double balance;
    bool isOpen;
    pthread_mutex_t mtx;
} Account;

typedef struct Bank {
    Account** accounts;
    int accountIdCounter;
    pthread_mutex_t globalLock;
} Bank;

Bank* createBank() {
    Bank* bank = (Bank*)malloc(sizeof(Bank));
    bank->accounts = (Account**)malloc(sizeof(Account*) * 1000); // initial capacity
    bank->accountIdCounter = 0;
    pthread_mutex_init(&bank->globalLock, NULL);
    return bank;
}

int openAccount(Bank* bank) {
    pthread_mutex_lock(&bank->globalLock);
    int accountId = bank->accountIdCounter++;
    bank->accounts[accountId] = (Account*)malloc(sizeof(Account));
    bank->accounts[accountId]->balance = 0.0;
    bank->accounts[accountId]->isOpen = true;
    pthread_mutex_init(&bank->accounts[accountId]->mtx, NULL);
    pthread_mutex_unlock(&bank->globalLock);
    return accountId;
}

bool closeAccount(Bank* bank, int accountId) {
    if (accountId >= bank->accountIdCounter) return false;
    pthread_mutex_lock(&bank->accounts[accountId]->mtx);
    if (!bank->accounts[accountId]->isOpen) {
        pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
        return false;
    }
    bank->accounts[accountId]->isOpen = false;
    pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
    return true;
}

bool deposit(Bank* bank, int accountId, double amount) {
    if (accountId >= bank->accountIdCounter || amount < 0) return false;
    pthread_mutex_lock(&bank->accounts[accountId]->mtx);
    if (!bank->accounts[accountId]->isOpen) {
        pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
        return false;
    }
    bank->accounts[accountId]->balance += amount;
    pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
    return true;
}

bool withdraw(Bank* bank, int accountId, double amount) {
    if (accountId >= bank->accountIdCounter || amount < 0) return false;
    pthread_mutex_lock(&bank->accounts[accountId]->mtx);
    if (!bank->accounts[accountId]->isOpen || bank->accounts[accountId]->balance < amount) {
        pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
        return false;
    }
    bank->accounts[accountId]->balance -= amount;
    pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
    return true;
}

double getBalance(Bank* bank, int accountId) {
    if (accountId >= bank->accountIdCounter) return -1;
    pthread_mutex_lock(&bank->accounts[accountId]->mtx);
    double balance = bank->accounts[accountId]->isOpen ? bank->accounts[accountId]->balance : -1;
    pthread_mutex_unlock(&bank->accounts[accountId]->mtx);
    return balance;
}

int main() {
    Bank* bank = createBank();
    
    int acc1 = openAccount(bank);
    int acc2 = openAccount(bank);
    
    printf("%d\n", deposit(bank, acc1, 1000)); // true
    printf("%d\n", withdraw(bank, acc1, 500)); // true
    printf("%.1f\n", getBalance(bank, acc1)); // 500.0
    
    printf("%d\n", deposit(bank, acc2, 200)); // true
    printf("%.1f\n", getBalance(bank, acc2)); // 200.0
    
    printf("%d\n", closeAccount(bank, acc1)); // true
    printf("%d\n", withdraw(bank, acc1, 100)); // false
    
    printf("%.1f\n", getBalance(bank, acc1)); // -1
    
    // Free allocated memory
    for (int i = 0; i < bank->accountIdCounter; i++) {
        pthread_mutex_destroy(&bank->accounts[i]->mtx);
        free(bank->accounts[i]);
    }
    free(bank->accounts);
    pthread_mutex_destroy(&bank->globalLock);
    free(bank);
    
    return 0;
}