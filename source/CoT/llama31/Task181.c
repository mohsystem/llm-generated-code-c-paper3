#include <stdio.h>
#include <pthread.h>

typedef struct {
    double balance;
    bool isOpen;
    pthread_mutex_t mutex;
} BankAccount;

void* open(void* account) {
    BankAccount* acc = (BankAccount*) account;
    pthread_mutex_lock(&acc->mutex);
    if (!acc->isOpen) {
        acc->isOpen = true;
        printf("Account opened.\n");
    } else {
        printf("Account is already open.\n");
    }
    pthread_mutex_unlock(&acc->mutex);
    return NULL;
}

void* close(void* account) {
    BankAccount* acc = (BankAccount*) account;
    pthread_mutex_lock(&acc->mutex);
    if (acc->isOpen) {
        acc->isOpen = false;
        printf("Account closed.\n");
    } else {
        printf("Account is already closed.\n");
    }
    pthread_mutex_unlock(&acc->mutex);
    return NULL;
}

void* deposit(void* data) {
    BankAccount* acc = ((void**) data)[0];
    double amount = *(double*)((void**) data)[1];
    pthread_mutex_lock(&acc->mutex);
    if (acc->isOpen) {
        acc->balance += amount;
        printf("Deposited: %.2f\n", amount);
        printf("Balance after deposit: %.2f\n", acc->balance);
    } else {
        printf("Operation failed: Account is closed.\n");
    }
    pthread_mutex_unlock(&acc->mutex);
    return NULL;
}

void* withdraw(void* data) {
    BankAccount* acc = ((void**) data)[0];
    double amount = *(double*)((void**) data)[1];
    pthread_mutex_lock(&acc->mutex);
    if (acc->isOpen) {
        if (acc->balance >= amount) {
            acc->balance -= amount;
            printf("Withdrawn: %.2f\n", amount);
            printf("Balance after withdrawal: %.2f\n", acc->balance);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Operation failed: Account is closed.\n");
    }
    pthread_mutex_unlock(&acc->mutex);
    return NULL;
}

int main() {
    BankAccount account;
    account.balance = 1000.0;
    account.isOpen = true;
    pthread_mutex_init(&account.mutex, NULL);

    // Test cases
    pthread_t thread;
    pthread_create(&thread, NULL, open, &account);
    pthread_join(thread, NULL);

    double amount = 500.0;
    void* data[] = {&account, &amount};
    pthread_create(&thread, NULL, deposit, data);
    pthread_join(thread, NULL);

    amount = 200.0;
    pthread_create(&thread, NULL, withdraw, data);
    pthread_join(thread, NULL);

    pthread_create(&thread, NULL, close, &account);
    pthread_join(thread, NULL);

    amount = 100.0;
    pthread_create(&thread, NULL, withdraw, data);
    pthread_join(thread, NULL);  // Should fail

    pthread_create(&thread, NULL, open, &account);
    pthread_join(thread, NULL);

    amount = 300.0;
    pthread_create(&thread, NULL, deposit, data);
    pthread_join(thread, NULL);

    return 0;
}