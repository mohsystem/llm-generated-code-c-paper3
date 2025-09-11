#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define a simple map implementation (for suits and their counts)
typedef struct {
    char suit[2];
    int count;
} SuitCount;

bool checkFlush(char table[5][4], char hand[2][4]) {
    SuitCount suitCounts[4] = {0}; // Initialize counts for each suit
    int numSuits = 0;

    // Function to add or update suit count
    void addSuit(char *suit) {
        for (int i = 0; i < numSuits; i++) {
            if (strcmp(suitCounts[i].suit, suit) == 0) {
                suitCounts[i].count++;
                return;
            }
        }
        strcpy(suitCounts[numSuits].suit, suit);
        suitCounts[numSuits].count = 1;
        numSuits++;
    }

    // Count suits in table and hand
    for (int i = 0; i < 5; i++) {
        char suit[2];
        strncpy(suit, table[i] + 2, 1); 
        suit[1] = '\0'; // Null-terminate
        addSuit(suit);
    }
    for (int i = 0; i < 2; i++) {
        char suit[2];
        strncpy(suit, hand[i] + 2, 1);
        suit[1] = '\0'; // Null-terminate
        addSuit(suit);
    }

    // Check for flush
    for (int i = 0; i < numSuits; i++) {
        if (suitCounts[i].count >= 5) {
            return true;
        }
    }

    return false;
}

int main() {
    // Test cases
    char table1[5][4] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char hand1[2][4] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1)); // true

    char table2[5][4] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char hand2[2][4] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2)); // true

    char table3[5][4] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char hand3[2][4] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3)); // false

    char table4[5][4] = {"2_H", "5_H", "A_H", "K_H", "J_H"};
    char hand4[2][4] = {"10_H", "Q_H"};
    printf("%d\n", checkFlush(table4, hand4)); // true


    char table5[5][4] = {"2_H", "5_D", "A_H", "K_C", "J_H"};
    char hand5[2][4] = {"10_S", "Q_S"};
    printf("%d\n", checkFlush(table5, hand5)); // false

    return 0;
}