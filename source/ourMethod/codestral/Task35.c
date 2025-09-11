#include<stdio.h>

int countPassengers(int stops[][2], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += stops[i][0] - stops[i][1];
    }
    return total;
}

int main() {
    int stops[][2] = {{10,0}, {3,5}, {5,8}};
    int size = sizeof(stops) / sizeof(stops[0]);
    printf("%d\n", countPassengers(stops, size));
    return 0;
}