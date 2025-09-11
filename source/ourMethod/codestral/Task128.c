#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void Task128_main() {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        printf("%d\n", rand());
    }
}

int main() {
    Task128_main();
    return 0;
}