#include <stdio.h>
#include <time.h>

double getProcessorTimeInSeconds() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    for (int i = 0; i < 5; i++) {
        printf("%f\n", getProcessorTimeInSeconds());
    }
    return 0;
}