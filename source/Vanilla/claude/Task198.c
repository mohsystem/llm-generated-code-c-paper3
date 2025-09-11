
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    // Simulated rand7() API
    return rand() % 7 + 1;
}

int rand10() {
    int result = 40;
    while (result >= 40) {
        result = 7 * (rand7() - 1) + (rand7() - 1);
    }
    return result % 10 + 1;
}

int main() {
    srand(time(0));
    
    // Test case 1: n = 1
    printf("%d\\n", rand10());
    
    // Test case 2: n = 2
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    
    // Test case 3: n = 3
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    
    // Test case 4: n = 4
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    
    // Test case 5: n = 5
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    printf("%d\\n", rand10());
    
    return 0;
}
