#include <stdio.h>
#include <time.h>

void Task95_main() {
    double seconds;
    time_t t = time(NULL);
    if (t != ((time_t)-1)) {
        seconds = (double)t;
        printf("Current processor time in seconds: %.2f\n", seconds);
    } else {
        printf("Error occurred while retrieving the time.\n");
    }
}

int main() {
    Task95_main();
    return 0;
}