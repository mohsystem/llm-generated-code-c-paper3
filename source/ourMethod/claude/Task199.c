
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void setTime(Clock* clock, int hours, int minutes) {
    int totalMinutes = hours * 60 + minutes;
    
    // Handle negative time
    while (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }
    
    totalMinutes = totalMinutes % (24 * 60);
    clock->hours = (totalMinutes / 60) % 24;
    clock->minutes = totalMinutes % 60;
}

void initClock(Clock* clock, int hours, int minutes) {
    setTime(clock, hours, minutes);
}

void addMinutes(Clock* clock, int minutes) {
    setTime(clock, clock->hours, clock->minutes + minutes);
}

void subtractMinutes(Clock* clock, int minutes) {
    setTime(clock, clock->hours, clock->minutes - minutes);
}

bool isEqual(const Clock* clock1, const Clock* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void toString(const Clock* clock, char* buffer) {
    sprintf(buffer, "%02d:%02d", clock->hours, clock->minutes);
}

int main() {
    char timeStr[6];  // Format: "HH:MM\\0"
    
    // Test case 1: Basic initialization
    Clock clock1;
    initClock(&clock1, 8, 0);
    toString(&clock1, timeStr);
    printf("Test 1: %s\\n", timeStr);  // Should print 08:00
    
    // Test case 2: Add minutes
    Clock clock2;
    initClock(&clock2, 8, 0);
    addMinutes(&clock2, 30);
    toString(&clock2, timeStr);
    printf("Test 2: %s\\n", timeStr);  // Should print 08:30
    
    // Test case 3: Subtract minutes
    Clock clock3;
    initClock(&clock3, 8, 0);
    subtractMinutes(&clock3, 30);
    toString(&clock3, timeStr);
    printf("Test 3: %s\\n", timeStr);  // Should print 07:30
    
    // Test case 4: Equality test
    Clock clock4a, clock4b;
    initClock(&clock4a, 9, 30);
    initClock(&clock4b, 9, 30);
    printf("Test 4: %d\\n", isEqual(&clock4a, &clock4b));  // Should print 1
    
    // Test case 5: Wrap around midnight
    Clock clock5;
    initClock(&clock5, 23, 45);
    addMinutes(&clock5, 30);
    toString(&clock5, timeStr);
    printf("Test 5: %s\\n", timeStr);  // Should print 00:15
    
    return 0;
}
