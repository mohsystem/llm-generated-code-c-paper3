#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Account {
    double balance;
    int isClosed;
    pthread_mutex_t lock;
} Account;

typedef struct Task181 {
    Account** accounts;
    size_t size;
    size_t capacity;
    pthread_mutex_t lock;
} Task181;

Task181* createBank() {
    Task181* bank = (Task181*)malloc(sizeof(Task181));
    bank->size = 0;
    bank->capacity = 10;
    bank->accounts = (Account**)malloc(sizeof(Account*) * bank->capacity);
    pthread_mutex_init(&bank->lock, NULL);
    return bank;
}

Account* createAccount(double initialBalance) {
    Account* account = (Account*)malloc(sizeof(Account));
    account->balance = initialBalance;
    account->isClosed = 0;
    pthread_mutex_init(&account->lock, NULL);
    return account;
}

int openAccount(Task181* bank, const char* id, double initialBalance) {
    pthread_mutex_lock(&bank->lock);
    if (bank->size >= bank->capacity) {
        bank->capacity *= 2;
        bank->accounts = (Account**)realloc(bank->accounts, sizeof(Account*) * bank->capacity);
    }
    for (size_t i = 0; i < bank->size; ++i) {
        if (bank->accounts[i] && strcmp(id, bank->accounts[i]->id) == 0) {
            pthread_mutex_unlock(&bank->lock);
            return 0;
        }
    }
    Account* account = createAccount(initialBalance);
    bank->accounts[bank->size++] = account;
    pthread_mutex_unlock(&bank->lock);
    return 1;
}

int closeAccount(Task181* bank, const char* id) {
    pthread_mutex_lock(&bank->lock);
    for (size_t i = 0; i < bank->size; ++i) {
        if (bank->accounts[i] && strcmp(id, bank->accounts[i]->id) == 0) {
            pthread_mutex_lock(&bank->accounts[i]->lock);
            if (!bank->accounts[i]->isClosed) {
                bank->accounts[i]->isClosed = 1;
                pthread_mutex_unlock(&bank->accounts[i]->lock);
                pthread_mutex_unlock(&bank->lock);
                return 1;
            }
            pthread_mutex_unlock(&bank->accounts[i]->lock);
            break;
        }
    }
    pthread_mutex_unlock(&bank->lock);
    return 0;
}

int deposit(Task181* bank, const char* id, double amount) {
    pthread_mutex_lock(&bank->lock);
    for (size_t i = 0; i < bank->size; ++i) {
        if (bank->accounts[i] && strcmp(id, bank->accounts[i]->id) == 0) {
            pthread_mutex_lock(&bank->accounts[i]->lock);
            if (!bank->accounts[i]->isClosed) {
                bank->accounts[i]->balance += amount;
                pthread_mutex_unlock(&bank->accounts[i]->lock);
                pthread_mutex_unlock(&bank->lock);
                return 1;
            }
            pthread_mutex_unlock(&bank->accounts[i]->lock);
            break;
        }
    }
    pthread_mutex_unlock(&bank->lock);
    return 0;
}

int withdraw(Task181* bank, const char* id, double amount) {
    pthread_mutex_lock(&bank->lock);
    for (size_t i = 0; i < bank->size; ++i) {
        if (bank->accounts[i] && strcmp(id, bank->accounts[i]->id) == 0) {
            pthread_mutex_lock(&bank->accounts[i]->lock);
            if (!bank->accounts[i]->isClosed && bank->accounts[i]->balance >= amount) {
                bank->accounts[i]->balance -= amount;
                pthread_mutex_unlock(&bank->accounts[i]->lock);
                pthread_mutex_unlock(&bank->lock);
                return 1;
            }
            pthread_mutex_unlock(&bank->accounts[i]->lock);
            break;
        }
    }
    pthread_mutex_unlock(&bank->lock);
    return 0;
}

double getBalance(Task181* bank, const char* id) {
    pthread_mutex_lock(&bank->lock);
    double balance = 0.0;
    for (size_t i = 0; i < bank->size; ++i) {
        if (bank->accounts[i] && strcmp(id, bank->accounts[i]->id) == 0) {
            pthread_mutex_lock(&bank->accounts[i]->lock);
            if (!bank->accounts[i]->isClosed) {
                balance = bank->accounts[i]->balance;
            }
            pthread_mutex_unlock(&bank->accounts[i]->lock);
            break;
        }
    }
    pthread_mutex_unlock(&bank->lock);
    return balance;
}

int main() {
    Task181* bank = createBank();
    openAccount(bank, "123", 1000);
    deposit(bank, "123", 500);
    withdraw(bank, "123", 200);
    closeAccount(bank, "123");
    withdraw(bank, "123", 100);
    openAccount(bank, "124", 1500);
    deposit(bank, "124", 300);
    closeAccount(bank, "124");
    deposit(bank, "124", 100);
    return 0;
}