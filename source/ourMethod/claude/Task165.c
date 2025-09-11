
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkFlush(char *table[], int tableSize, char *hand[], int handSize) {
    if (!table || !hand || tableSize != 5 || handSize != 2) {
        return false;
    }
    
    int suitCount[4] = {0}; // S, H, D, C
    
    // Count suits on table
    for (int i = 0; i < tableSize; i++) {
        if (!table[i]) continue;
        int len = strlen(table[i]);
        if (len < 2) continue;
        
        char suit = table[i][len-1];
        switch(suit) {
            case 'S': suitCount[0]++; break;
            case 'H': suitCount[1]++; break;
            case 'D': suitCount[2]++; break;
            case 'C': suitCount[3]++; break;
        }
    }
    
    // Add hand suits
    for (int i = 0; i < handSize; i++) {
        if (!hand[i]) continue;
        int len = strlen(hand[i]);
        if (len < 2) continue;
        
        char suit = hand[i][len-1];
        switch(suit) {
            case 'S': suitCount[0]++; break;
            case 'H': suitCount[1]++; break;
            case 'D': suitCount[2]++; break;
            case 'C': suitCount[3]++; break;
        }
    }
    
    // Check for flush
    for (int i = 0; i < 4; i++) {
        if (suitCount[i] >= 5) return true;
    }
    
    return false;
}

int main() {
    char *test1_table[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char *test1_hand[] = {"J_D", "3_D"};
    printf("%d\\n", checkFlush(test1_table, 5, test1_hand, 2)); // 1 (true)
    
    char *test2_table[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char *test2_hand[] = {"K_S", "Q_S"};
    printf("%d\\n", checkFlush(test2_table, 5, test2_hand, 2)); // 1 (true)
    
    char *test3_table[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char *test3_hand[] = {"3_S", "4_D"};
    printf("%d\\n", checkFlush(test3_table, 5, test3_hand, 2)); // 0 (false)
    
    char *test4_table[] = {"A_H", "K_H", "Q_H", "J_H", "10_H"};
    char *test4_hand[] = {"2_H", "3_H"};
    printf("%d\\n", checkFlush(test4_table, 5, test4_hand, 2)); // 1 (true)
    
    char *test5_table[] = {"A_C", "K_C", "Q_C", "J_C", "10_S"};
    char *test5_hand[] = {"2_C", "3_H"};
    printf("%d\\n", checkFlush(test5_table, 5, test5_hand, 2)); // 0 (false)
    
    return 0;
}
