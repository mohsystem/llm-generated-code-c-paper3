#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    double balance;
    int isOpen;
    pthread_mutex_t lock;
} BankAccount;

void initAccount(BankAccount* account) {
    account->balance = 0.0;
    account->isOpen = 1;
    pthread_mutex_init(&account->lock, NULL);
}

int deposit(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        return 0;
    }
    if (amount < 0) {
        pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Amount must be positive\n");
        return 0;
    }
    account->balance += amount;
    pthread_mutex_unlock(&account->lock);
    return 1;
}

int withdraw(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        return 0;
    }
    if (amount < 0 || amount > account->balance) {
        pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Invalid amount\n");
        return 0;
    }
    account->balance -= amount;
    pthread_mutex_unlock(&account->lock);
    return 1;
}

double getBalance(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        fprintf(stderr, "Account is closed\n");
        return -1;
    }
    double balance = account->balance;
    pthread_mutex_unlock(&account->lock);
    return balance;
}

int closeAccount(BankAccount* account) {
    pthread_mutex_lock(&account->lock);
    if (!account->isOpen) {
        pthread_mutex_unlock(&account->lock);
        return 0;
    }
    account->isOpen = 0;
    pthread_mutex_unlock(&account->lock);
    return 1;
}

typedef struct {
    BankAccount* accounts;
    int accountCounter;
    int maxAccounts;
    pthread_mutex_t lock;
} Bank;

void initBank(Bank* bank, int maxAccounts) {
    bank->accounts = (BankAccount*)malloc(maxAccounts * sizeof(BankAccount));
    bank->accountCounter = 0;
    bank->maxAccounts = maxAccounts;
    pthread_mutex_init(&bank->lock, NULL);
}

int openAccount(Bank* bank) {
    pthread_mutex_lock(&bank->lock);
    if (bank->accountCounter >= bank->maxAccounts) {
        pthread_mutex_unlock(&bank->lock);
        fprintf(stderr, "Maximum accounts reached\n");
        return -1;
    }
    initAccount(&bank->accounts[bank->accountCounter]);
    int accountId = bank->accountCounter++;
    pthread_mutex_unlock(&bank->lock);
    return accountId;
}

int bankCloseAccount(Bank* bank, int accountId) {
    if (accountId < 0 || accountId >= bank->accountCounter) {
        fprintf(stderr, "Invalid account ID\n");
        return 0;
    }
    return closeAccount(&bank->accounts[accountId]);
}

int bankDeposit(Bank* bank, int accountId, double amount) {
    if (accountId < 0 || accountId >= bank->accountCounter) {
        fprintf(stderr, "Invalid account ID\n");
        return 0;
    }
    return deposit(&bank->accounts[accountId], amount);
}

int bankWithdraw(Bank* bank, int accountId, double amount) {
    if (accountId < 0 || accountId >= bank->accountCounter) {
        fprintf(stderr, "Invalid account ID\n");
        return 0;
    }
    return withdraw(&bank->accounts[accountId], amount);
}

double bankGetBalance(Bank* bank, int accountId) {
    if (accountId < 0 || accountId >= bank->accountCounter) {
        fprintf(stderr, "Invalid account ID\n");
        return -1;
    }
    return getBalance(&bank->accounts[accountId]);
}

int main() {
    Bank bank;
    initBank(&bank, 10);

    // Test cases
    int acc1 = openAccount(&bank);
    int acc2 = openAccount(&bank);
    int acc3 = openAccount(&bank);
    int acc4 = openAccount(&bank);
    int acc5 = openAccount(&bank);

    printf("Acc1 Deposit 100: %d\n", bankDeposit(&bank, acc1, 100));
    printf("Acc2 Deposit 200: %d\n", bankDeposit(&bank, acc2, 200));
    printf("Acc1 Withdraw 50: %d\n", bankWithdraw(&bank, acc1, 50));
    printf("Acc1 Balance: %.2f\n", bankGetBalance(&bank, acc1));
    printf("Close Acc3: %d\n", bankCloseAccount(&bank, acc3));
    printf("Acc3 Withdraw 50: %d\n", bankWithdraw(&bank, acc3, 50)); // Should fail

    free(bank.accounts);
    return 0;
}