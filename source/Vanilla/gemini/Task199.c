#include <stdio.h>

struct Task199 {
    int minutes;
};

void add(struct Task199 *clock, int minutes) {
    clock->minutes = (clock->minutes + minutes) % (24 * 60);
    if (clock->minutes < 0) {
        clock->minutes += 24 * 60;
    }
}

void subtract(struct Task199 *clock, int minutes) {
    clock->minutes = (clock->minutes - minutes) % (24 * 60);
    if (clock->minutes < 0) {
        clock->minutes += 24 * 60;
    }
}

int getHours(struct Task199 clock) {
    return (clock.minutes / 60) % 24;
}

int getMinutes(struct Task199 clock) {
    return clock.minutes % 60;
}

int equals(struct Task199 clock1, struct Task199 clock2) {
    return clock1.minutes == clock2.minutes;
}


int main() {
    struct Task199 clock1 = {10 * 60 + 30};
    add(&clock1, 30);
    printf("%02d:%02d\n", getHours(clock1), getMinutes(clock1)); // Output: 11:00

    struct Task199 clock2 = {23 * 60 + 59};
    add(&clock2, 1);
    printf("%02d:%02d\n", getHours(clock2), getMinutes(clock2)); // Output: 00:00

    struct Task199 clock3 = {0};
    subtract(&clock3, 1);
    printf("%02d:%02d\n", getHours(clock3), getMinutes(clock3)); // Output: 23:59

    struct Task199 clock4 = {12 * 60};
    struct Task199 clock5 = {720};
    printf("%d\n", equals(clock4, clock5)); // 1 (true)
    printf("%02d:%02d\n", getHours(clock4), getMinutes(clock4)); // 12:00
    printf("%02d:%02d\n", getHours(clock5), getMinutes(clock5)); // 12:00

    return 0;
}