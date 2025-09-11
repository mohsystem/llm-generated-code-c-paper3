
#include <stdio.h>
#include <stdlib.h>

int longest_run(int* arr, int size) {
    if (arr == NULL || size == 0) return 0;
    if (size == 1) return 1;
    
    int max_run = 1;
    int current_run = 1;
    int is_increasing = 1;  // Using 1 for true, 0 for false
    
    for (int i = 1; i < size; i++) {
        if (i == 1) {
            is_increasing = arr[1] > arr[0];
        }
        
        if ((is_increasing && arr[i] == arr[i-1] + 1) || 
            (!is_increasing && arr[i] == arr[i-1] - 1)) {
            current_run++;
            max_run = (current_run > max_run) ? current_run : max_run;
        } else {
            if (i < size - 1) {
                is_increasing = arr[i+1] > arr[i];
            }
            current_run = 1;
        }
    }
    
    return max_run;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int test2[] = {1, 2, 3, 10, 11, 15};
    int test3[] = {5, 4, 2, 1};
    int test4[] = {3, 5, 7, 10, 15};
    int test5[] = {1, 2, 3, 4, 5};
    
    printf("%d\\n", longest_run(test1, 8));  // 5
    printf("%d\\n", longest_run(test2, 6));  // 3
    printf("%d\\n", longest_run(test3, 4));  // 2
    printf("%d\\n", longest_run(test4, 5));  // 1
    printf("%d\\n", longest_run(test5, 5));  // 5
    
    return 0;
}
