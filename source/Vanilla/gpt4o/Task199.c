#include <stdio.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

Task199 create_clock(int h, int m) {
    Task199 clock;
    clock.hours = (h + m / 60) % 24;
    if (clock.hours < 0) clock.hours += 24;
    clock.minutes = m % 60;
    if (clock.minutes < 0) clock.minutes += 60;
    return clock;
}

Task199 add_minutes(Task199 clock, int minutesToAdd) {
    return create_clock(clock.hours, clock.minutes + minutesToAdd);
}

Task199 subtract_minutes(Task199 clock, int minutesToSubtract) {
    return create_clock(clock.hours, clock.minutes - minutesToSubtract);
}

int equals(Task199 c1, Task199 c2) {
    return c1.hours == c2.hours && c1.minutes == c2.minutes;
}

void print_clock(Task199 clock) {
    printf("%02d:%02d\n", clock.hours, clock.minutes);
}

int main() {
    Task199 clock1 = create_clock(10, 30);
    Task199 clock2 = create_clock(10, 30);
    Task199 clock3 = add_minutes(clock1, 45);
    Task199 clock4 = subtract_minutes(clock1, 75);
    Task199 clock5 = add_minutes(create_clock(23, 59), 2);

    printf("%d\n", equals(clock1, clock2)); // 1 (true)
    print_clock(clock3);                    // 11:15
    print_clock(clock4);                    // 08:45
    print_clock(clock5);                    // 00:01
    printf("%d\n", equals(clock1, clock3)); // 0 (false)

    return 0;
}