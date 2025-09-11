#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int accountId;
    double balance;
    int isClosed;
} Account;

typedef struct {
    Account* accounts;
    int nextAccountId;
    pthread_mutex_t lock;
} Task181;

Account* createAccount(int accountId, double initialBalance) {
    Account* account = malloc(sizeof(Account));
    account->accountId = accountId;
    account->balance = initialBalance;
    account->isClosed = 0;
    return account;
}

void closeAccount(Account* account) {
    account->isClosed = 1;
}

void deposit(Account* account, double amount) {
    account->balance += amount;
}

int withdraw(Account* account, double amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        return 1;
    }
    return 0;
}

double getBalance(Account* account) {
    return account->balance;
}

Task181* createBank() {
    Task181* bank = malloc(sizeof(Task181));
    bank->accounts = malloc(sizeof(Account) * 100);
    bank->nextAccountId = 1;
    pthread_mutex_init(&bank->lock, NULL);
    return bank;
}

int openAccount(Task181* bank, double initialBalance) {
    pthread_mutex_lock(&bank->lock);
    int accountId = bank->nextAccountId++;
    bank->accounts[accountId] = *createAccount(accountId, initialBalance);
    pthread_mutex_unlock(&bank->lock);
    return accountId;
}

void closeAccountById(Task181* bank, int accountId) {
    pthread_mutex_lock(&bank->lock);
    if (accountId < bank->nextAccountId && !bank->accounts[accountId].isClosed) {
        closeAccount(&bank->accounts[accountId]);
    }
    pthread_mutex_unlock(&bank->lock);
}

int depositAmount(Task181* bank, int accountId, double amount) {
    pthread_mutex_lock(&bank->lock);
    if (accountId < bank->nextAccountId && !bank->accounts[accountId].isClosed) {
        deposit(&bank->accounts[accountId], amount);
        pthread_mutex_unlock(&bank->lock);
        return 1;
    }
    pthread_mutex_unlock(&bank->lock);
    return 0;
}

int withdrawAmount(Task181* bank, int accountId, double amount) {
    pthread_mutex_lock(&bank->lock);
    if (accountId < bank->nextAccountId && !bank->accounts[accountId].isClosed) {
        int success = withdraw(&bank->accounts[accountId], amount);
        pthread_mutex_unlock(&bank->lock);
        return success;
    }
    pthread_mutex_unlock(&bank->lock);
    return 0;
}

double getBalanceById(Task181* bank, int accountId) {
    pthread_mutex_lock(&bank->lock);
    if (accountId < bank->nextAccountId && !bank->accounts[accountId].isClosed) {
        double balance = getBalance(&bank->accounts[accountId]);
        pthread_mutex_unlock(&bank->lock);
        return balance;
    }
    pthread_mutex_unlock(&bank->lock);
    return -1;
}

int main() {
    Task181* bank = createBank();
    int account1 = openAccount(bank, 1000);
    int account2 = openAccount(bank, 500);

    depositAmount(bank, account1, 200);
    withdrawAmount(bank, account2, 100);

    printf("Account 1 balance: %.2f\n", getBalanceById(bank, account1));
    printf("Account 2 balance: %.2f\n", getBalanceById(bank, account2));

    closeAccountById(bank, account1);
    printf("Account 1 balance after close: %.2f\n", getBalanceById(bank, account1));

    free(bank->accounts);
    pthread_mutex_destroy(&bank->lock);
    free(bank);
    return 0;
}