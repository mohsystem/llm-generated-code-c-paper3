#include <stdio.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

Task199 create_clock(int hours, int minutes) {
    Task199 clock;
    int total_minutes = hours * 60 + minutes;
    clock.hours = (total_minutes / 60) % 24;
    clock.minutes = total_minutes % 60;
    if (clock.minutes < 0) {
        clock.minutes += 60;
        clock.hours = (clock.hours - 1 + 24) % 24;
    }
    return clock;
}

void add_minutes(Task199* clock, int minutes_to_add) {
    int total_minutes = clock->hours * 60 + clock->minutes + minutes_to_add;
    clock->hours = (total_minutes / 60) % 24;
    clock->minutes = total_minutes % 60;
    if (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours = (clock->hours - 1 + 24) % 24;
    }
}

void subtract_minutes(Task199* clock, int minutes_to_subtract) {
    add_minutes(clock, -minutes_to_subtract);
}

int are_equal(Task199 clock1, Task199 clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

void print_clock(Task199 clock) {
    printf("%02d:%02d\n", clock.hours, clock.minutes);
}

int main() {
    Task199 clock1 = create_clock(14, 45);
    Task199 clock2 = create_clock(14, 45);
    Task199 clock3 = create_clock(23, 59);
    Task199 clock4 = create_clock(0, 0);
    Task199 clock5 = create_clock(12, 30);

    printf("%d\n", are_equal(clock1, clock2)); // 1
    printf("%d\n", are_equal(clock1, clock3)); // 0

    add_minutes(&clock3, 2);
    print_clock(clock3); // 00:01

    subtract_minutes(&clock4, 1);
    print_clock(clock4); // 23:59

    add_minutes(&clock5, 90);
    print_clock(clock5); // 14:00

    return 0;
}