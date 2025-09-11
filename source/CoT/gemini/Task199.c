#include <stdio.h>
#include <stdbool.h>
#include <string.h>



struct Clock {
    int hours;
    int minutes;
};

void clock_init(struct Clock *clock, int hours, int minutes) {

    clock->hours = 0;
    clock->minutes = 0;
    clock_add(clock, hours * 60 + minutes);

}

void clock_add(struct Clock *clock, int minutes) {
    clock->minutes += minutes;
    clock->hours += clock->minutes / 60;
    clock->minutes %= 60;
    clock->hours %= 24;
    if (clock->hours < 0) {
        clock->hours += 24;
    }
    if (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours--;
        if (clock->hours < 0) {
            clock->hours += 24;
        }
    }
}

bool clock_equals(struct Clock c1, struct Clock c2) {
    return c1.hours == c2.hours && c1.minutes == c2.minutes;
}


void clock_to_string(struct Clock *clock, char* str) {
    sprintf(str, "%02d:%02d", clock->hours, clock->minutes);

}

int main() {
    struct Clock c1;
    clock_init(&c1, 10, 30);

    char str[6];


    clock_to_string(&c1, str);

    printf("%s\n", str); // Output: 10:30

    clock_add(&c1, 30);

    clock_to_string(&c1, str);
    printf("%s\n", str); // Output: 11:00



    struct Clock c2;
    clock_init(&c2, 23, 59);
    clock_add(&c2, 1);
    clock_to_string(&c2, str);
    printf("%s\n", str); // Output: 00:00


    struct Clock c3;
    clock_init(&c3, 10, 30);

    struct Clock c4;
    clock_init(&c4, 10, 30);


    printf("%d\n", clock_equals(c3, c4)); // Output: true (1)

    struct Clock c5;
    clock_init(&c5, 0, 0);

    clock_add(&c5, -1);
    clock_to_string(&c5, str);
    printf("%s\n", str); // Output: 23:59




    return 0;
}