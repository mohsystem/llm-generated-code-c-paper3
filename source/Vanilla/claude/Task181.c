
// C doesn't have built-in support for object-oriented programming and threading\n// Here's a basic implementation without thread safety

#include <stdio.h>
#include <stdbool.h>

struct BankAccount {
    double balance;
    bool isActive;
};

bool deposit(struct BankAccount* account, double amount) {
    if (!account->isActive) return false;
    if (amount <= 0) return false;
    
    account->balance += amount;
    return true;
}

bool withdraw(struct BankAccount* account, double amount) {
    if (!account->isActive) return false;
    if (amount <= 0) return false;
    
    if (account->balance >= amount) {
        account->balance -= amount;
        return true;
    }
    return false;
}

double getBalance(struct BankAccount* account) {
    if (!account->isActive) return -1;
    return account->balance;
}

bool closeAccount(struct BankAccount* account) {
    if (!account->isActive) return false;
    account->isActive = false;
    return true;
}

int main() {
    // Test Case 1: Basic deposit and withdraw
    struct BankAccount acc1 = {1000, true};
    printf("%d\\n", deposit(&acc1, 500));  // 1
    printf("%.2f\\n", getBalance(&acc1));  // 1500
    printf("%d\\n", withdraw(&acc1, 200)); // 1
    printf("%.2f\\n", getBalance(&acc1));  // 1300

    // Test Case 2: Invalid operations
    printf("%d\\n", deposit(&acc1, -100)); // 0
    printf("%d\\n", withdraw(&acc1, 2000)); // 0

    // Test Case 3: Cannot test concurrent operations in C

    // Test Case 4: Closed account operations
    struct BankAccount acc3 = {500, true};
    closeAccount(&acc3);
    printf("%d\\n", deposit(&acc3, 100));  // 0
    printf("%d\\n", withdraw(&acc3, 100)); // 0
    printf("%.2f\\n", getBalance(&acc3));  // -1

    // Test Case 5: Multiple deposits and withdrawals
    struct BankAccount acc4 = {0, true};
    for(int i = 0; i < 5; i++) {
        deposit(&acc4, 100);
        withdraw(&acc4, 50);
    }
    printf("%.2f\\n", getBalance(&acc4));  // 250

    return 0;
}
