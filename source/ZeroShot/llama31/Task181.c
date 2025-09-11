#include <stdio.h>
#include <pthread.h>

typedef struct {
    double balance;
    int isOpen;
    pthread_mutex_t mutex;
} BankAccount;

void initBankAccount(BankAccount* account, double initialBalance) {
    account->balance = initialBalance;
    account->isOpen = 1;
    pthread_mutex_init(&account->mutex, NULL);
}

void openAccount(BankAccount* account) {
    pthread_mutex_lock(&account->mutex);
    account->isOpen = 1;
    pthread_mutex_unlock(&account->mutex);
}

void closeAccount(BankAccount* account) {
    pthread_mutex_lock(&account->mutex);
    account->isOpen = 0;
    pthread_mutex_unlock(&account->mutex);
}

void deposit(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->mutex);
    if (!account->isOpen) {
        printf("Account is closed. Deposit failed.\n");
        pthread_mutex_unlock(&account->mutex);
        return;
    }
    account->balance += amount;
    printf("Deposit: %.2f\n", amount);
    printf("Balance after deposit: %.2f\n", account->balance);
    pthread_mutex_unlock(&account->mutex);
}

void withdraw(BankAccount* account, double amount) {
    pthread_mutex_lock(&account->mutex);
    if (!account->isOpen) {
        printf("Account is closed. Withdrawal failed.\n");
        pthread_mutex_unlock(&account->mutex);
        return;
    }
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrawal: %.2f\n", amount);
        printf("Balance after withdrawal: %.2f\n", account->balance);
    } else {
        printf("Insufficient funds. Withdrawal cancelled.\n");
    }
    pthread_mutex_unlock(&account->mutex);
}

void* threadFunction(void* arg) {
    BankAccount* account = (BankAccount*)arg;
    double amount = *(double*)((char*)arg + sizeof(BankAccount*));
    if (*(int*)((char*)arg + sizeof(BankAccount*) + sizeof(double))) {
        deposit(account, amount);
    } else {
        withdraw(account, amount);
    }
    return NULL;
}

int main() {
    BankAccount account;
    initBankAccount(&account, 1000.0);

    double depositAmount = 500.0;
    double withdrawalAmount = 200.0;

    pthread_t depositThread, withdrawalThread, closeThread;

    int depositFlag = 1;
    int closeFlag = 0;

    pthread_create(&depositThread, NULL, threadFunction, (void*)&account);
    pthread_create(&withdrawalThread, NULL, threadFunction, (void*)&account);

    closeAccount(&account);

    pthread_join(depositThread, NULL);
    pthread_join(withdrawalThread, NULL);

    deposit(&account, 100.0);  // This should fail because the account is closed

    return 0;
}