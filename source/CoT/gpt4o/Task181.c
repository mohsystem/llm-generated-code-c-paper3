#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    double balance;
    bool isOpen;
    pthread_mutex_t lock;
} BankAccount;

typedef struct {
    BankAccount** accounts;
    int size;
    pthread_mutex_t lock;
} Bank;

BankAccount* createBankAccount() {
    BankAccount* account = (BankAccount*)malloc(sizeof(BankAccount));
    account->balance = 0.0;
    account->isOpen = true;
    pthread_mutex_init(&account->lock, NULL);
    return account;
}

void deleteBankAccount(BankAccount* account) {
    pthread_mutex_destroy(&account->lock);
    free(account);
}

bool deposit(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen || amount < 0) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
    return true;
}

bool withdraw(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen || amount < 0 || account->balance < amount) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
    return true;
}

double getBalance(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    double balance = account->isOpen ? account->balance : -1;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

bool closeAccount(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        return false;
    }
    account->isOpen = false;
    pthread_mutex_unlock(&account->lock);
    return true;
}

Bank* createBank() {
    Bank* bank = (Bank*)malloc(sizeof(Bank));
    bank->accounts = (BankAccount**)malloc(sizeof(BankAccount*) * 100); // Assume max 100 accounts
    bank->size = 0;
    pthread_mutex_init(&bank->lock, NULL);
    return bank;
}

void deleteBank(Bank* bank) {
    for (int i = 0; i < bank->size; ++i) {
        deleteBankAccount(bank->accounts[i]);
    }
    free(bank->accounts);
    pthread_mutex_destroy(&bank->lock);
    free(bank);
}

int openAccount(Bank* bank) {
    pthread_mutex_lock(&bank->lock);
    int accountId = bank->size++;
    bank->accounts[accountId] = createBankAccount();
    pthread_mutex_unlock(&bank->lock);
    return accountId;
}

BankAccount* getAccount(Bank* bank, int accountId) {
    return bank->accounts[accountId];
}

int main() {
    Bank* bank = createBank();
    int acc1 = openAccount(bank);
    int acc2 = openAccount(bank);
    int acc3 = openAccount(bank);

    BankAccount* account1 = getAccount(bank, acc1);
    BankAccount* account2 = getAccount(bank, acc2);
    BankAccount* account3 = getAccount(bank, acc3);

    deposit(account1, 1000);
    deposit(account2, 500);

    printf("Account 1 Balance: %.2f\n", getBalance(account1));
    printf("Account 2 Balance: %.2f\n", getBalance(account2));
    printf("Account 3 Balance: %.2f\n", getBalance(account3));

    withdraw(account1, 100);
    withdraw(account2, 1000); // should fail
    deposit(account3, 200);

    printf("Account 1 Balance after withdrawal: %.2f\n", getBalance(account1));
    printf("Account 2 Balance after withdrawal: %.2f\n", getBalance(account2));
    printf("Account 3 Balance after deposit: %.2f\n", getBalance(account3));

    closeAccount(account3);
    printf("Account 3 closed: %d\n", !account3->isOpen);

    printf("Account 3 Balance after closure attempt: %.2f\n", getBalance(account3));
    printf("Deposit to closed account 3: %d\n", deposit(account3, 100)); // should fail

    deleteBank(bank);

    return 0;
}