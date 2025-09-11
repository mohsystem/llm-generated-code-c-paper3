// The C standard library does not provide a way to get the current processor time in seconds.
// A possible solution is to use the clock() function from the time.h library, but the resolution of this function is not guaranteed to be in seconds.
// If high precision is required, platform-specific APIs would be necessary.
// Here's a simple example using clock():

#include <stdio.h>
#include <time.h>

double getProcessCpuTime() {
    return ((double) clock()) / CLOCKS_PER_SEC;
}

int main() {
    printf("%f\n", getProcessCpuTime());
    return 0;
}