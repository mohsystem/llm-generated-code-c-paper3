
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkFlush(char* table[], int tableSize, char* hand[], int handSize) {
    int suitCount[4] = {0}; // S, H, D, C
    
    // Count suits from table cards
    for(int i = 0; i < tableSize; i++) {
        char suit = table[i][strlen(table[i]) - 1];
        switch(suit) {
            case 'S': suitCount[0]++; break;
            case 'H': suitCount[1]++; break;
            case 'D': suitCount[2]++; break;
            case 'C': suitCount[3]++; break;
        }
    }
    
    // Count suits from hand cards
    for(int i = 0; i < handSize; i++) {
        char suit = hand[i][strlen(hand[i]) - 1];
        switch(suit) {
            case 'S': suitCount[0]++; break;
            case 'H': suitCount[1]++; break;
            case 'D': suitCount[2]++; break;
            case 'C': suitCount[3]++; break;
        }
    }
    
    // Check if any suit count is 5 or more
    for(int i = 0; i < 4; i++) {
        if(suitCount[i] >= 5) return true;
    }
    return false;
}

int main() {
    // Test case 1
    char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char* hand1[] = {"J_D", "3_D"};
    printf("%d\\n", checkFlush(table1, 5, hand1, 2)); // 1
    
    // Test case 2
    char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char* hand2[] = {"K_S", "Q_S"};
    printf("%d\\n", checkFlush(table2, 5, hand2, 2)); // 1
    
    // Test case 3
    char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char* hand3[] = {"3_S", "4_D"};
    printf("%d\\n", checkFlush(table3, 5, hand3, 2)); // 0
    
    // Test case 4
    char* table4[] = {"A_H", "K_H", "Q_H", "J_H", "10_H"};
    char* hand4[] = {"9_H", "8_H"};
    printf("%d\\n", checkFlush(table4, 5, hand4, 2)); // 1
    
    // Test case 5
    char* table5[] = {"A_C", "K_D", "Q_H", "J_S", "10_C"};
    char* hand5[] = {"9_C", "8_C"};
    printf("%d\\n", checkFlush(table5, 5, hand5, 2)); // 0
    
    return 0;
}
