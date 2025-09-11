#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

void Task199_normalizeTime(Task199* clock) {
    clock->hours += clock->minutes / 60;
    clock->minutes %= 60;
    if (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours--;
    }
    clock->hours %= 24;
    if (clock->hours < 0) {
        clock->hours += 24;
    }
}

Task199 Task199_new(int hours, int minutes) {
    Task199 clock;
    clock.hours = hours;
    clock.minutes = minutes;
    Task199_normalizeTime(&clock);
    return clock;
}

void Task199_addMinutes(Task199* clock, int minutes) {
    clock->minutes += minutes;
    Task199_normalizeTime(clock);
}

void Task199_subtractMinutes(Task199* clock, int minutes) {
    clock->minutes -= minutes;
    Task199_normalizeTime(clock);
}

bool Task199_equals(const Task199* clock1, const Task199* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void Task199_print(const Task199* clock) {
    printf("%02d:%02d", clock->hours, clock->minutes);
}

int main() {
    Task199 clock1 = Task199_new(12, 30);
    Task199 clock2 = Task199_new(12, 30);
    Task199 clock3 = Task199_new(13, 0);

    printf("Clock1: ");
    Task199_print(&clock1);
    printf("\n");

    printf("Clock2: ");
    Task199_print(&clock2);
    printf("\n");

    printf("Clock3: ");
    Task199_print(&clock3);
    printf("\n");

    printf("Are Clock1 and Clock2 equal? %d\n", Task199_equals(&clock1, &clock2));
    printf("Are Clock1 and Clock3 equal? %d\n", Task199_equals(&clock1, &clock3));

    Task199_addMinutes(&clock1, 30);
    printf("Clock1 after adding 30 minutes: ");
    Task199_print(&clock1);
    printf("\n");

    Task199_subtractMinutes(&clock1, 60);
    printf("Clock1 after subtracting 60 minutes: ");
    Task199_print(&clock1);
    printf("\n");

    return 0;
}