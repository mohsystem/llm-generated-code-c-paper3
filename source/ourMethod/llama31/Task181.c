#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double balance;
    int isOpen;
    pthread_mutex_t mutex;
} BankAccount;

void* deposit(void* arg) {
    BankAccount* account = (BankAccount*)arg;
    double amount = 500.0;

    pthread_mutex_lock(&account->mutex);
    if (account->isOpen) {
        account->balance += amount;
        printf("Deposited: %.2f\n", amount);
        printf("Balance after deposit: %.2f\n", account->balance);
    } else {
        printf("Account is closed.\n");
    }
    pthread_mutex_unlock(&account->mutex);

    return NULL;
}

void* withdraw(void* arg) {
    BankAccount* account = (BankAccount*)arg;
    double amount = 200.0;

    pthread_mutex_lock(&account->mutex);
    if (account->isOpen) {
        if (account->balance >= amount) {
            account->balance -= amount;
            printf("Withdrawn: %.2f\n", amount);
            printf("Balance after withdrawal: %.2f\n", account->balance);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Account is closed.\n");
    }
    pthread_mutex_unlock(&account->mutex);

    return NULL;
}

void* closeAccount(void* arg) {
    BankAccount* account = (BankAccount*)arg;

    pthread_mutex_lock(&account->mutex);
    account->isOpen = 0;
    printf("Account closed.\n");
    pthread_mutex_unlock(&account->mutex);

    return NULL;
}

int main() {
    BankAccount account;
    account.balance = 1000.0;
    account.isOpen = 1;
    pthread_mutex_init(&account.mutex, NULL);

    pthread_t depositThread, withdrawalThread, closeThread;

    pthread_create(&depositThread, NULL, deposit, &account);
    pthread_create(&withdrawalThread, NULL, withdraw, &account);
    pthread_create(&closeThread, NULL, closeAccount, &account);

    pthread_join(depositThread, NULL);
    pthread_join(withdrawalThread, NULL);
    pthread_join(closeThread, NULL);

    pthread_mutex_destroy(&account.mutex);

    return 0;
}