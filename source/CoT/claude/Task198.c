
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    // API provided, implementation not shown
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
    printf("n = 1: [%d]\\n", rand10());
    
    // Test case 2: n = 2
    printf("n = 2: [%d,%d]\\n", rand10(), rand10());
    
    // Test case 3: n = 3
    printf("n = 3: [%d,%d,%d]\\n", rand10(), rand10(), rand10());
    
    // Test case 4: n = 4
    printf("n = 4: [%d,%d,%d,%d]\\n", rand10(), rand10(), rand10(), rand10());
    
    // Test case 5: n = 5
    printf("n = 5: [%d,%d,%d,%d,%d]\\n", rand10(), rand10(), rand10(), rand10(), rand10());
    
    return 0;
}
