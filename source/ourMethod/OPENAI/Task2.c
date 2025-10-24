#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* create_phone_number(const int* numbers, size_t len) {
    if (numbers == NULL) {
        return NULL;
    }
    if (len != 10) {
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            return NULL;
        }
    }
    // "(123) 456-7890" -> 14 chars + null terminator
    char* out = (char*)malloc(15);
    if (!out) {
        return NULL;
    }
    int written = snprintf(
        out, 15,
        "(%d%d%d) %d%d%d-%d%d%d%d",
        numbers[0], numbers[1], numbers[2],
        numbers[3], numbers[4], numbers[5],
        numbers[6], numbers[7], numbers[8], numbers[9]
    );
    if (written < 0 || written >= 15) {
        free(out);
        return NULL;
    }
    return out;
}

static void run_test(const int* arr, size_t len) {
    char* res = create_phone_number(arr, len);
    printf("[");
    for (size_t i = 0; i < len; ++i) {
        printf("%d%s", arr[i], (i + 1 < len) ? "," : "");
    }
    printf("] -> ");
    if (res) {
        printf("%s\n", res);
        free(res);
    } else {
        printf("ERROR\n");
    }
}

int main(void) {
    int t1[10] = {1,2,3,4,5,6,7,8,9,0};   // valid
    int t2[10] = {0,0,0,0,0,0,0,0,0,0};   // valid
    int t3[10] = {9,7,6,5,4,3,2,1,0,9};   // valid
    int t4[9]  = {1,2,3,4,5,6,7,8,9};     // invalid length
    int t5[10] = {1,2,3,4,5,6,7,8,9,10};  // invalid digit

    run_test(t1, 10);
    run_test(t2, 10);
    run_test(t3, 10);
    run_test(t4, 9);
    run_test(t5, 10);

    return 0;
}