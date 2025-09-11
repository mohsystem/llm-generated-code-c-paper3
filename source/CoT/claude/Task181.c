
// Note: C doesn't have built-in support for threading and objects\n// Here's a simplified version without thread safety

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100
#define ACCOUNT_ID_LENGTH 20

typedef struct {
    char accountId[ACCOUNT_ID_LENGTH];
    double balance;
    bool isOpen;
} BankAccount;

typedef struct {
    BankAccount accounts[MAX_ACCOUNTS];
    int accountCount;
} Bank;

void initBank(Bank* bank) {
    bank->accountCount = 0;
}

int findAccount(Bank* bank, const char* accountId) {
    for(int i = 0; i < bank->accountCount; i++) {
        if(strcmp(bank->accounts[i].accountId, accountId) == 0) {
            return i;
        }
    }
    return -1;
}

bool openAccount(Bank* bank, const char* accountId, double initialBalance) {
    if(initialBalance < 0 || bank->accountCount >= MAX_ACCOUNTS) {
        return false;
    }
    
    if(findAccount(bank, accountId) != -1) {
        return false;
    }

    BankAccount* account = &bank->accounts[bank->accountCount];
    strncpy(account->accountId, accountId, ACCOUNT_ID_LENGTH - 1);
    account->accountId[ACCOUNT_ID_LENGTH - 1] = '\\0';
    account->balance = initialBalance;
    account->isOpen = true;
    bank->accountCount++;
    return true;
}

bool closeAccount(Bank* bank, const char* accountId) {
    int index = findAccount(bank, accountId);
    if(index == -1) {
        return false;
    }
    
    if(!bank->accounts[index].isOpen) {
        return false;
    }
    
    bank->accounts[index].isOpen = false;
    return true;
}

bool withdraw(Bank* bank, const char* accountId, double amount) {
    int index = findAccount(bank, accountId);
    if(index == -1) {
        return false;
    }
    
    BankAccount* account = &bank->accounts[index];
    if(!account->isOpen || amount <= 0 || amount > account->balance) {
        return false;
    }
    
    account->balance -= amount;
    return true;
}

bool deposit(Bank* bank, const char* accountId, double amount) {
    int index = findAccount(bank, accountId);
    //todo    //incomplete code
    // if(index ==', type='text')
}