
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Mock implementation of rand7()
int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int result = 40;
    while (result >= 40) {
        result = (rand7() - 1) * 7 + (rand7() - 1);
    }
    return result % 10 + 1;
}

int main() {
    srand(time(0));
    
    // Test case 1: n = 1
    printf("Test case 1: %d\\n", rand10());
    
    // Test case 2: n = 2
    printf("Test case 2: ");
    for(int i = 0; i < 2; i++) {
        printf("%d ", rand10());
    }
    printf("\\n");
    
    // Test case 3: n = 3
    printf("Test case 3: ");
    for(int i = 0; i < 3; i++) {
        printf("%d ", rand10());
    }
    printf("\\n");
    
    // Test case 4: n = 4
    printf("Test case 4: ");
    for(int i = 0; i < 4; i++) {
        printf("%d ", rand10());
    }
    printf("\\n");
    
    // Test case 5: n = 5
    printf("Test case 5: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", rand10());
    }
    printf("\\n");
    
    return 0;
}
